#include "MacroCell.h"

// Constructor
// initialize macro cell
// x: gNB x position
// y: gNB y position
// cellType: gNB CellType, Macro or Femto //FIXME maybe reduntant
MacroCell::MacroCell(int x, int y, int nBeams, CellType cellType):Cell(x, y, nBeams, cellType){
    setCellSupportDistance(200);
    initializeBeams(getnBeams());
}

// Draw Macro Cell
// painter: QPainter use for painting
void MacroCell::drawCell(QPainter &painter){
    painter.setBrush(QBrush(QColor(0, 0, 0, 255), Qt::SolidPattern));
    painter.drawEllipse(x + 200 / 2 - 5 - 100, y + 200 / 2 - 5 - 100, 10, 10);
    painter.setBrush(QBrush(QColor(128, 128, 255, 64), Qt::SolidPattern));

    Beam *beam;
    for(int i = 0;(int)i < beams.size();i++){
        beam = beams.at(i);
        beam->drawBeam(painter);
    }
}

// initialize gNB's beams
void MacroCell::initializeBeams(int nBeams){
    int spanAngle = cellAngle / nBeams;
    for(int i = 0;i < nBeams;i++){
        Beam *beam = new Beam(this->x, this->y, i + 1, cellSupportDistance, spanAngle);
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
    int spanAngle = cellAngle / getnBeams(); 
    for(unsigned int i = 0;i < beams.size();i++){
        beam = beams.at(i);
        beam->setStartAngle(beamStartAngle + i * spanAngle);
    } 
}
