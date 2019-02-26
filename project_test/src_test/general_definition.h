#ifndef GENERAL_TEST_DEF
#define GENERAL_TEST_DEF
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>

#include "../src/includefile.h"
#include "../src/Model.h"
#include "../src/Cell.h"
#include "../src/MacroCell.h"
#include "../src/UE.h"

extern Cell *cell = NULL;
extern UE *ue = NULL;

void initialize(){
    cell = new MacroCell(100, 100, 0, 4, Macro, 27);
    cell->updateBeamsAngle(0, 0);
    cell->findCellCoverAreaEquation();
    printf("%f\n", cell->getBeamStartAngle());
    ue = new UE(110, 90, 0);
    cell->detectUE(ue);
}

void initialize(int prachConfigIndex, int msg1FDM, double ssbPerRAO){
    initialize();
    cell->setPrachConfigIndex(prachConfigIndex);
    cell->setMsg1FDM(msg1FDM);
    cell->setSSBPerRAO(ssbPerRAO);
    printf("msg1FDM: %d\n", cell->getMsg1FDM());
    printf("ssb-perRAO: %f\n", cell->getSSBPerRAO());
}

void destory(){
    free(cell);
    free(ue);
}

int getRound(int simulationTime, int associationFrame){
    int round = simulationTime / (associationFrame * 10);
    if(simulationTime % (associationFrame * 10) != 0)
        round += 1;
    printf("round: %d\n", round);
    return round;
}

void validation(vector<vector<int>>& expected, int simulationTime, int prachConfigIndex, int msg1FDM, double ssbPerRAO){
    for(int i = 0;i < simulationTime;i++){
        printf("===================info===================\n");
        cell->broadcastSI();
        ue->doRA();
        vector<int>& raos = ue->getRAOs();
        vector<int> expect = expected[i];
        printf("%d\n", i);
        if(raos.size() != expect.size()){
            printf("test case: \n");
            printf("prachConfigIndex: %d\nmsg1FDM: %d\nSSBPerRAO: %f\n", 
                    prachConfigIndex, 
                    msg1FDM,
                    ssbPerRAO);
            printf("test failed\n");
            printf("ue raos size: %lu, expect raos size: %lu\n",
                    raos.size(),
                    expect.size());
            abort();
        }
        //assert(raos.size() == expect.size());
        for(unsigned int j = 0;j < raos.size();j++){
            printf("%d, %d\n", raos[j], expect[j]);
            //assert(raos[j] == expect[j]);
            if(raos[j] != expect[j]){
                printf("test case: \n");
                printf("prachConfigIndex: %d\nmsg1FDM: %d\nSSBPerRAO: %f\n", 
                        prachConfigIndex, 
                        msg1FDM,
                        ssbPerRAO);
                printf("test failed\n");
                printf("ue rao: %d, expect rao: %d\n",
                        raos[j],
                        expect[j]);
                abort();
            }
        }
        cell->updateSubframe();
        printf("===================info===================\n");
    }
}

void printExpects(vector<vector<int>>& expected){
    vector<int> temp;
    for(unsigned int i = 0;i < expected.size();i++){
        temp = expected[i];
        for(unsigned int j = 0;j < temp.size();j++){
            printf("%d\t%d\n", i, temp[j]);
        }
    }
}
#endif
