#include "Model.h"

// Initialize
Model::Model(){
    mouseX = 0;
    mouseY = 0;
    ueIndex = 0;
    cellIndex = 0;
    ueArrivalRate = 10;
    tempCell = NULL;
    mousePressed = false;
    cellType = celltype::Macro;
    countPressedReleased = 0;
    tempCell = NULL;
    simulationTime = 0;
    simulationCounter = 0;
    nBeams = 4;
    FR = 0;
    prachConfigIndex = 16;
    outputFolderName = "./result/";
    outputFileExtension = ".csv";
    outputFileUE = "UE";
    outputFileCell = "Cell";
    mode = DrawMode::DrawCell;
    nPreambles = 64;
    preambleSCS = 1.25;
}

// Set mouse XY position
void Model::setMouseXY(int x, int y){
    mouseX = x;
    mouseY = y;
    if(mode == DrawMode::DrawCell){
        if(isMousePressed() && countPressedReleased == 1){
            // do when mouse first pressed
            tempCell->setX(mouseX);
            tempCell->setY(mouseY);
        }
        else if(countPressedReleased > 1){
            // do things when mouse click second time
            tempCell->updateBeamsAngle(x - tempCell->getX(),
                    tempCell->getY() - y);
            //tempCell->updateBeamsAngle(x - tempCell->getX(),
            //        y - tempCell->getY());
        }
        if(countPressedReleased >= 1)
            notifyAll();
    }
    else{
        eraseRect.setXY(mouseX, mouseY);
        notifyAll();
    }
}

// Get mouse X position
int Model::getMouseX(){
    return mouseX;
}

// Get mouse y position
int Model::getMouseY(){
    return mouseY;
}

// Set mouse is pressed or not
void Model::setMousePressed(bool isPressed){
    mousePressed = isPressed;
    countPressedReleased++;
    if(mousePressed){
        if(countPressedReleased == 1 && mode == DrawMode::DrawCell){
            if(cellType == celltype::Macro)
                tempCell = new MacroCell(mouseX, mouseY, cellIndex++, nBeams, cellType, prachConfigIndex, nPreambles, cellBW, preambleSCS); 
            else
                tempCell = new FemtoCell(mouseX, mouseY, cellIndex++, nBeams, cellType, prachConfigIndex, nPreambles, cellBW, preambleSCS);
            tempCell->initializeBeams();
        }
        
        else if(countPressedReleased == 3){
            // TODO
            // do mouse pressed second time
        }
        if(mode == DrawMode::EraseCell){
            detectCellInEraseArea();
        }
    }
    else if(!mousePressed 
            && countPressedReleased == 4 
            && mode == DrawMode::DrawCell){
        // mouse release second time
        tempCell->updateBeamsAngle(this->mouseX - tempCell->getX(),
                tempCell->getY() - this->mouseY);
        //tempCell->findCellCoverAreaEquation();
        countPressedReleased = 0;
        cells.push_back(tempCell);
        tempCell = NULL;
        notifyAll();
    }
    if(mode == DrawMode::EraseCell)
        countPressedReleased = 0;
}

// Get mouse is pressed or not
bool Model::isMousePressed(){
    return mousePressed;
}

// Draw Cells and UEs
void Model::draw(QPainter &painter){
    drawing(painter);
    if(mode == DrawMode::EraseCell){
        erasing(painter);
    }
}

// get number of mouse pressed count
int Model::getPressedCount(){
    return countPressedReleased;
}

// get FR mode
// 0: FR1
// 1: FR2
unsigned int Model::getFR(){
    return FR;
}

// notify all IPaintObservor
void Model::notifyAll(){
    for(unsigned int i = 0;i < observors.size();i++){
        IPaintObservor *o = observors.at(i);
        o->updateCanvas();
    }
}

// register a IPaintObservor
void Model::registerPaintObservor(IPaintObservor *observor){
    observors.push_back(observor);
}

// traverse all UEs and detect them is in cell or not
void Model::traverseUEs(){
    UE *ue;
    Cell *cell;
    for(unsigned int i = 0;i < UEs.size();i++){
        //printf("%lu\n", i);
        ue = UEs.at(i);
        //printf("ues size: %lu\n", UEs.size());
        if(ue->isRASuccess()){
            recordUELatency(ue);
            UEs.erase(UEs.begin() + i);
            delete ue;
            i--;
            if(remainingUEs)
                remainingUEs--;
            continue;
        }
        //printf("ues size: %lu\n", UEs.size());
        for(unsigned int j = 0;j < cells.size();j++){
            cell = cells.at(j);
            cell->detectUE(ue);
        }
    }
}

