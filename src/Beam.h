#ifndef BEAM
#define BEAM
#include <QPainter>

class Beam{
    private:
        int index;
        int spanAngle;
        int startAngle;
        int x;
        int y;
        int lengthBeam;
    public:
        Beam(int x, int y, int index, int lengthBeam, int spanAngle);
        void drawBeam(QPainter &painter);
        void setX(int x);
        void setY(int y);
        void setXY(int x, int y);
        void setBeamIndex(int index);
        void setSpanAngle(int spanAngle);
        void setStartAngle(int index, int spanAngle);
        void setStartAngle(int startAngle);
        void setLengthBeam(int lengthBeam);
        int getX();
        int getY();
        int getBeamIndex();
        int getSpanAngle();
        int getStartAngle();
        int getLengthBeam();
};
#endif
