#ifndef ERASE_RECT
#define ERASE_RECT

#include <QPainter>

#include "IDrawable.h"
#include "include_log.h"

class EraseRect : IDrawable{
    private:
        int x;
        int y;
        const int size = 50;
    public:
        EraseRect();
        ~EraseRect();
        void setXY(int x, int y);
        bool isInside(int objectX, int objectY);
        void draw(QPainter &painter);
};

#endif
