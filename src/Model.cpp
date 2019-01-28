#include "Model.h"

// Initialize
Model::Model(){
    mouseX = 0;
    mouseY = 0;
    tempCell = NULL;
    mousePressed = false;
    cellType = Macro;
    tempCell = new MacroCell(mouseX, mouseY, 4, cellType);
    countPressedReleased = 0;
}

// Set mouse XY position
void Model::setMouseXY(int x, int y){
    mouseX = x;
    mouseY = y;
    if(isMousePressed() && countPressedReleased == 1){
        tempCell->setX(mouseX);
        tempCell->setY(mouseY);
    }
    else if(countPressedReleased == 3){
        // TODO
        // do mouse click second time
        tempCell->updateBeamsAngle(x - tempCell->getX(),
                tempCell->getY() - y);
    }
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
            tempCell = new MacroCell(mouseX, mouseY, 4, cellType); 
        else if(countPressedReleased == 3){
            // TODO
            // do mouse pressed second time
        }
    }
    else if(!mousePressed && countPressedReleased == 4){
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
    for(int i = 0;i < cells.size();i++){
        Cell *cell = cells.at(i);
        cell->drawCell(painter);
    }
    if(countPressedReleased >= 1 && countPressedReleased < 4){
        tempCell->drawCell(painter);
    }
}

// get number of mouse pressed count
int Model::getPressedCount(){
    return countPressedReleased;
}

// notify all IPaintObservor
void Model::notifyAll(){
    for(int i = 0;i < observors.size();i++){
        IPaintObservor *o = observors.at(i);
        o->updateCanvas();
    }
}

// register a IPaintObservor
void Model::registerPaintObservor(IPaintObservor *observor){
    observors.push_back(observor);
}
