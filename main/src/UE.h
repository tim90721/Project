#ifndef UE_DEFINE
#define UE_DEFINE

#include <QPainter>
#include <random>
#include "include_log.h"
#include "Beam.h"
#include "Cell.h"
#include "IPRACHConfig.h"
#include "IAvailiableRAO.h"
#include "includefile.h"
#include "CommonMath.h"
#include "random_access.h"
#include "IDrawable.h"

class Cell;

class UE : public IDrawable{
    public:
        UE(int x, int y, unsigned long id);
        UE(int x, int y, unsigned long id, bool isTest);
        void setXY(int x, int y);
        void setBeam(int cellIndex, int beamIndex, int beamStrength);
        int receiveSI(Cell *beam);
        void doRA();
        void receiveRAR(const std::vector<RAR*>& rars, const int cellIndex);
        void setActiveTime(const int frameIndex, const int subframeIndex);
        unsigned long getID();
        int getX();
        int getY();
        int getBeamIndex();
        int getCellIndex();
        int getBeamStrength();
        int getActiveFrame();
        int getActiveSubframe();
        int getDepartedFrame();
        int getDepartedSubframe();
        int getRAFrame();
        int getRASubframe();
        int getRAMsg1FDM();
        int getSelectPreambleIndex();
        int getSelectRAOIndex();
        double getRASSBPerRAO();
        bool receiveCR(const std::vector<Msg3*>& CRs, const int cellIndex);
        bool isBindCell();
        bool isPreambleTransmit();
        bool isRarReceived();
        bool isMsg3Transmitted();
        bool isRASuccess();
        bool isCollided();
        void draw(QPainter &painter);
        std::vector<int>& getRAOs();
        ~UE();
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
        /////////// should modify to unsigned ///////////
        int beamStrength;
        int powerRamp;
        /////////// should modify to unsigned ///////////
        int UEPixelSize;
        int startRAO;
        int endRAO;
        int raStartRAO;
        int raEndRAO;
        int selectRAOIndex;
        int selectPreambleIndex;
        int uplinkResourceIndex;
        int tc_rnti;
        int activeFrame;
        int activeSubframe;
        int raFrame;
        int raSubframe;
        int msg3Frame;
        int msg3Subframe;
        int departedFrame;
        int departedSubframe;
        double raSSBPerRAO;
        int raMsg1FDM;
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
