#ifndef CELL
#define CELL

#include <QPainter>
#include "includefile.h"
#include "Beam.h"
#include "UE.h"
#include "CommonMath.h"
//#include "PRACHConfig.h"
#include "PRACHConfigFR1Paired.h"
#include "AvailiableRAO.h"

enum CellType{
    Macro,
    Femto
};

class Beam;
class UE;

class Cell{
    public:
        Cell(int x, int y,int cellIndex, int nBeams, CellType cellType, int prachConfigIndex);
        virtual void drawCell(QPainter &painter) = 0;
        void setCellType(CellType cellType);
        void setX(int x);
        void setY(int y);
        void setnBeams(int nBeams);
        void setCellSupportDistance(int supportDistance);
        void setBeamStartAngle(int diffX, int diffY);
        void setCellIndex(int cellIndex);
        void findCellCoverAreaEquation();
        void detectUE(UE *ue);
        void broadcastSI();
        void updateSubframe();
        void resetFrame();
        virtual void initializeBeams(int nBeams) = 0;
        virtual void updateBeamsAngle(int diffX, int diffY) = 0;
        int getX();
        int getY();
        int getnBeams();
        int getCellSupportDistance();
        double getBeamStartAngle();
        int getCellIndex();
        int getSubframeIndex();
        int getFrameIndex();
        CellType getCellType();
        IPRACHConfig *getPRACHConfig();
        IAvailiableRAO *getAvailiableRAO();
    protected:
        int x;
        int y;
        int cellIndex;
        int cellSupportDistance;
        int nBeams;
        int cellPixelSize;
        int cellAngle;
        int startAngle;
        int endAngle;
        int subframeIndex;
        int frameIndex;
        double beamStartAngle;
        double startB;
        double startC;
        double endB;
        double endC;
        CellType cellType;
        vector<Beam*> beams;
        vector<UE*> ues;
        PRACHConfig *prachConfig;
        AvailiableRAO *availiableRAO;
    private:
        bool checkUEisExist(UE *ue);

};

#endif
