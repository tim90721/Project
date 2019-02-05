#ifndef MODEL
#define MODEL

#include "includefile.h"
#include "IPaintSubject.h"
#include <stdio.h>

#include "Cell.h"
#include "MacroCell.h"
#include "UE.h"

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
        void startSimulation();
    private:
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
};
        
#endif