// transmit cells downlink
// first broadcast all cells' system information
// for ue to deregister from the cell that SINR is not the best one
// since when traverse all UEs, cell will first store all detected UE
// then when ue receive SI, it will deregister from the cell 
// that it does not select
// second, cell will then transmit RAR and CR later
void Model::transmitDL(){
    Cell *cell;
    for(auto it = cells.begin();it != cells.end();it++){
        (*it)->broadcastSI();
    }
    for(unsigned int i = 0;i < cells.size();i++){
        cell = cells.at(i);
    //    cell->broadcastSI();
        cell->transmitRAR();
        cell->transmitCR();
    }
}

// transmit all UEs' uplink aka performing RA
void Model::transmitUL(){
    UE *ue;
    for(unsigned int i = 0;i < UEs.size();i++){
        ue = UEs.at(i);
        if(ue->isBindCell()){
            //printf("UE %lu doing doRA\n", ue->getID());
            ue->doRA();
            //printf("UE %lu complete doRA\n", ue->getID());
        }
    }
}

// start the simulation
// if simulation time or no cell is in the canvas
// it won't start the simulation
// otherwise, frame, subframe number, ueIndex counter,
// remaining UEs will be reset
// then, run the simulation for simulationTime in ms
// finally, if there are UEs remain after simulationTime,
// simulation will then proceed until all UEs success
void Model::startSimulation(){
    if(!TESTING){
        initializeOutFiles();
        if(!outFileUE || !outFileCell){
            SPDLOG_CRITICAL("ue output file create failed!\n");
            exit(1);
        }
    }
    //////////////////////// testing ////////////////////////
    //simulationTime = 16;
    //////////////////////// testing ////////////////////////
    ueIndex = 0;
    remainingUEs = 0;
    bool isTimesUp = false;
    if(simulationTime == 0 || cells.size() == 0){
        SPDLOG_WARN("no cell in simulation or simualtion time is 0");
        return;
    }
    for(unsigned int i = 0;i < cells.size();i++){
        cells.at(i)->resetFrame();
    }
    for(int i = 0;i < simulationTime;i++){
        run(isTimesUp);
    }
    isTimesUp = true;
    if(UEs.size() > 0 && !TESTING){
        for(auto it = UEs.begin();it != UEs.end();it++){
            if((*it)->isBindCell()){
                remainingUEs++;
            }
        }
        while(remainingUEs){
            run(isTimesUp);
            SPDLOG_TRACE("remaining UEs: {0}", remainingUEs);
        }
    }
    SPDLOG_INFO("simulation: {0} complete", simulationCounter++);
    if(!TESTING){
        recordCellsInfo();
        restoreCells2Initial();
        plotResult();
        closeOutFiles();
    }
}

// set the simulation time
// simulationTime: the simulation time for simulation
// it will be stored in ms
void Model::setSimulationTime(int simulationTime){
    // model store simulation time in msec
    this->simulationTime = simulationTime * 1000;
    SPDLOG_TRACE("{0}", this->simulationTime);
}

// set number of beams
// nBeams: number of beams
void Model::setnBeams(const int nBeams){
    this->nBeams = nBeams;
}

// set cell type
// type: cell type
void Model::setCellType(const celltype::CellType type){
    cellType = type;
}

// set UE arrival rate
// arrivalRate: ue arrival rate
void Model::setArrivalRate(const unsigned int arrivalRate){
    SPDLOG_TRACE("arrival rate: {0}", arrivalRate);
    ueArrivalRate = arrivalRate;
}

// set prach configuration index
// s: input from GUI's combobox item text
void Model::setPrachConfigIndex(string s){
    //cout << s << endl;
    int spaceIndex = s.find(";");
    int colonIndex = s.find(":");
    string sPrachConfigIndex = s.substr(colonIndex + 1, spaceIndex - colonIndex - 1);
    prachConfigIndex = stoi(sPrachConfigIndex);
    SPDLOG_TRACE("prach configuration index: {0}", prachConfigIndex);
    //cout << prachConfigIndex << endl;
}

// set drawing mode
// mode: draw cell mode or erase cell mode
void Model::setDrawMode(DrawMode::Mode mode){
    this->mode = mode;
    SPDLOG_TRACE("mode: {0}", this->mode);
}

