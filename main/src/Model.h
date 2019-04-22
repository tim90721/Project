#ifndef MODEL
#define MODEL

#include "includefile.h"
#include "IPaintSubject.h"
#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <stdlib.h>

#include "Cell.h"
#include "MacroCell.h"
#include "FemtoCell.h"
#include "UE.h"
#include "CommonMath.h"
#include "include_log.h"

#include "EraseRect.h"

namespace DrawMode{
    enum Mode{
        DrawCell,
        EraseCell
    };
};

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
        unsigned int getFR();
        void notifyAll();
        void registerPaintObservor(IPaintObservor *observor);
        void traverseUEs();
        void transmitDL();
        void transmitUL();
        void startSimulation();
        void setSimulationTime(int simulationTime);
        void setnBeams(const int nBeams);
        void setCellType(const celltype::CellType type);
        void setFR(const unsigned int FR);
        void setArrivalRate(const unsigned int arrivalRate);
        void setPrachConfigIndex(std::string s);
        void setDrawMode(DrawMode::Mode mode);
        void setNPreambles(const int nPreambles);
        void setPreambleSCS(const double preambleSCS);
        void setCellBW(const int cellBW);
        ~Model();
    private:
        void run(bool isTimesUp);
        void generateRandomUEs();
        void recordUELatency(UE *ue);
        void recordCellsInfo();
        void initializeOutFiles();
        void closeOutFiles();
        void plotResult();
        void restoreCells2Initial();
        void drawing(QPainter &painter);
        void erasing(QPainter &painter);
        void detectCellInEraseArea();

        unsigned long ueIndex;
        int remainingUEs;
        int cellIndex;
        int ueArrivalRate;
        int mouseX;
        int mouseY;
        int prachConfigIndex;
        vector<Cell*> cells;
        vector<UE*> UEs;
        vector<IPaintObservor*> observors;
        Cell *tempCell;
        UE *ue;
        EraseRect eraseRect;
        celltype::CellType cellType;
        bool mousePressed;
        int countPressedReleased;
        int simulationTime;
        int simulationCounter;
        int nBeams;
        int nPreambles;
        int cellBW;
        double preambleSCS;
        std::string outputFolderName;
        std::string outputFileExtension;
        std::string outputFileUE;
        std::string outputFileCell;
        std::string filenameUE;
        std::string filenameCell;
        unsigned int FR;
        ofstream outFileUE;
        ofstream outFileCell;
        std::string curTime;
        DrawMode::Mode mode;
};
#endif
