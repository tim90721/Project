#ifndef MODEL
#define MODEL

#include "includefile.h"
#include "IPaintSubject.h"
#include <stdio.h>
#include <chrono>
#include <thread>

#include "Cell.h"
#include "MacroCell.h"
#include "UE.h"
#include "CommonMath.h"

class Model : public IPaintSubject{
    public:
        Model();
        void draw(QPainter &painter);
        void drawCell(QPainter &painter);
        void drawUE(QPainter &painter);
        void setMouseXY(int x, int y);
        int getMouseX();
        int getMouseY();
        void setMousePressed(bool isPressed);
        bool isMousePressed();
        int getPressedCount();
        void notifyAll();
        void registerPaintObservor(IPaintObservor *observor);
        void traverseUEs();
        void transmitDL();
        void transmitUL();
        void startSimulation();
        void setSimulationTime(int simulationTime);
    private:
        void run(bool isTimesUp);
        void generateRandomUEs();

        unsigned long ueIndex;
        int cellIndex;
        int ueArrivalRate;
        int mouseX;
        int mouseY;
        vector<Cell*> cells;
        vector<UE*> UEs;
        vector<IPaintObservor*> observors;
        Cell *tempCell;
        UE *ue;
        CellType cellType;
        bool mousePressed;
        int countPressedReleased;
        int simulationTime;
        int simulationCounter;
        int remainingUEs;
};
        
#endif
