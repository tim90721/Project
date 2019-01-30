#ifndef UE_DEFINE
#define UE_DEFINE

#include <QPainter>

class UE{
    public:
        UE(int x, int y);
        void setXY(int x, int y);
        void setBeam(int cellIndex, int beamIndex, int beamStrength);
        int getX();
        int getY();
        int getBeamIndex();
        int getCellIndex();
        int getBeamStrength();
        void drawUE(QPainter &painter);
    private:
        int x;
        int y;
        int beamIndex;
        int cellIndex;
        int beamStrength;
        int UEPixelSize;
};
#endif