#ifndef PRACH_INDEX_19_TEST
#define PRACH_INDEX_19_TEST

#include "general_definition.h"

extern Cell* cell;
extern UE* ue;

void testPrachIndex19_24(){
    int prachConfigIndex = 19;
    int msg1FDM = 8;
    double ssbPerRAO = 4;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        for(int i = 0;i < 8;i++){
            subframeExpect->push_back(i);
        }
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 6){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        for(int i = 0;i < 8;i++){
            subframeExpect->push_back(i);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_23(){
    int prachConfigIndex = 19;
    int msg1FDM = 4;
    double ssbPerRAO = 4;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        for(int i = 0;i < 4;i++){
            subframeExpect->push_back(i);
        }
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 6){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        for(int i = 0;i < 4;i++){
            subframeExpect->push_back(i);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_22(){
    int prachConfigIndex = 19;
    int msg1FDM = 2;
    double ssbPerRAO = 4;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(0);
        subframeExpect->push_back(1);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 6){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(0);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_21(){
    int prachConfigIndex = 19;
    int msg1FDM = 1;
    double ssbPerRAO = 4;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(0);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 6){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(0);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_20(){
    int prachConfigIndex = 19;
    int msg1FDM = 8;
    double ssbPerRAO = 2;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(0);
        subframeExpect->push_back(2);
        subframeExpect->push_back(4);
        subframeExpect->push_back(6);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 6){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(0);
        subframeExpect->push_back(2);
        subframeExpect->push_back(4);
        subframeExpect->push_back(6);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_19(){
    int prachConfigIndex = 19;
    int msg1FDM = 4;
    double ssbPerRAO = 2;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(0);
        subframeExpect->push_back(2);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 6){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(0);
        subframeExpect->push_back(2);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_18(){
    int prachConfigIndex = 19;
    int msg1FDM = 2;
    double ssbPerRAO = 2;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(0);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 6){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(0);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_17(){
    int prachConfigIndex = 19;
    int msg1FDM = 1;
    double ssbPerRAO = 2;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(0);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_16(){
    int prachConfigIndex = 19;
    int msg1FDM = 8;
    double ssbPerRAO = 0.125;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 2;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 6){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(8);
        subframeExpect->push_back(9);
        subframeExpect->push_back(10);
        subframeExpect->push_back(11);
        subframeExpect->push_back(12);
        subframeExpect->push_back(13);
        subframeExpect->push_back(14);
        subframeExpect->push_back(15);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_15(){
    int prachConfigIndex = 19;
    int msg1FDM = 4;
    double ssbPerRAO = 0.125;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 4;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 11){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(8);
        subframeExpect->push_back(9);
        subframeExpect->push_back(10);
        subframeExpect->push_back(11);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 16){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(12);
        subframeExpect->push_back(13);
        subframeExpect->push_back(14);
        subframeExpect->push_back(15);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_14(){
    int prachConfigIndex = 19;
    int msg1FDM = 2;
    double ssbPerRAO = 0.125;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 8;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 21){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(8);
        subframeExpect->push_back(9);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 26){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(10);
        subframeExpect->push_back(11);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 31){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(12);
        subframeExpect->push_back(13);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 36){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(14);
        subframeExpect->push_back(15);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_13(){
    int prachConfigIndex = 19;
    int msg1FDM = 1;
    double ssbPerRAO = 0.125;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 16;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 41){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(8);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 46){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(9);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 51){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(10);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 56){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(11);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 61){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(12);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 66){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(13);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 71){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(14);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 76){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(15);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_12(){
    int prachConfigIndex = 19;
    int msg1FDM = 8;
    double ssbPerRAO = 0.25;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_11(){
    int prachConfigIndex = 19;
    int msg1FDM = 4;
    double ssbPerRAO = 0.25;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 2;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 6){
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_10(){
    int prachConfigIndex = 19;
    int msg1FDM = 2;
    double ssbPerRAO = 0.25;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 4;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 11){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(4);
        subframeExpect->push_back(5);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 16){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_9(){
    int prachConfigIndex = 19;
    int msg1FDM = 1;
    double ssbPerRAO = 0.25;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 8;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 21){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(4);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 26){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(5);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 31){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(6);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 36){
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_8(){
    int prachConfigIndex = 19;
    int msg1FDM = 8;
    double ssbPerRAO = 0.5;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(2);
        subframeExpect->push_back(3);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 6){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(2);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_7(){
    int prachConfigIndex = 19;
    int msg1FDM = 4;
    double ssbPerRAO = 0.5;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(2);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_6(){
    int prachConfigIndex = 19;
    int msg1FDM = 2;
    double ssbPerRAO = 0.5;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 2;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 6){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(2);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_5(){
    int prachConfigIndex = 19;
    int msg1FDM = 1;
    double ssbPerRAO = 0.5;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 4;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 11){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(2);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 16){
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_4(){
    int prachConfigIndex = 19;
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
        while(j % (associationFrame * 10) < 6){
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_3(){
    int prachConfigIndex = 19;
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
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(1);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 6){
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_2(){
    int prachConfigIndex = 19;
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19_1(){
    int prachConfigIndex = 19;
    int msg1FDM = 1;
    double ssbPerRAO = 1;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 2;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 6){
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex19(){
    testPrachIndex19_1();
    testPrachIndex19_2();
    testPrachIndex19_3();
    testPrachIndex19_4();
    testPrachIndex19_5();
    testPrachIndex19_6();
    testPrachIndex19_7();
    testPrachIndex19_8();
    testPrachIndex19_9();
    testPrachIndex19_10();
    testPrachIndex19_11();
    testPrachIndex19_12();
    testPrachIndex19_13();
    testPrachIndex19_14();
    testPrachIndex19_15();
    testPrachIndex19_16();
    testPrachIndex19_17();
    testPrachIndex19_18();
    testPrachIndex19_19();
    testPrachIndex19_20();
    testPrachIndex19_21();
    testPrachIndex19_22();
    testPrachIndex19_23();
    testPrachIndex19_24();
}

#endif
