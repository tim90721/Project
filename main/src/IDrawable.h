#ifndef IDRAWABLE
#define IDRAWABLE
#include <QPainter>

class IDrawable{
    public:
        virtual void draw(QPainter& painter) = 0;
};
#endif
