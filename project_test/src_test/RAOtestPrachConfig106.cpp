#ifndef PRACH_INDEX_106_TEST
#define PRACH_INDEX_106_TEST

#include "general_definition.h"

extern Cell *cell;
extern UE *ue;

void testPrachIndex106_4(){
    int prachConfigIndex = 106;
    int msg1FDM = 8;
    double ssbPerRAO = 1;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int l = 0;l < 10;l++){
            subframeExpect = new vector<int>;
            for(int k = 0;k < 24;k++){
                subframeExpect->push_back(1 + k * 4);
            } 
            expected.push_back(*subframeExpect);
            j++;
        }
        while(j % (associationFrame * 10) != 0){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
            if(j >= simulationTime)
                break;
        }
    }
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex106_3(){
    int prachConfigIndex = 106;
    int msg1FDM = 4;
    double ssbPerRAO = 1;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int l = 0;l < 10;l++){
            subframeExpect = new vector<int>;
            for(int k = 0;k < 12;k++){
                subframeExpect->push_back(1 + k * 4);
            } 
            expected.push_back(*subframeExpect);
            j++;
        }
        while(j % (associationFrame * 10) != 0){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
            if(j >= simulationTime)
                break;
        }
    }
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex106_2(){
    int prachConfigIndex = 106;
    int msg1FDM = 2;
    double ssbPerRAO = 1;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int l = 0;l < 10;l++){
            subframeExpect = new vector<int>;
            for(int k = 0;k < 6;k++){
                subframeExpect->push_back(1 + k * 4);
            } 
            expected.push_back(*subframeExpect);
            j++;
        }
        while(j % (associationFrame * 10) != 0){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
            if(j >= simulationTime)
                break;
        }
    }
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex106_1(){
    int prachConfigIndex = 106;
    int msg1FDM = 1;
    double ssbPerRAO = 1;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int l = 0;l < 10;l++){
            subframeExpect = new vector<int>;
            for(int k = 0;k < 3;k++){
                subframeExpect->push_back(1 + k * 4);
            } 
            expected.push_back(*subframeExpect);
            j++;
        }
        while(j % (associationFrame * 10) != 0){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
            if(j >= simulationTime)
                break;
        }
    }
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex106(){
    testPrachIndex106_1();
    testPrachIndex106_2();
    testPrachIndex106_3();
    testPrachIndex106_4();
}
#endif
