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
}

// Set mouse XY position
void Model::setMouseXY(int x, int y){
    mouseX = x;
    mouseY = y;
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
        if(countPressedReleased == 1){
            if(cellType == celltype::Macro)
                tempCell = new MacroCell(mouseX, mouseY, cellIndex++, nBeams, cellType, 106); 
            else
                tempCell = new FemtoCell(mouseX, mouseY, cellIndex++, nBeams, cellType, 106);
            tempCell->initializeBeams();
        }
        
        else if(countPressedReleased == 3){
            // TODO
            // do mouse pressed second time
        }
    }
    else if(!mousePressed && countPressedReleased == 4){
        // mouse release second time
        tempCell->updateBeamsAngle(this->mouseX - tempCell->getX(),
                tempCell->getY() - this->mouseY);
        tempCell->findCellCoverAreaEquation();
        countPressedReleased = 0;
        cells.push_back(tempCell);
        tempCell = NULL;
        notifyAll();
    }
}

// Get mouse is pressed or not
bool Model::isMousePressed(){
    return mousePressed;
}

// Draw Cells and UEs
void Model::draw(QPainter &painter){
    Cell *cell;
    UE *ue;
    for(unsigned int i = 0;i < cells.size();i++){
        cell = cells.at(i);
        cell->drawCell(painter);
    }
    if(countPressedReleased >= 1 && countPressedReleased < 4){
        tempCell->drawCell(painter);
    }
    painter.setBrush(QBrush(QColor(200, 128, 255, 255), Qt::SolidPattern));
    for(decltype(UEs.size()) i = 0;i < UEs.size();i++){
        ue = UEs[i];
        ue->drawUE(painter);
    }
}

// get number of mouse pressed count
int Model::getPressedCount(){
    return countPressedReleased;
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
    ueIndex = 0;
    remainingUEs = 0;
    bool isTimesUp = false;
    if(simulationTime == 0 || cells.size() == 0){
        printf("no cell in simulation or simualtion time is 0\n");
        return;
    }
    for(unsigned int i = 0;i < cells.size();i++){
        cells.at(i)->resetFrame();
    }
    for(int i = 0;i < simulationTime;i++){
        run(isTimesUp);
    }
    isTimesUp = true;
    if(UEs.size() > 0){
        for(auto it = UEs.begin();it != UEs.end();it++){
            if((*it)->isBindCell()){
                remainingUEs++;
            }
        }
        while(remainingUEs){
            run(isTimesUp);
            printf("remaining UEs: %d\n", remainingUEs);
        }
    }
    printf("simulation: %d complete\n", simulationCounter++);
}

// set the simulation time
// simulationTime: the simulation time for simulation
// it will be stored in ms
void Model::setSimulationTime(int simulationTime){
    // model store simulation time in msec
    this->simulationTime = simulationTime * 10;
    //printf("%d\n", this->simulationTime);
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
    printf("arrival rate: %lu\n", arrivalRate);
    ueArrivalRate = arrivalRate;
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
    //for(int i = 0;i < 1;i++){
    printf("=================info=================\n");
    if(!isTimesUp)
        generateRandomUEs();
    printf("frame: %d\nsubframe: %d\n", 
            cells.at(0)->getFrameIndex(),
            cells.at(0)->getSubframeIndex());
    traverseUEs();
    notifyAll();
    transmitDL();
    printf("downlink transmit complete\n");
    transmitUL();
    printf("uplink transmit complete\n");
    for(unsigned int j = 0;j < cells.size();j++){
        cells.at(j)->updateSubframe();
    } 
    printf("=================info=================\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

// generate random number UEs based on ueArrivalRate
// first random select a cell
// second random select an angle
// third random select a distance from the cell centor
// FIXME////////////////////////FIXME
// notice that random generated angle has a 5 degree tolerance
// and random generated distance has a 10 tolerance
// for decreasing the probability of cell cannot detect ue
// FIXME////////////////////////FIXME
// then calculate random x, y point based on distance and angle
void Model::generateRandomUEs(){
    Cell *cell;
    printf("generating ues\n");
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
        //printf("random angle: %d, random distance: %d\n",
        //        rndAngle,
        //        rndDistance);
        //printf("random x: %d, random y: %d\n",
        //        rndX,
        //        rndY);
        UE *ue = new UE(cell->getX() + rndX,
                cell->getY() - rndY,
                ueIndex++);
        UEs.push_back(ue);
    }
}