// set number of preambles
// nPreambles: number of preambles
void Model::setNPreambles(const int nPreambles){
    this->nPreambles = nPreambles;
    SPDLOG_TRACE("nPreambles: {0}", this->nPreambles);
}

// set preamble SCS
// preambleSCS: preamble SCS
void Model::setPreambleSCS(const double preambleSCS){
    this->preambleSCS = preambleSCS;
    SPDLOG_TRACE("praemble SCS: {0}", this->preambleSCS);
}

// set cell BW
// cellBW: cell BW
void Model::setCellBW(const int cellBW){
    this->cellBW = cellBW;
    SPDLOG_TRACE("cell BW: {0}", this->cellBW);
}

// set FR
// FR: FR
void Model::setFR(const unsigned int FR){
    this->FR = FR;
}

// run the simulation
// first, traverse each UEs stored in model to detect 
// whether UE is in the cell
// second, transmit cell's DL
// third, transmit UE's UL
// isTimesUp: when simulationTime is 0, set this value to true
// for proceeding remaining UEs RA
void Model::run(bool isTimesUp){
    SPDLOG_INFO("=================info=================");
    recordCellsInfo();
    if(!isTimesUp)
        generateRandomUEs();
    SPDLOG_INFO("frame: {0}, subframe: {1}", 
            cells.at(0)->getFrameIndex(),
            cells.at(0)->getSubframeIndex());
    traverseUEs();
    notifyAll();
    transmitDL();
    SPDLOG_TRACE("downlink transmit complete");
    transmitUL();
    SPDLOG_TRACE("uplink transmit complete");
    for(unsigned int j = 0;j < cells.size();j++){
        cells.at(j)->updateSubframe();
    } 
    SPDLOG_INFO("=================info=================");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

// generate random number UEs based on ueArrivalRate
// first random select a cell
// second random select an angle
// third random select a distance from the cell centor
// notice that random generated angle has a 5 degree tolerance
// and random generated distance has a 10 tolerance
// for decreasing the probability of cell cannot detect ue
// then calculate random x, y point based on distance and angle
void Model::generateRandomUEs(){
    Cell *cell;
    SPDLOG_TRACE("generating ues\n");
    for(int i = 0;i < ueArrivalRate;i++){
        int rndCellIndex = getRnd(0, cells.size() - 1);

        cell = cells[rndCellIndex];
        double cellStartAngle = cell->getBeamStartAngle();
        double cellSpanAngle = cell->getCellSpanAngle();

        int rndAngle = getRnd(cellStartAngle + 5, 
                cellStartAngle + cellSpanAngle - 5);
        //printf("%d\n", cell->getCellSupportDistance());
        int rndDistance = getRnd(10, cell->getCellSupportDistance() / 2);
        int rndX = rndDistance * cos(rndAngle * M_PI / 180.0);
        int rndY = rndDistance * sin(rndAngle * M_PI / 180.0);
        UE *ue = new UE(cell->getX() + rndX,
                cell->getY() - rndY,
                ueIndex++);
        ue->setActiveTime(cell->getFrameIndex(), cell->getSubframeIndex());
        UEs.push_back(ue);
    }
}

// record ue active and departed frame and subframe index to a file
void Model::recordUELatency(UE *ue){
    int cellIndexUE = ue->getCellIndex();
    auto it = cells.begin();
    for(it;it != cells.end();it++)
        if((*it)->getCellIndex() == cellIndexUE)
            break;
    outFileUE << ue->getID() << ", " 
        << ue->getCellIndex() << ", " 
        << (*it)->getnBeams() << ", "
        << ue->getBeamIndex() << ", "
        << ue->getRASSBPerRAO() << ", "
        << ue->getRAMsg1FDM() << ", "
        << ue->getActiveFrame() << ", " 
        << ue->getActiveSubframe() << ", " 
        << ue->getRAFrame() << ", "
        << ue->getRASubframe() << ", "
        << ue->getDepartedFrame() << ", " 
        << ue->getDepartedSubframe() << ", "
        << ue->getSelectRAOIndex() << ", "
        << ue->getSelectPreambleIndex() << ", "
        << ue->isCollided() << endl;
}

// record each cells information every 160ms
void Model::recordCellsInfo(){
    auto it = cells.begin();
    const int frame = (*it)->getFrameIndex();
    const int subframe = (*it)->getSubframeIndex();
    if((frame * 10 + subframe) % 160 != 0 && UEs.size() != 0)
        return;
    for(;it != cells.end();it++){
        outFileCell << (*it)->getCellIndex() << ", "
            << (*it)->getnBeams() << ", "
            << (*it)->getFrameIndex() << ", "
            << (*it)->getSubframeIndex() << ", "
            << (*it)->getSSBPerRAO() << ", "
            << (*it)->getMsg1FDM() << ", "
            << (*it)->getPrachConfigIndex() << ", " 
            << (*it)->getSuccessUEs() << ", "
            << (*it)->getEstimateUEs() << ", "
            << (*it)->getFailedUEs() << endl;
    }
}

// initialize output files
void Model::initializeOutFiles(){
    time_t t = time(nullptr);
    tm tm = *localtime(&t);
    stringstream ss;
    ss << put_time(&tm, "%Y%m%d_%H%M%S");
    curTime = ss.str();

    outputFolderName = outputFolderName + curTime 
        + "_prach-" + to_string(cells[0]->getPrachConfigIndex()) 
        + "_simu-" + to_string(simulationTime / 10) 
        + "_arrival-" + to_string(ueArrivalRate) + "/";

    string command = "mkdir " + outputFolderName; 
    system(command.c_str());

    filenameUE = outputFolderName + outputFileUE + outputFileExtension;
    filenameCell = outputFolderName + outputFileCell + outputFileExtension;
    outFileUE = ofstream(filenameUE);
    outFileUE << "\"UE ID\", \"Cell ID\", \"Total Beams\", \"Beam Index\", \"SSB per RAO\", \"msg1-FDM\", \"Active Frame\", \"Active Subframe\", \"RA Frame\", \"RA Subframe\", \"Departed Frame\", \"Departed Subframe\", \"Selected RAO Undex\", \"Selected Preamble\", \"Collided\"" << endl;
    outFileCell = ofstream(filenameCell);
    outFileCell << "\"Cell ID\", \"Total Beams\", \"Current Frame\", \"Current Subframe\", \"SSB per RAO\", \"msg1-FDM\", \"prach-ConfigurationIndex\", \"Success UEs\", \"Estimate UEs\", \"Failed UEs\"" << endl;
}

// close output files
void Model::closeOutFiles(){
    outFileUE.close();
    outFileCell.close();
    outputFolderName = "./result/";
}

// plot result done recently
void Model::plotResult(){
    string command = "python3 ./scripts/plot_result.py " + outputFolderName + " " + filenameUE + " " + filenameCell + " " + to_string(cells[0]->getPrachConfigIndex()) + " " + to_string(simulationTime) + " " + to_string(ueArrivalRate);
    system(command.c_str());
}

// restore the cell's ssb per rao and msg1-fdm to initial status
void Model::restoreCells2Initial(){
    for(auto it = cells.begin();it != cells.end();it++){
        (*it)->restoreMonitorRA2Initial();
    }
}

// draw cell/ue
// painter: QPainter
void Model::drawing(QPainter &painter){
    Cell *cell;
    UE *ue;
    for(unsigned int i = 0;i < cells.size();i++){
        cell = cells.at(i);
        cell->draw(painter);
    }
    if(countPressedReleased >= 1 
            && countPressedReleased < 4 
            && mode == DrawMode::DrawCell){
        tempCell->draw(painter);
    }
    //painter.setBrush(QBrush(QColor(200, 128, 255, 255), Qt::SolidPattern));
    for(decltype(UEs.size()) i = 0;i < UEs.size();i++){
        ue = UEs[i];
        ue->draw(painter);
    }
}

// erase cell
// painter: QPainter
void Model::erasing(QPainter &painter){
    eraseRect.draw(painter);
}

// detect cell is in erase area
// if cell is in erase area, delete
void Model::detectCellInEraseArea(){
    for(decltype(cells.size()) i = 0;i < cells.size();++i){
        SPDLOG_INFO("i: {0}", i);
        SPDLOG_INFO("cell size: {0}", cells.size());
        if(eraseRect.isInside(cells[i]->getX(),
                cells[i]->getY())){
            SPDLOG_INFO("cell {0} is in erase area", cells[i]->getCellIndex());
            Cell *cell = cells[i];
            cells.erase(cells.begin() + i);
            delete cell;
            --i;
        }
    }
}

// destructor
Model::~Model(){
    SPDLOG_TRACE("model destructor");
    for(auto it = cells.begin();it != cells.end();it++){
        delete (*it);
    }
}
