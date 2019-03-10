#include "Model.h"

// Initialize
Model::Model(){
    mouseX = 0;
    mouseY = 0;
    tempCell = NULL;
    mousePressed = false;
    cellType = Macro;
    countPressedReleased = 0;
    tempCell = NULL;
    simulationTime = 0;
    ue = new UE(300, 200, UEs.size());
    UEs.push_back(ue);
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
        if(countPressedReleased == 1)
            tempCell = new MacroCell(mouseX, mouseY, cells.size(), 4, cellType, 106); 
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
    for(auto i = 0;i < UEs.size();i++){
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
        ue = UEs.at(i);
        if(ue->isRASuccess()){
            UEs.erase(UEs.begin() + i);
            continue;
        }
        //if(!ue->isBindCell()){
        //}
        for(unsigned int j = 0;j < cells.size();j++){
            cell = cells.at(j);
            cell->detectUE(ue);
        }
    }
}

void Model::transmitDL(){
    Cell *cell;
    for(unsigned int i = 0;i < cells.size();i++){
        cell = cells.at(i);
        cell->broadcastSI();
        cell->transmitRAR();
        cell->transmitCR();
    }
}

void Model::transmitUL(){
    UE *ue;
    for(unsigned int i = 0;i < UEs.size();i++){
        ue = UEs.at(i);
        ue->doRA();
    }
}

void Model::startSimulation(){
    if(simulationTime == 0 || cells.size() == 0){
        printf("no cell in simulation or simualtion time is 0\n");
        return;
    }
    for(unsigned int i = 0;i < cells.size();i++){
        cells.at(i)->resetFrame();
    }
    for(int i = 0;i < simulationTime;i++){
        printf("=================info=================\n");
        printf("frame: %d\nsubframe: %d\n", 
                cells.at(0)->getFrameIndex(),
                cells.at(0)->getSubframeIndex());
        traverseUEs();
        notifyAll();
        transmitDL();
        transmitUL();
        for(unsigned int j = 0;j < cells.size();j++){
            cells.at(j)->updateSubframe();
        } 
        printf("=================info=================\n");
    }
}

void Model::setSimulationTime(int simulationTime){
    // model store simulation time in msec
    this->simulationTime = simulationTime * 10;
    //printf("%d\n", this->simulationTime);
}
