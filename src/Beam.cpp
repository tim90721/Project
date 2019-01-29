#include "Beam.h"

// constructor
// x: x position of cell center
// y: y position of cell center
// beamIndex: beam index
// lengthBeam: the beam length(strength), corresponding to Cell supportDistance member
// spanAngle: each beam's area(in form of angle) in a cell
Beam::Beam(int x, int y, int cellIndex, int beamIndex, int lengthBeam, int spanAngle){
    setXY(x, y);
    setCellIndex(cellIndex);
    setBeamIndex(beamIndex);
    setLengthBeam(lengthBeam);
    setSpanAngle(spanAngle);
    setStartAngle(beamIndex, spanAngle);
}

// set beam's x position
// x: x position of cell center
void Beam::setX(int x){
    this->x = x;
}

// set beam's y position
// y: y position of cell center
void Beam::setY(int y){
    this->y = y;
}

// set beam's x and y position
// x: x position of cell center
// y: y position of cell center 
void Beam::setXY(int x, int y){
    this->x = x;
    this->y = y;
}

// set beam's index
// beamIndex: the index of beam
void Beam::setBeamIndex(int beamIndex){
    this->beamIndex = beamIndex;
}

// set length(strength) of this beam
// lengthBeam: corresponding to Cell supportDistance member
void Beam::setLengthBeam(int lengthBeam){
    this->lengthBeam = lengthBeam;
}

// set span angle
// the area cover by this beam, in form of angle
// spanAngle: the angle covered by this beam
void Beam::setSpanAngle(int spanAngle){
    this->spanAngle = spanAngle;
}

// set this beam's start angle
// beam will draw from (start angle) to ((start angle) + (span angle))
// beamIndex: the index of this beam
// spanAngle: the angle covered by this beam
void Beam::setStartAngle(int beamIndex, int spanAngle){
    this->startAngle = (beamIndex - 1) * spanAngle;
}

// set this beam's start angle
// beam will draw from (start angle) to ((start angle) + (span angle))
// startAngle: the start drawing angle of this beam
void Beam::setStartAngle(int startAngle){
    this->startAngle = startAngle;
}

// set this beam's cell index
// cellIndex: cell index
void Beam::setCellIndex(int cellIndex){
    this->cellIndex = cellIndex;
}

// get this beam's x position
// return: this beam's x position, equals to x position of cell center
int Beam::getX(){
    return this->x;
}

// get this beam's y position
// return: this beam's y position, equals to y position of cell center
int Beam::getY(){
    return this->y;
}

// get this beam's index
// return: this beam's index
int Beam::getBeamIndex(){
    return this->beamIndex;
}

// get this beam's span angle
// the beam will cover the area with this span angle
// return: this beam's span angle
int Beam::getSpanAngle(){
    return this->spanAngle;
}

// get this beam's start angle
// the beam will cover the area from (start angle) to ((start angle) + (span angle))
// return: this beam's start angle 
int Beam::getStartAngle(){
    return this->startAngle;
}

// get this beam's length(strength)
// the beam will cover the area from cell center to beam length(associate with strength)
// return: this beam's length
int Beam::getLengthBeam(){
    return this->lengthBeam;
}

// get this beam's cell index
// return: this beam's cell index
int Beam::getCellIndex(){
    return this->cellIndex;
}

// draw beam
// painter: QPainter for drawing
void Beam::drawBeam(QPainter &painter){
    painter.drawPie(x - lengthBeam / 2, 
            y - lengthBeam / 2,
            lengthBeam,
            lengthBeam,
            startAngle * 16,
            spanAngle * 16);
}

