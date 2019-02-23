#include "Beam.h"

// constructor
// x: x position of cell center
// y: y position of cell center
// beamIndex: beam index
// lengthBeam: the beam length(strength), corresponding to Cell supportDistance member
// spanAngle: each beam's area(in form of angle) in a cell
Beam::Beam(Cell *parent, int cellIndex, int beamIndex, int lengthBeam, int spanAngle){
    this->parent = parent;
    //setXY(x, y);
    setCellIndex(cellIndex);
    setBeamIndex(beamIndex);
    setLengthBeam(lengthBeam);
    setSpanAngle(spanAngle);
    setStartAngle(beamIndex, spanAngle);
}

// set beam's x position
// x: x position of cell center
//void Beam::setX(int x){
//    this->x = x;
//}

// set beam's y position
// y: y position of cell center
//void Beam::setY(int y){
//    this->y = y;
//}

// set beam's x and y position
// x: x position of cell center
// y: y position of cell center 
//void Beam::setXY(int x, int y){
//    this->x = x;
//    this->y = y;
//}

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
    this->startAngle = (beamIndex) * spanAngle;
}

// set this beam's start angle
// beam will draw from (start angle) to ((start angle) + (span angle))
// startAngle: the start drawing angle of this beam
void Beam::setStartAngle(double startAngle){
    if(startAngle < 0){
        startAngle += 360;
    }
    this->startAngle = startAngle;
}

// set this beam's cell index
// cellIndex: cell index
void Beam::setCellIndex(int cellIndex){
    this->cellIndex = cellIndex;
}

// find beam cover area equation
// B, C is the coefficient of linear function X + bY + C = 0
// startB, startC is the coefficient of beam start angle equation
// endB, endC is the coefficient of beam end angle equation
void Beam::findBeamCoverAreaEquation(){
    //startB = -1.0 * tan(startAngle);
    //startC = -1.0 * ((double)this->x + startB * (double)this->y);
    //endB = -1.0 * tan(startAngle + spanAngle);
    //endC = -1.0 * ((double)this->x + endB * (double)this->y);
    //printf("startAngle: %f\n", startAngle);
    startB = -1.0 * tan((-1.0) * (startAngle - 90) * (M_PI / 180));
    startC = 0;
    endB = -1.0 * tan((-1.0) * (startAngle + spanAngle - 90) * (M_PI / 180));
    endC = 0;
    //printf("%3.2f %3.2f %3.2f %3.2f\n", floor(startB), floor(startC), floor(endB), floor(endC));
    //printf("%3.2f %3.2f\n", floor(startAngle), floor(startAngle + spanAngle));
    //printf("%3d\n", getEndAngle());
}

// detect UE is in this beam's area
void Beam::detectUE(UE *ue, double power){
    if(isInArea(ue->getX() - getX(),
                getY() - ue->getY(),
                this->startAngle,
                getEndAngle(),
                this->startB,
                this->startC,
                this->endB,
                this->endC)){
        printf("UE id %d is in cell index %d beam index %d\n",
                ue->getID(),
                parent->getCellIndex(),
                getBeamIndex());
        ue->setBeam(this->cellIndex, this->beamIndex, power);
    }
}

// get this beam's x position
// return: this beam's x position, equals to x position of cell center
int Beam::getX(){
    return parent->getX();
}

// get this beam's y position
// return: this beam's y position, equals to y position of cell center
int Beam::getY(){
    return parent->getY();
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
double Beam::getStartAngle(){
    return this->startAngle;
}

// get this beam's end angle
// return: this beam's end angle(startAngle + spaneAngle)
int Beam::getEndAngle(){
    int endAngle = this->startAngle + this->spanAngle;
    return (endAngle > 360)?(endAngle - 360):(endAngle);
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
    painter.drawPie(getX() - lengthBeam / 2, 
            getY() - lengthBeam / 2,
            lengthBeam,
            lengthBeam,
            startAngle * 16,
            spanAngle * 16);
}

// get this beam's startB with linear equation x + By + C = 0
// return: coefficient B of start line
double Beam::getStartB(){
    return this->startB;
}

// get this beam's startC with linear equation x + By + C = 0
// return: coefficient C of start line
double Beam::getStartC(){
    return this->startC;
}

// get this beam's endB with linear equation x + By + C = 0
// return: coefficient B of end line
double Beam::getEndB(){
    return this->endB;
}

// get this beam's endC with linear equation x + By + C = 0
// return: coefficient C of end line
double Beam::getEndC(){
    return this->endC;
}
