#ifndef PRACH_INDEX_22_TEST
#define PRACH_INDEX_22_TEST

#include "general_definition.h"

extern Cell* cell;
extern UE* ue;

void testPrachIndex22_24(){
    int prachConfigIndex = 22;
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
        
        for(int k = 0;k < 3;++k){
            while(j % (associationFrame * 10) < 1 + k * 3){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(0);
            subframeExpect->push_back(1);
            subframeExpect->push_back(2);
            subframeExpect->push_back(3);
            subframeExpect->push_back(4);
            subframeExpect->push_back(5);
            subframeExpect->push_back(6);
            subframeExpect->push_back(7);
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
    //destoryExpects(expected);
    destory();
}
void testPrachIndex22_23(){
    int prachConfigIndex = 22;
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
        
        for(int k = 0;k < 3;++k){
            while(j % (associationFrame * 10) < 1 + k * 3){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(0);
            subframeExpect->push_back(1);
            subframeExpect->push_back(2);
            subframeExpect->push_back(3);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex22_22(){
    int prachConfigIndex = 22;
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
        
        for(int k = 0;k < 3;++k){
            while(j % (associationFrame * 10) < 1 + k * 3){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(0);
            subframeExpect->push_back(1);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex22_21(){
    int prachConfigIndex = 22;
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
        
        for(int k = 0;k < 3;++k){
            while(j % (associationFrame * 10) < 1 + k * 3){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(0);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex22_20(){
    int prachConfigIndex = 22;
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
        
        for(int k = 0;k < 3;++k){
            while(j % (associationFrame * 10) < 1 + k * 3){
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex22_19(){
    int prachConfigIndex = 22;
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
        
        for(int k = 0;k < 3;++k){
            while(j % (associationFrame * 10) < 1 + k * 3){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(0);
            subframeExpect->push_back(2);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex22_18(){
    int prachConfigIndex = 22;
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
        
        for(int k = 0;k < 3;++k){
            while(j % (associationFrame * 10) < 1 + k * 3){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(0);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex22_17(){
    int prachConfigIndex = 22;
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

void testPrachIndex22_16(){
    int prachConfigIndex = 22;
    int msg1FDM = 8;
    double ssbPerRAO = 0.125;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 2;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int rao = 8;
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 4){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
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

void testPrachIndex22_15(){
    int prachConfigIndex = 22;
    int msg1FDM = 4;
    double ssbPerRAO = 0.125;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 4;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int rao = 8;
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 7){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 11){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
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

void testPrachIndex22_14(){
    int prachConfigIndex = 22;
    int msg1FDM = 2;
    double ssbPerRAO = 0.125;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 8;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int rao = 8;
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 14){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 17){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 21){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 24){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(rao++);
        subframeExpect->push_back(rao++);
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

void testPrachIndex22_13(){
    int prachConfigIndex = 22;
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
        
        while(j % (associationFrame * 10) < 27){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(8);
        expected.push_back(*subframeExpect);
        j++;
        int rao = 9;
        for(int k = 0;k < 2;k++){
            while(j % (associationFrame * 10) < 31 + k * 10){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(rao++);
            expected.push_back(*subframeExpect);
            j++;
            while(j % (associationFrame * 10) < 34 + k * 10){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(rao++);
            expected.push_back(*subframeExpect);
            j++;
            while(j % (associationFrame * 10) < 37 + k * 10){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(rao++);
            expected.push_back(*subframeExpect);
            j++;
        }
        while(j % (associationFrame * 10) < 51){
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

void testPrachIndex22_12(){
    int prachConfigIndex = 22;
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

void testPrachIndex22_11(){
    int prachConfigIndex = 22;
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
        
        while(j % (associationFrame * 10) < 4){
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

void testPrachIndex22_10(){
    int prachConfigIndex = 22;
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
        
        while(j % (associationFrame * 10) < 7){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(4);
        subframeExpect->push_back(5);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 11){
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

void testPrachIndex22_9(){
    int prachConfigIndex = 22;
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
        
        while(j % (associationFrame * 10) < 14){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(4);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 17){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(5);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 21){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(6);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 24){
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

void testPrachIndex22_8(){
    int prachConfigIndex = 22;
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
        
        for(int k = 0;k < 3;k++){
            while(j % (associationFrame * 10) < 1 + k * 3){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(2);
            subframeExpect->push_back(3);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex22_7(){
    int prachConfigIndex = 22;
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

void testPrachIndex22_6(){
    int prachConfigIndex = 22;
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
        
        while(j % (associationFrame * 10) < 4){
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

void testPrachIndex22_5(){
    int prachConfigIndex = 22;
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
        
        while(j % (associationFrame * 10) < 7){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(2);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 11){
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

void testPrachIndex22_4(){
    int prachConfigIndex = 22;
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
        
        for(int k = 0;k < 3;k++){
            while(j % (associationFrame * 10) < 1 + k * 3){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(1);
            subframeExpect->push_back(5);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex22_3(){
    int prachConfigIndex = 22;
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
        
        for(int k = 0;k < 3;k++){
            while(j % (associationFrame * 10) < 1 + k * 3){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(1);
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
    //destoryExpects(expected);
    destory();
}

void testPrachIndex22_2(){
    int prachConfigIndex = 22;
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

void testPrachIndex22_1(){
    int prachConfigIndex = 22;
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
        
        while(j % (associationFrame * 10) < 4){
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

void testPrachIndex22(){
    testPrachIndex22_1();
    testPrachIndex22_2();
    testPrachIndex22_3();
    testPrachIndex22_4();
    testPrachIndex22_5();
    testPrachIndex22_6();
    testPrachIndex22_7();
    testPrachIndex22_8();
    testPrachIndex22_9();
    testPrachIndex22_10();
    testPrachIndex22_11();
    testPrachIndex22_12();
    testPrachIndex22_13();
    testPrachIndex22_14();
    testPrachIndex22_15();
    testPrachIndex22_16();
    testPrachIndex22_17();
    testPrachIndex22_18();
    testPrachIndex22_19();
    testPrachIndex22_20();
    testPrachIndex22_21();
    testPrachIndex22_22();
    testPrachIndex22_23();
    testPrachIndex22_24();
}

#endif
