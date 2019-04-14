#include "EraseRect.h"

EraseRect::EraseRect() : x(0), y(0){
}

EraseRect::~EraseRect(){
}

void EraseRect::setXY(int x, int y){
    this->x = x - size / 2;
    this->y = y - size / 2;
}

bool EraseRect::isInside(int objectX, int objectY){
    if((x <= objectX && y <= objectY)
            && ((x + size) >= objectX && (y + size) >= objectY))
        return true;
    return false;
}

void EraseRect::draw(QPainter &painter){
    painter.setBrush(QBrush(QColor(255, 255, 255, 255), Qt::SolidPattern));
    painter.drawRect(x, y, size, size);
}
