#include "Beam.h"

// constructor
// x: x position of cell center
// y: y position of cell center
// beamIndex: beam index
// lengthBeam: the beam length(strength), corresponding to Cell supportDistance member
// spanAngle: each beam's area(in form of angle) in a cell
Beam::Beam(Cell *parent, int cellIndex, int beamIndex, int lengthBeam, double spanAngle){
    this->parent = parent;
    //setXY(x, y);
    setCellIndex(cellIndex);
    setBeamIndex(beamIndex);
    setLengthBeam(lengthBeam);
    setSpanAngle(spanAngle);
    setStartAngle(beamIndex, spanAngle);
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
void Beam::setSpanAngle(double spanAngle){
    this->spanAngle = spanAngle;
}

// set this beam's start angle
// beam will draw from (start angle) to ((start angle) + (span angle))
// beamIndex: the index of this beam
// spanAngle: the angle covered by this beam
void Beam::setStartAngle(int beamIndex, double spanAngle){
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

// detect UE is in this beam's area
void Beam::detectUE(UE *ue, double power){
    //printf("cell %d beam %d startAngle: %f, spanAngle: %f\n",
    //        cellIndex,
    //        beamIndex,
    //        startAngle,
    //        spanAngle);
    if(isInArea(ue->getX(), ue->getY(),
                getX(), getY(),
                startAngle,
                spanAngle,
                lengthBeam / 2)){
        printf("UE id %lu is in cell index %d beam index %d\n",
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
double Beam::getSpanAngle(){
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
void Beam::draw(QPainter &painter){
    painter.drawPie(getX() - lengthBeam / 2, 
            getY() - lengthBeam / 2,
            lengthBeam,
            lengthBeam,
            startAngle * 16,
            spanAngle * 16);
}

// destructor
Beam::~Beam(){
    printf("beam destructor\n");
}
