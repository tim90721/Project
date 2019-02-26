#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "general_definition.h"
#include "RAOtestPrachConfig16.cpp"
#include "RAOtestPrachConfig27.cpp"
#include "RAOtestPrachConfig101.cpp"
#include "RAOtestPrachConfig106.cpp"

//#include "../src/includefile.h"
//#include "../src/Model.h"
//#include "../src/Cell.h"
//#include "../src/MacroCell.h"
//#include "../src/UE.h"

//Cell *cell;
//UE *ue;

//void initialize(){
//    cell = new MacroCell(100, 100, 0, 4, Macro, 27);
//    cell->updateBeamsAngle(0, 0);
//    cell->findCellCoverAreaEquation();
//    printf("%f\n", cell->getBeamStartAngle());
//    ue = new UE(110, 90, 0);
//    cell->detectUE(ue);
//}
//
//void initialize(int prachConfigIndex, int msg1FDM, double ssbPerRAO){
//    initialize();
//    cell->setPrachConfigIndex(prachConfigIndex);
//    cell->setMsg1FDM(msg1FDM);
//    cell->setSSBPerRAO(ssbPerRAO);
//    printf("msg1FDM: %d\n", cell->getMsg1FDM());
//    printf("ssb-perRAO: %f\n", cell->getSSBPerRAO());
//}
//
//void destory(){
//    free(cell);
//    free(ue);
//}
//
//int getRound(int simulationTime, int associationFrame){
//    int round = simulationTime / (associationFrame * 10);
//    if(simulationTime % (associationFrame * 10) != 0)
//        round += 1;
//    printf("round: %d\n", round);
//    return round;
//}
//
//void validation(vector<vector<int>>& expected, int simulationTime, int prachConfigIndex, int msg1FDM, double ssbPerRAO){
//    for(int i = 0;i < simulationTime;i++){
//        printf("===================info===================\n");
//        cell->broadcastSI();
//        ue->doRA();
//        vector<int>& raos = ue->getRAOs();
//        vector<int> expect = expected[i];
//        printf("%d\n", i);
//        if(raos.size() != expect.size()){
//            printf("test case: \n");
//            printf("prachConfigIndex: %d\nmsg1FDM: %d\nSSBPerRAO: %f\n", 
//                    prachConfigIndex, 
//                    msg1FDM,
//                    ssbPerRAO);
//            printf("test failed\n");
//            printf("ue raos size: %lu, expect raos size: %lu\n",
//                    raos.size(),
//                    expect.size());
//            abort();
//        }
//        //assert(raos.size() == expect.size());
//        for(unsigned int j = 0;j < raos.size();j++){
//            printf("%d, %d\n", raos[j], expect[j]);
//            assert(raos[j] == expect[j]);
//            if(raos.size() != expect.size()){
//                printf("test case: \n");
//                printf("prachConfigIndex: %d\nmsg1FDM: %d\nSSBPerRAO: %f\n", 
//                        prachConfigIndex, 
//                        msg1FDM,
//                        ssbPerRAO);
//                printf("test failed\n");
//                printf("ue rao: %d, expect rao: %d\n",
//                        raos[j],
//                        expect[j]);
//                abort();
//            }
//        }
//        cell->updateSubframe();
//        printf("===================info===================\n");
//    }
//}
//
//void printExpects(vector<vector<int>>& expected){
//    vector<int> temp;
//    for(unsigned int i = 0;i < expected.size();i++){
//        temp = expected[i];
//        for(unsigned int j = 0;j < temp.size();j++){
//            printf("%d\t%d\n", i, temp[j]);
//        }
//    }
//}

