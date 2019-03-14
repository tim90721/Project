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
#include "random_access.h"
#include "IDrawable.h"

namespace celltype{
    enum CellType{
        Macro,
        Femto
    };
}

class Beam;
class UE;

class Cell : public IDrawable{
    public:
        Cell(int x, int y,int cellIndex, int nBeams, celltype::CellType cellType, int prachConfigIndex);
        virtual void draw(QPainter &painter) = 0;
        void setCellType(celltype::CellType cellType);
        void setX(int x);
        void setY(int y);
        void setnBeams(int nBeams);
        void setCellSupportDistance(int supportDistance);
        void setBeamStartAngle(int diffX, int diffY);
        void setCellIndex(int cellIndex);
        void detectUE(UE *ue);
        void broadcastSI();
        void deregisterCell(UE *ue);
        void updateSubframe();
        void resetFrame();
        void setMsg1FDM(int msg1FDM);
        void setSSBPerRAO(double ssbPerRAO);
        void setPrachConfigIndex(int prachConfigIndex);
        void setRaResponseWindow(const int raResponseWindw);
        void receivePreamble(const int raoIndex, const int preambleIndex);
        void transmitRAR();
        void receiveMsg3(Msg3& msg3);
        void transmitCR();
        virtual void initializeBeams() = 0;
        virtual void updateBeamsAngle(int diffX, int diffY) = 0;
        int getX();
        int getY();
        int getnBeams();
        int getCellSupportDistance();
        int getCellIndex();
        int getSubframeIndex();
        int getFrameIndex();
        int getMsg1FDM();
        int getRaResponseWindow();
        double getBeamStartAngle();
        double getSSBPerRAO();
        double getCellSpanAngle();
        bool hasRAR();
        celltype::CellType getCellType();
        IPRACHConfig *getPRACHConfig();
        IAvailiableRAO *getAvailiableRAO();
    protected:
        int x;
        int y;
        int cellIndex;
        int cellSupportDistance;
        int nBeams;
        int cellPixelSize;
        int subframeIndex;
        int frameIndex;
        int raResponseWindow;
        double cellAngle;
        double startAngle;
        double endAngle;
        double beamStartAngle;
        celltype::CellType cellType;
        vector<Beam*> beams;
        vector<UE*> ues;
        vector<vector<RAR*>> rars;
        vector<Msg3*> msg3s;
        PRACHConfig *prachConfig;
        AvailiableRAO *availiableRAO;
    private:
        bool checkUEisExist(UE *ue);

};

#endif
