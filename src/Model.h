#ifndef MODEL
#define MODEL

#include "includefile.h"
//#include <QPainter>
#include "Cell.h"
#include "MacroCell.h"
#include "IPaintSubject.h"
#include <stdio.h>

using namespace std;

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
    private:
        int mouseX;
        int mouseY;
        vector<Cell*> cells;
        vector<IPaintObservor*> observors;
        Cell *tempCell;
        CellType cellType;
        bool mousePressed;
        int countPressedReleased;
};
        
#endif
