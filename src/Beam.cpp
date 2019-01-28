#include "Beam.h"

Beam::Beam(int x, int y, int index, int lengthBeam, int spanAngle){
    setXY(x, y);
    setBeamIndex(index);
    setLengthBeam(lengthBeam);
    setSpanAngle(spanAngle);
    setStartAngle(index, spanAngle);
}

void Beam::setX(int x){
    this->x = x;
}

void Beam::setY(int y){
    this->y = y;
}

void Beam::setXY(int x, int y){
    this->x = x;
    this->y = y;
}

void Beam::setBeamIndex(int index){
    this->index = index;
}

void Beam::setLengthBeam(int lengthBeam){
    this->lengthBeam = lengthBeam;
}

void Beam::setSpanAngle(int spanAngle){
    this->spanAngle = spanAngle;
}

void Beam::setStartAngle(int index, int spanAngle){
    this->startAngle = (index - 1) * spanAngle;
}

void Beam::setStartAngle(int startAngle){
    this->startAngle = startAngle;
}

int Beam::getX(){
    return this->x;
}

int Beam::getY(){
    return this->y;
}

int Beam::getBeamIndex(){
    return this->index;
}

int Beam::getSpanAngle(){
    return this->spanAngle;
}

int Beam::getStartAngle(){
    return this->startAngle;
}

int Beam::getLengthBeam(){
    return this->lengthBeam;
}

void Beam::drawBeam(QPainter &painter){
    painter.drawPie(x - lengthBeam / 2, 
            y - lengthBeam / 2,
            lengthBeam,
            lengthBeam,
            startAngle * 16,
            spanAngle * 16);
}

