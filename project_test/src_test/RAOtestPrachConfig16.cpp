#ifndef PRACH_INDEX_16_TEST
#define PRACH_INDEX_16_TEST
#include "general_definition.h"

extern Cell* cell;
extern UE* ue;

void testPrachIndex16_8(){
    int prachConfigIndex = 16;
    int msg1FDM = 8;
    double ssbPerRAO = 1.0 / 16.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 8;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 21){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        for(int k = 16;k < 24;k++){
            subframeExpect->push_back(k);
        }
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 31){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        for(int k = 24;k < 32;k++){
            subframeExpect->push_back(k);
        }
        expected.push_back(*subframeExpect);
        j++;
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

void testPrachIndex16_7(){
    int prachConfigIndex = 16;
    int msg1FDM = 8;
    double ssbPerRAO = 1.0 / 4.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 2;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(4);
        subframeExpect->push_back(5);
        subframeExpect->push_back(6);
        subframeExpect->push_back(7);
        expected.push_back(*subframeExpect);
        j++;
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

void testPrachIndex16_6(){
    int prachConfigIndex = 16;
    int msg1FDM = 1;
    double ssbPerRAO = 1.0 / 4.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 16;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 41){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(4);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 51){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(5);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 61){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(6);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 71){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(7);
        expected.push_back(*subframeExpect);
        j++;
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

void testPrachIndex16_5(){
    int prachConfigIndex = 16;
    int msg1FDM = 1;
    double ssbPerRAO = 1.0 / 2.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 60;
    int associationFrame = 8;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 21){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(2);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 31){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(3);
        expected.push_back(*subframeExpect);
        j++;
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

void testPrachIndex16_4(){
    int prachConfigIndex = 16;
    int msg1FDM = 8;
    double ssbPerRAO = 1;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 60;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(1);
        subframeExpect->push_back(5);
        expected.push_back(*subframeExpect);
        j++;
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

void testPrachIndex16_3(){
    int prachConfigIndex = 16;
    int msg1FDM = 4;
    double ssbPerRAO = 1;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 60;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(1);
        expected.push_back(*subframeExpect);
        j++;
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

void testPrachIndex16_2(){
    int prachConfigIndex = 16;
    int msg1FDM = 2;
    double ssbPerRAO = 1;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);
    
    int simulationTime = 60;
    int associationFrame = 2;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(1);
        expected.push_back(*subframeExpect);
        j++;
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

void testPrachIndex16_1(){
    int prachConfigIndex = 16;
    int msg1FDM = 1;
    double ssbPerRAO = 1;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 60;
    int associationFrame = 4;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) <= 10){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(1);
        expected.push_back(*subframeExpect);
        j++;
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

void testPrachIndex16(){
    testPrachIndex16_1();
    testPrachIndex16_2();
    testPrachIndex16_3();
    testPrachIndex16_4();
    testPrachIndex16_5();
    testPrachIndex16_6();
    testPrachIndex16_7();
    testPrachIndex16_8();
}
#endif
