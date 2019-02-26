#ifndef PRACH_INDEX_106_TEST
#define PRACH_INDEX_106_TEST

#include "general_definition.h"

extern Cell *cell;
extern UE *ue;

void testPrachIndex106_14(){
    int prachConfigIndex = 106;
    int msg1FDM = 2;
    double ssbPerRAO = 1.0 / 8.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int l = 0;l < 2;l++){
            subframeExpect = new vector<int>;
            for(int k = 8;k < 16;k++){
                subframeExpect->push_back(k);
            }
            expected.push_back(*subframeExpect);
            j++;

            subframeExpect = new vector<int>;
            for(int k = 40;k < 48;k++){
                subframeExpect->push_back(k);
            }
            expected.push_back(*subframeExpect);
            j++;

            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;

            subframeExpect = new vector<int>;
            for(int k = 8;k < 16;k++){
                subframeExpect->push_back(k);
            }
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        for(int k = 8;k < 16;k++){
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

void testPrachIndex106_13(){
    int prachConfigIndex = 106;
    int msg1FDM = 1;
    double ssbPerRAO = 1.0 / 8.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        subframeExpect = new vector<int>;
        for(int k = 8;k < 12;k++){
            subframeExpect->push_back(k);
        }
        expected.push_back(*subframeExpect);
        j++;

        subframeExpect = new vector<int>;
        for(int k = 12;k < 16;k++){
            subframeExpect->push_back(k);
        }
        expected.push_back(*subframeExpect);
        j++;

        subframeExpect = new vector<int>;
        expected.push_back(*subframeExpect);
        j++;

        subframeExpect = new vector<int>;
        for(int k = 8;k < 16;k++){
            subframeExpect->push_back(k);
        }
        expected.push_back(*subframeExpect);
        j++;

        subframeExpect = new vector<int>;
        expected.push_back(*subframeExpect);
        j++;

        subframeExpect = new vector<int>;
        expected.push_back(*subframeExpect);
        j++;

        subframeExpect = new vector<int>;
        for(int k = 8;k < 16;k++){
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

void testPrachIndex106_12(){
    int prachConfigIndex = 106;
    int msg1FDM = 8;
    double ssbPerRAO = 1.0 / 4.0;
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
                subframeExpect->push_back(4 + k * 16);
                subframeExpect->push_back(5 + k * 16);
                subframeExpect->push_back(6 + k * 16);
                subframeExpect->push_back(7 + k * 16);
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

void testPrachIndex106_11(){
    int prachConfigIndex = 106;
    int msg1FDM = 4;
    double ssbPerRAO = 1.0 / 4.0;
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
                subframeExpect->push_back(4 + k * 16);
                subframeExpect->push_back(5 + k * 16);
                subframeExpect->push_back(6 + k * 16);
                subframeExpect->push_back(7 + k * 16);
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

void testPrachIndex106_10(){
    int prachConfigIndex = 106;
    int msg1FDM = 2;
    double ssbPerRAO = 1.0 / 4.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int l = 0;l < 5;l++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(4);
            subframeExpect->push_back(5);
            subframeExpect->push_back(6);
            subframeExpect->push_back(7);
            subframeExpect->push_back(20);
            subframeExpect->push_back(21);
            subframeExpect->push_back(22);
            subframeExpect->push_back(23);
            expected.push_back(*subframeExpect);
            j++;
            subframeExpect = new vector<int>;
            subframeExpect->push_back(20);
            subframeExpect->push_back(21);
            subframeExpect->push_back(22);
            subframeExpect->push_back(23);
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

void testPrachIndex106_9(){
    int prachConfigIndex = 106;
    int msg1FDM = 1;
    double ssbPerRAO = 1.0 / 4.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int l = 0;l < 2;l++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(4);
            subframeExpect->push_back(5);
            subframeExpect->push_back(6);
            subframeExpect->push_back(7);
            expected.push_back(*subframeExpect);
            j++;
            
            subframeExpect = new vector<int>;
            subframeExpect->push_back(20);
            subframeExpect->push_back(21);
            subframeExpect->push_back(22);
            subframeExpect->push_back(23);
            expected.push_back(*subframeExpect);
            j++;

            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;

            subframeExpect = new vector<int>;
            subframeExpect->push_back(4);
            subframeExpect->push_back(5);
            subframeExpect->push_back(6);
            subframeExpect->push_back(7);
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

void testPrachIndex106_8(){
    int prachConfigIndex = 106;
    int msg1FDM = 8;
    double ssbPerRAO = 1.0 / 2.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int k = 0;k < 10;k++){
            subframeExpect = new vector<int>;
            for(int l = 0;l < 12;l++){
                subframeExpect->push_back(2 + l * 8);
                subframeExpect->push_back(3 + l * 8);
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

void testPrachIndex106_7(){
    int prachConfigIndex = 106;
    int msg1FDM = 4;
    double ssbPerRAO = 1.0 / 2.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int k = 0;k < 10;k++){
            subframeExpect = new vector<int>;
            for(int l = 0;l < 6;l++){
                subframeExpect->push_back(2 + l * 8);
                subframeExpect->push_back(3 + l * 8);
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

void testPrachIndex106_6(){
    int prachConfigIndex = 106;
    int msg1FDM = 2;
    double ssbPerRAO = 1.0 / 2.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int k = 0;k < 10;k++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(2);
            subframeExpect->push_back(3);
            subframeExpect->push_back(10);
            subframeExpect->push_back(11);
            subframeExpect->push_back(18);
            subframeExpect->push_back(19);
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

void testPrachIndex106_5(){
    int prachConfigIndex = 106;
    int msg1FDM = 1;
    double ssbPerRAO = 1.0 / 2.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int k = 0;k < 10;k++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(2);
            subframeExpect->push_back(3);
            subframeExpect->push_back(10);
            subframeExpect->push_back(11);
            expected.push_back(*subframeExpect);
            j++;

            subframeExpect = new vector<int>;
            subframeExpect->push_back(10);
            subframeExpect->push_back(11);
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
    testPrachIndex106_5();
    testPrachIndex106_6();
    testPrachIndex106_7();
    testPrachIndex106_8();
    testPrachIndex106_9();
    testPrachIndex106_10();
    testPrachIndex106_11();
    testPrachIndex106_12();
    testPrachIndex106_13();
    testPrachIndex106_14();
}
#endif

