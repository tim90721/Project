#include "Model.h"

// Initialize
Model::Model(){
    mouseX = 0;
    mouseY = 0;
    tempCell = NULL;
    mousePressed = false;
    cellType = Macro;
    tempCell = new MacroCell(mouseX, mouseY, cellType);
}

// Set mouse XY position
void Model::setMouseXY(int x, int y){
    mouseX = x;
    mouseY = y;
    tempCell->setX(mouseX);
    tempCell->setY(mouseY);
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
    if(mousePressed){
        tempCell = new MacroCell(mouseX, mouseY, cellType); 
    }
    else if(!mousePressed){
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
    if(mousePressed){
        tempCell->drawCell(painter);
    }
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
