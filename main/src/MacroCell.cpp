#include "MacroCell.h"

// Constructor
// initialize macro cell
// x: gNB x position
// y: gNB y position
// cellType: gNB CellType, Macro or Femto //FIXME maybe reduntant
MacroCell::MacroCell(int x, int y, int cellIndex, int nBeams, celltype::CellType cellType, int prachConfigIndex):Cell(x, y, cellIndex, nBeams, cellType, prachConfigIndex){
    this->cellAngle = 120;
    this->cellSupportDistance = 300;
}

// Draw Macro Cell
// painter: QPainter use for painting
void MacroCell::draw(QPainter &painter){
    painter.setBrush(QBrush(QColor(0, 0, 0, 255), Qt::SolidPattern));
    painter.drawEllipse(x - cellPixelSize / 2,
            y - cellPixelSize / 2,
            cellPixelSize, 
            cellPixelSize);
    painter.setBrush(QBrush(QColor(128, 128, 255, 32), Qt::SolidPattern));

    Beam *beam;
    for(unsigned int i = 0;i < beams.size();i++){
        beam = beams.at(i);
        beam->draw(painter);
    }
}

// initialize gNB's beams
// nBeams: number of beams
void MacroCell::initializeBeams(){
    double spanAngle = (double)cellAngle / (double)nBeams;
    for(int i = 0;i < nBeams;i++){
        Beam *beam = new Beam(this, cellIndex, i, cellSupportDistance, spanAngle);
        beams.push_back(beam); 
    }
}

// calculate beam start angle based on first mouse click coordinate and
// second mouse click coordinate
// diffX: the difference of x1 and x2
// diffY: the difference of y1 and y2
void MacroCell::updateBeamsAngle(int diffX, int diffY){
    Cell::setBeamStartAngle(diffX, diffY);
    Beam *beam;
    double spanAngle = cellAngle / getnBeams(); 
    for(unsigned int i = 0;i < beams.size();i++){
        beam = beams.at(i);
        beam->setStartAngle(beamStartAngle + i * spanAngle);
    } 
    startAngle = beams[0]->getStartAngle();
}


// destructor
MacroCell::~MacroCell(){
    SPDLOG_TRACE("Macro cell destructor");
    for(auto it = beams.begin();it != beams.end();it++){
        delete (*it);
    }
}
