#include "MacroCell.h"

// Constructor
// initialize macro cell
// x: gNB x position
// y: gNB y position
// cellType: gNB CellType, Macro or Femto //FIXME maybe reduntant
MacroCell::MacroCell(int x, int y, int cellIndex, int nBeams, CellType cellType):Cell(x, y, cellIndex, nBeams, cellType){
    this->cellAngle = 120;
    setCellSupportDistance(200);
    initializeBeams(getnBeams());
}

// Draw Macro Cell
// painter: QPainter use for painting
void MacroCell::drawCell(QPainter &painter){
    painter.setBrush(QBrush(QColor(0, 0, 0, 255), Qt::SolidPattern));
    painter.drawEllipse(x - cellPixelSize / 2,
            y - cellPixelSize / 2,
            cellPixelSize, 
            cellPixelSize);
    painter.setBrush(QBrush(QColor(128, 128, 255, 32), Qt::SolidPattern));

    Beam *beam;
    for(unsigned int i = 0;i < beams.size();i++){
        beam = beams.at(i);
        beam->drawBeam(painter);
    }
    //int y1 = XgetY(0, this->startB, this->startC);
    //int y2 = XgetY(150, this->startB, this->startC);
    //painter.drawLine(this->x, this->y - y1, this->x + 150, this->y - y2);
    //y1 = XgetY(0, this->endB, this->endC);
    //y2 = XgetY(150, this->endB, this->endC);
    //painter.drawLine(this->x, this->y - y1, this->x + 150, this->y - y2);
}

// initialize gNB's beams
void MacroCell::initializeBeams(int nBeams){
    int spanAngle = cellAngle / nBeams;
    for(int i = 0;i < nBeams;i++){
        Beam *beam = new Beam(this, cellIndex, i + 1, cellSupportDistance, spanAngle);
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
