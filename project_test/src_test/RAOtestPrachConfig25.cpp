#ifndef PRACH_INDEX_25_TEST
#define PRACH_INDEX_25_TEST
#include "general_definition.h"

extern Cell* cell;
extern UE* ue;

void testPrachIndex25_24(){
    int prachConfigIndex = 25;
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
        
        for(int k = 0;k < 5;k++){
            int rao = 0;
            while(j % (associationFrame * 10) < 0 + 2 * k){
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

void testPrachIndex25_23(){
    int prachConfigIndex = 25;
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
        
        for(int k = 0;k < 5;k++){
            int rao = 0;
            while(j % (associationFrame * 10) < 0 + 2 * k){
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

void testPrachIndex25_22(){
    int prachConfigIndex = 25;
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
        
        for(int k = 0;k < 5;k++){
            int rao = 0;
            while(j % (associationFrame * 10) < 0 + 2 * k){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(rao++);
            subframeExpect->push_back(rao++);
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

void testPrachIndex25_21(){
    int prachConfigIndex = 25;
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
        
        for(int k = 0;k < 5;k++){
            while(j % (associationFrame * 10) < 0 + 2 * k){
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
    destory();
}

void testPrachIndex25_20(){
    int prachConfigIndex = 25;
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
        
        for(int k = 0;k < 5;k++){
            while(j % (associationFrame * 10) < 0 + 2 * k){
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
    destory();
}

void testPrachIndex25_19(){
    int prachConfigIndex = 25;
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
        
        for(int k = 0;k < 5;k++){
            while(j % (associationFrame * 10) < 0 + 2 * k){
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
    destory();
}

void testPrachIndex25_18(){
    int prachConfigIndex = 25;
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
        
        for(int k = 0;k < 5;k++){
            int rao = 0;
            while(j % (associationFrame * 10) < 0 + 2 * k){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(rao++);
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

void testPrachIndex25_17(){
    int prachConfigIndex = 25;
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
        
        for(int k = 0;k < 2;k++){
            int rao = 0;
            while(j % (associationFrame * 10) < 0 + 4 * k){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(rao++);
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

void testPrachIndex25_16(){
    int prachConfigIndex = 25;
    int msg1FDM = 8;
    double ssbPerRAO = 0.125;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        int rao = 8;
        for(int k = 0;k < 1;k++){
            while(j % (associationFrame * 10) < 2 + 2 * k){
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

void testPrachIndex25_15(){
    int prachConfigIndex = 25;
    int msg1FDM = 4;
    double ssbPerRAO = 0.125;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 2;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        int rao = 8;
        for(int k = 0;k < 2;k++){
            while(j % (associationFrame * 10) < 4 + 2 * k){
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

void testPrachIndex25_14(){
    int prachConfigIndex = 25;
    int msg1FDM = 2;
    double ssbPerRAO = 0.125;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 4;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        int rao = 8;
        for(int k = 0;k < 4;k++){
            while(j % (associationFrame * 10) < 8 + 2 * k){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(rao++);
            subframeExpect->push_back(rao++);
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

void testPrachIndex25_13(){
    int prachConfigIndex = 25;
    int msg1FDM = 1;
    double ssbPerRAO = 0.125;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 8;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        int rao = 8;
        for(int k = 0;k < 8;k++){
            while(j % (associationFrame * 10) < 16 + 2 * k){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(rao++);
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

void testPrachIndex25_12(){
    int prachConfigIndex = 25;
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
        
        for(int k = 0;k < 2;k++){
            int rao = 4;
            while(j % (associationFrame * 10) < 0 + 4 * k){
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

void testPrachIndex25_11(){
    int prachConfigIndex = 25;
    int msg1FDM = 4;
    double ssbPerRAO = 0.25;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        int rao = 4;
        for(int k = 0;k < 1;k++){
        while(j % (associationFrame * 10) < 2 + 2 * k){
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

void testPrachIndex25_10(){
    int prachConfigIndex = 25;
    int msg1FDM = 2;
    double ssbPerRAO = 0.25;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 2;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        int rao = 4;
        for(int k = 0;k < 2;k++){
            while(j % (associationFrame * 10) < 4 + 2 * k){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            subframeExpect->push_back(rao++);
            subframeExpect->push_back(rao++);
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

void testPrachIndex25_9(){
    int prachConfigIndex = 25;
    int msg1FDM = 1;
    double ssbPerRAO = 0.25;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 4;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        int rao = 4;
        for(int k = 0;k < 4;k++){
        while(j % (associationFrame * 10) < 8 + 2 * k){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(rao++);
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

void testPrachIndex25_8(){
    int prachConfigIndex = 25;
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
        
        for(int k = 0;k < 5;k++){
            while(j % (associationFrame * 10) < 2 * k){
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
    destory();
}

void testPrachIndex25_7(){
    int prachConfigIndex = 25;
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
        
        while(j % (associationFrame * 10) < 0){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(2);
        subframeExpect->push_back(3);
        expected.push_back(*subframeExpect);
        j++;
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
    destory();
}

void testPrachIndex25_6(){
    int prachConfigIndex = 25;
    int msg1FDM = 2;
    double ssbPerRAO = 0.5;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 2){
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
    destory();
}

void testPrachIndex25_5(){
    int prachConfigIndex = 25;
    int msg1FDM = 1;
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
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 6){
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

void testPrachIndex25_4(){
    int prachConfigIndex = 25;
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
        
        for(int k = 0;k < 5;k++){
            while(j % (associationFrame * 10) < k * 2){
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
    destory();
}

void testPrachIndex25_3(){
    int prachConfigIndex = 25;
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
        
        for(int k = 0;k < 5;k++){
            while(j % (associationFrame * 10) < k * 2){
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
    destory();
}

void testPrachIndex25_2(){
    int prachConfigIndex = 25;
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
        
        while(j % (associationFrame * 10) < 0){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(1);
        expected.push_back(*subframeExpect);
        j++;
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
    destory();
}

void testPrachIndex25_1(){
    int prachConfigIndex = 25;
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
        
        while(j % (associationFrame * 10) < 2){
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

void testPrachIndex25(){
    testPrachIndex25_1();
    testPrachIndex25_2();
    testPrachIndex25_3();
    testPrachIndex25_4();
    testPrachIndex25_5();
    testPrachIndex25_6();
    testPrachIndex25_7();
    testPrachIndex25_8();
    testPrachIndex25_9();
    testPrachIndex25_10();
    testPrachIndex25_11();
    testPrachIndex25_12();
    testPrachIndex25_13();
    testPrachIndex25_14();
    testPrachIndex25_15();
    testPrachIndex25_16();
    testPrachIndex25_17();
    testPrachIndex25_18();
    testPrachIndex25_19();
    testPrachIndex25_20();
    testPrachIndex25_21();
    testPrachIndex25_22();
    testPrachIndex25_23();
    testPrachIndex25_24();
}
#endif
