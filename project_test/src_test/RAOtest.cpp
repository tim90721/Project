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
    cell->setMsg1FDM(1);
    cell->setSSBPerRAO(1);
    printf("msg1FDM: %d\n", cell->getMsg1FDM());
    printf("ssb-perRAO: %f\n", cell->getSSBPerRAO());
    cell->broadcastSI();

    int simulationTime = 60;
    vector<vector<int>> expected;
    int i = 0;
    vector<int> *subframeExpect;
    while(i < 11){
        subframeExpect = new vector<int>;
        expected.push_back(*subframeExpect);
        i++;
    }
    subframeExpect = new vector<int>;
    subframeExpect->push_back(1);
    expected.push_back(*subframeExpect);
    i++;
    while(i < 51){
        subframeExpect = new vector<int>;
        expected.push_back(*subframeExpect);
        i++;
    }
    subframeExpect = new vector<int>;
    subframeExpect->push_back(1);
    expected.push_back(*subframeExpect);
    i++;
    while(i < 60){
        subframeExpect = new vector<int>;
        expected.push_back(*subframeExpect);
        i++;
    }

    for(int i = 0;i < simulationTime;i++){
        printf("===================info===================\n");
        cell->broadcastSI();
        ue->doRA();
        vector<int>& raos = ue->getRAOs();
        vector<int> expect = expected[i];
        bool same = true;
        if(raos.size() == expect.size()){
            printf("same size\n");
            for(unsigned int j = 0;j < raos.size();j++){
                if(raos[j] == expect[j])
                    continue;
                else{
                    same = false;
                    break;
                }
            }
        }
        else
            same = false;
        if(same){
            printf("correct\n");
        }
        else{
            printf("%d\t%d\n", raos.size(), expect.size());
            printf("wrong\n");
            return;
        }
        
        cell->updateSubframe();
        printf("===================info===================\n");
    }
}

int main(){
    test1();
    return 0;
}


