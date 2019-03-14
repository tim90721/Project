#ifndef UE_DEFINE
#define UE_DEFINE

#include <QPainter>
#include <random>
#include "Beam.h"
#include "Cell.h"
#include "IPRACHConfig.h"
#include "IAvailiableRAO.h"
#include "includefile.h"
#include "CommonMath.h"
#include "random_access.h"

class Cell;

class UE{
    public:
        UE(int x, int y, unsigned long id);
        UE(int x, int y, unsigned long id, bool isTest);
        void setXY(int x, int y);
        void setBeam(int cellIndex, int beamIndex, int beamStrength);
        int receiveSI(Cell *beam);
        void doRA();
        void receiveRAR(const std::vector<RAR*>& rars, const int cellIndex);
        void receiveCR(const std::vector<Msg3*>& CRs, const int cellIndex);
        unsigned long getID();
        int getX();
        int getY();
        int getBeamIndex();
        int getCellIndex();
        int getBeamStrength();
        bool isBindCell();
        bool isPreambleTransmit();
        bool isRarReceived();
        bool isRASuccess();
        void drawUE(QPainter &painter);
        std::vector<int>& getRAOs();
    private:
        void checkRA();
        void updateRAOforRA();
        void updateRAOforRA(const int startRAO, const int endRAO, const int subframeStartRAO, const int subframeEndRAO, const int totalNeedRAO);
        void storeRAOsforRA(int subframeStartRAO, int subframeEndRAO);
        void transmitMsg1();
        void transmitMsg3();
        unsigned long id;
        int x;
        int y;
        int beamIndex;
        int cellIndex;
        int beamStrength;
        int UEPixelSize;
        int startRAO;
        int endRAO;
        int raStartRAO;
        int raEndRAO;
        int selectRAOIndex;
        int selectPreambleIndex;
        int uplinkResourceIndex;
        int tc_rnti;
        bool preambleTransmitted;
        bool rarReceived;
        bool msg3Transmitted;
        bool raSuccess;
        bool collided;
        bool isTest;
        Cell *candidateCell;
        IPRACHConfig *prachConfig;
        IAvailiableRAO *availiableRAO;
        std::vector<int> raos;
};
#endif