//void testPrachIndex27_17(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 8;
//    double ssbPerRAO = 1.0 / 4.0;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        for(int k = 0;k < 10;k++){
//            subframeExpect = new vector<int>;
//            subframeExpect->push_back(4);
//            subframeExpect->push_back(5);
//            subframeExpect->push_back(6);
//            subframeExpect->push_back(7);
//            expected.push_back(*subframeExpect);
//            j++;
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            j++;
//        }
//        if(j >= simulationTime)
//            break;
//    }
//    printExpects(expected);
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_16(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 8;
//    double ssbPerRAO = 1.0 / 2.0;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        for(int k = 0;k < 10;k++){
//            subframeExpect = new vector<int>;
//            subframeExpect->push_back(2);
//            subframeExpect->push_back(3);
//            expected.push_back(*subframeExpect);
//            j++;
//        }
//        if(j >= simulationTime)
//            break;
//    }
//    printExpects(expected);
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_15(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 4;
//    double ssbPerRAO = 1.0 / 2.0;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        for(int k = 0;k < 5;k++){
//            subframeExpect = new vector<int>;
//            subframeExpect->push_back(2);
//            subframeExpect->push_back(3);
//            expected.push_back(*subframeExpect);
//            j++;
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            //printf("%d\t%d\n", j, j %(associationFrame * 10));
//            j++;
//        }
//        if(j >= simulationTime)
//            break;
//    }
//    printExpects(expected);
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_14(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 2;
//    double ssbPerRAO = 1.0 / 2.0;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        while(j % (associationFrame * 10) < 1){
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            //printf("%d\t%d\n", j, j %(associationFrame * 10));
//            j++;
//        }
//        subframeExpect = new vector<int>;
//        subframeExpect->push_back(2);
//        subframeExpect->push_back(3);
//        expected.push_back(*subframeExpect);
//        j++;
//        while(j % (associationFrame * 10) < 5){
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            //printf("%d\t%d\n", j, j %(associationFrame * 10));
//            j++;
//        }
//        subframeExpect = new vector<int>;
//        subframeExpect->push_back(2);
//        subframeExpect->push_back(3);
//        expected.push_back(*subframeExpect);
//        j++;
//        while(j % (associationFrame * 10) != 0){
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            j++;
//            if(j >= simulationTime)
//                break;
//        }
//    }
//    printExpects(expected);
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_13(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 8;
//    double ssbPerRAO = 4;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        for(int k = 0;k < 10;k++){
//            subframeExpect = new vector<int>;
//            for(int l = 0;l < 8;l++){
//                subframeExpect->push_back(l);
//            }
//            expected.push_back(*subframeExpect);
//            j++;
//        }
//        if(j >= simulationTime)
//            break;
//    }
//    printExpects(expected);
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_12(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 4;
//    double ssbPerRAO = 4;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        for(int k = 0;k < 10;k++){
//            subframeExpect = new vector<int>;
//            subframeExpect->push_back(0);
//            subframeExpect->push_back(1);
//            subframeExpect->push_back(2);
//            subframeExpect->push_back(3);
//            expected.push_back(*subframeExpect);
//            j++;
//        }
//        if(j >= simulationTime)
//            break;
//    }
//    printExpects(expected);
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_11(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 2;
//    double ssbPerRAO = 4;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        for(int k = 0;k < 10;k++){
//            subframeExpect = new vector<int>;
//            subframeExpect->push_back(0);
//            subframeExpect->push_back(1);
//            expected.push_back(*subframeExpect);
//            j++;
//        }
//        if(j >= simulationTime)
//            break;
//    }
//    printExpects(expected);
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_10(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 1;
//    double ssbPerRAO = 4;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        for(int k = 0;k < 10;k++){
//            subframeExpect = new vector<int>;
//            subframeExpect->push_back(0);
//            expected.push_back(*subframeExpect);
//            j++;
//        }
//        if(j >= simulationTime)
//            break;
//    }
//    printExpects(expected);
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_9(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 1;
//    double ssbPerRAO = 2;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        for(int k = 0;k < 5;k++){
//            subframeExpect = new vector<int>;
//            subframeExpect->push_back(0);
//            expected.push_back(*subframeExpect);
//            j++;
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            j++;
//        }
//        if(j >= simulationTime)
//            break;
//    }
//    printExpects(expected);
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_7(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 1;
//    double ssbPerRAO = 1.0 / 8.0;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 4;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        while(j % (associationFrame * 10) < 8){
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            //printf("%d\t%d\n", j, j %(associationFrame * 10));
//            j++;
//        }
//        for(int k = 8;k < 16;k++){
//            subframeExpect = new vector<int>;
//            subframeExpect->push_back(k);
//            expected.push_back(*subframeExpect);
//            j++;
//        }
//        while(j % (associationFrame * 10) != 0){
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            j++;
//            if(j >= simulationTime)
//                break;
//        }
//    }
//    printExpects(expected);
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_6(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 1;
//    double ssbPerRAO = 1.0 / 4.0;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 2;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        while(j % (associationFrame * 10) < 4){
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            //printf("%d\t%d\n", j, j %(associationFrame * 10));
//            j++;
//        }
//        for(int k = 4;k < 8;k++){
//            subframeExpect = new vector<int>;
//            subframeExpect->push_back(k);
//            expected.push_back(*subframeExpect);
//            j++;
//        }
//        while(j % (associationFrame * 10) != 0){
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            j++;
//            if(j >= simulationTime)
//                break;
//        }
//    }
//    printExpects(expected);
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_5(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 1;
//    double ssbPerRAO = 1.0 / 2.0;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        while(j % (associationFrame * 10) < 2){
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            //printf("%d\t%d\n", j, j %(associationFrame * 10));
//            j++;
//        }
//        subframeExpect = new vector<int>;
//        subframeExpect->push_back(2);
//        expected.push_back(*subframeExpect);
//        j++;
//        subframeExpect = new vector<int>;
//        subframeExpect->push_back(3);
//        expected.push_back(*subframeExpect);
//        j++;
//        while(j % (associationFrame * 10) != 0){
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            j++;
//            if(j >= simulationTime)
//                break;
//        }
//    }
//    printExpects(expected);
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_4(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 8;
//    double ssbPerRAO = 1;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        for(int j = 0;j < 10;j++){
//            subframeExpect = new vector<int>;
//            subframeExpect->push_back(1);
//            subframeExpect->push_back(5);
//            expected.push_back(*subframeExpect);
//            //printf("%d\t%d\n", j, j %(associationFrame * 10));
//        }
//        if(j >= simulationTime)
//            break;
//    }
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_3(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 4;
//    double ssbPerRAO = 1;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        for(int j = 0;j < 10;j++){
//            subframeExpect = new vector<int>;
//            subframeExpect->push_back(1);
//            expected.push_back(*subframeExpect);
//            //printf("%d\t%d\n", j, j %(associationFrame * 10));
//        }
//        if(j >= simulationTime)
//            break;
//    }
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_2(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 2;
//    double ssbPerRAO = 1;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        for(int k = 0;k < 5;k++){
//            subframeExpect = new vector<int>;
//            subframeExpect->push_back(1);
//            expected.push_back(*subframeExpect);
//            j++;
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            //printf("%d\t%d\n", j, j %(associationFrame * 10));
//            j++;
//        }
//        if(j >= simulationTime)
//            break;
//    }
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}
//
//void testPrachIndex27_1(){
//    int prachConfigIndex = 27;
//    int msg1FDM = 1;
//    double ssbPerRAO = 1;
//    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
//
//    int simulationTime = 100;
//    int associationFrame = 1;
//    
//    vector<vector<int>> expected;
//    int round = getRound(simulationTime, associationFrame);
//    vector<int> *subframeExpect;
//    for(int i = 0;i < round;i++){
//        int j = i * associationFrame * 10;
//        
//        while(j % (associationFrame * 10) < 1){
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            //printf("%d\t%d\n", j, j %(associationFrame * 10));
//            j++;
//        }
//        subframeExpect = new vector<int>;
//        subframeExpect->push_back(1);
//        expected.push_back(*subframeExpect);
//        j++;
//        while(j % (associationFrame * 10) < 5){
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            //printf("%d\t%d\n", j, j %(associationFrame * 10));
//            j++;
//        }
//        subframeExpect = new vector<int>;
//        subframeExpect->push_back(1);
//        expected.push_back(*subframeExpect);
//        j++;
//        while(j % (associationFrame * 10) != 0){
//            subframeExpect = new vector<int>;
//            expected.push_back(*subframeExpect);
//            j++;
//            if(j >= simulationTime)
//                break;
//        }
//    }
//    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
//    destory();
//}

int main(){
    testPrachIndex16();
    testPrachIndex27();
    testPrachIndex101();
    testPrachIndex106();
    printf("test correct\n");
    return 0;
}


