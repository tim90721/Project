#include <stdio.h>
#include "../src/includefile.h"
#include "../src/Model.h"
#include "../src/Cell.h"
#include "../src/MacroCell.h"
#include "../src/UE.h"

Cell *cell;
UE *ue;

void initialize(){
    cell = new MacroCell(100, 100, 0, 4, Macro, 27);
    cell->updateBeamsAngle(0, 0);
    cell->findCellCoverAreaEquation();
    printf("%f\n", cell->getBeamStartAngle());
    ue = new UE(110, 90, 0);
    cell->detectUE(ue);
}

void test1(){
    initialize();
    cell->setPrachConfigIndex(16);
    printf("msg1FDM: %d\n", cell->getMsg1FDM());
    printf("ssb-perRAO: %f\n", cell->getSSBPerRAO());
    cell->broadcastSI();
    int simulationTime = 60;
    for(int i = 0;i < simulationTime;i++){
        printf("===================info===================\n");
        cell->broadcastSI();
        ue->doRA();
        cell->updateSubframe();
        printf("===================info===================\n");
    }
}

int main(){
    test1();
    return 0;
}


