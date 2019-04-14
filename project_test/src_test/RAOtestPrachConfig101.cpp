#ifndef PRACH_INDEX_101_TEST
#define PRACH_INDEX_101_TEST

#include "general_definition.h"

extern Cell* cell;
extern UE* ue;

void testPrachIndex101_19(){
    int prachConfigIndex = 101;
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
        for(int k = 0;k < 48;k++){
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

void testPrachIndex101_18(){
    int prachConfigIndex = 101;
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
        for(int k = 0;k < 12;k++){
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

void testPrachIndex101_17(){
    int prachConfigIndex = 101;
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
        for(int k = 0;k < 48;k++){
            subframeExpect->push_back(k * 2);
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

void testPrachIndex101_16(){
    int prachConfigIndex = 101;
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
        for(int k = 0;k < 24;k++){
            subframeExpect->push_back(k * 2);
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

void testPrachIndex101_15(){
    int prachConfigIndex = 101;
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
        for(int k = 0;k < 6;k++){
            subframeExpect->push_back(k * 2);
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

void testPrachIndex101_14(){
    int prachConfigIndex = 101;
    int msg1FDM = 8;
    double ssbPerRAO = 1.0 / 8.0;
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
        for(int l = 0;l < 3;l++){
            for(int k = 8;k < 16;k++){
                subframeExpect->push_back(k + l * 32);
            } 
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

void testPrachIndex101_13(){
    int prachConfigIndex = 101;
    int msg1FDM = 4;
    double ssbPerRAO = 1.0 / 8.0;
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

void testPrachIndex101_12(){
    int prachConfigIndex = 101;
    int msg1FDM = 2;
    double ssbPerRAO = 1.0 / 8.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 2;
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

void testPrachIndex101_11(){
    int prachConfigIndex = 101;
    int msg1FDM = 1;
    double ssbPerRAO = 1.0 / 8.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 4;
    vector<vector<int>> expected;

    vector<int> *subframeExpect;
    int round = getRound(simulationTime, associationFrame);
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int l = 0;l < 2;l++){
            while(j % (associationFrame * 10) < 1 + l * 10){
                subframeExpect = new vector<int>;
                expected.push_back(*subframeExpect);
                j++;
            }
            subframeExpect = new vector<int>;
            for(int k = 8 + l * 4;k < 12 + l * 4;k++){
                subframeExpect->push_back(k);
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

void testPrachIndex101_10(){
    int prachConfigIndex = 101;
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
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        for(int l = 0;l < 6;l++){
            for(int k = 4;k < 8;k++){
                subframeExpect->push_back(k + l * 16);
            } 
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

void testPrachIndex101_9(){
    int prachConfigIndex = 101;
    int msg1FDM = 1;
    double ssbPerRAO = 1.0 / 4.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 2;
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
        for(int l = 0;l < 1;l++){
            for(int k = 4;k < 8;k++){
                subframeExpect->push_back(k + l * 16);
            } 
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

void testPrachIndex101_8(){
    int prachConfigIndex = 101;
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
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        for(int l = 0;l < 12;l++){
            for(int k = 2;k < 4;k++){
                subframeExpect->push_back(k + l * 8);
            } 
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

void testPrachIndex101_7(){
    int prachConfigIndex = 101;
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
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        for(int l = 0;l < 6;l++){
            for(int k = 2;k < 4;k++){
                subframeExpect->push_back(k + l * 8);
            } 
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

void testPrachIndex101_6(){
    int prachConfigIndex = 101;
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
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        for(int l = 0;l < 3;l++){
            for(int k = 2;k < 4;k++){
                subframeExpect->push_back(k + l * 8);
            } 
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

void testPrachIndex101_5(){
    int prachConfigIndex = 101;
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
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        for(int k = 2;k < 4;k++){
            subframeExpect->push_back(k);
        } 
        //subframeExpect->push_back(1);
        //subframeExpect->push_back(5);
        //subframeExpect->push_back(9);
        //subframeExpect->push_back(13);
        //subframeExpect->push_back(17);
        //subframeExpect->push_back(21);
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

void testPrachIndex101_4(){
    int prachConfigIndex = 101;
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
        for(int k = 0;k < 24;k++){
            subframeExpect->push_back(1 + k * 4);
        } 
        //subframeExpect->push_back(1);
        //subframeExpect->push_back(5);
        //subframeExpect->push_back(9);
        //subframeExpect->push_back(13);
        //subframeExpect->push_back(17);
        //subframeExpect->push_back(21);
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

void testPrachIndex101_3(){
    int prachConfigIndex = 101;
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
        for(int k = 0;k < 12;k++){
            subframeExpect->push_back(1 + k * 4);
        } 
        //subframeExpect->push_back(1);
        //subframeExpect->push_back(5);
        //subframeExpect->push_back(9);
        //subframeExpect->push_back(13);
        //subframeExpect->push_back(17);
        //subframeExpect->push_back(21);
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

void testPrachIndex101_2(){
    int prachConfigIndex = 101;
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
        subframeExpect->push_back(5);
        subframeExpect->push_back(9);
        subframeExpect->push_back(13);
        subframeExpect->push_back(17);
        subframeExpect->push_back(21);
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

void testPrachIndex101_1(){
    int prachConfigIndex = 101;
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
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(1);
        subframeExpect->push_back(5);
        subframeExpect->push_back(9);
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

void testPrachIndex101(){
    testPrachIndex101_1();
    testPrachIndex101_2();
    testPrachIndex101_3();
    testPrachIndex101_4();
    testPrachIndex101_5();
    testPrachIndex101_6();
    testPrachIndex101_7();
    testPrachIndex101_8();
    testPrachIndex101_9();
    testPrachIndex101_10();
    testPrachIndex101_11();
    testPrachIndex101_12();
    testPrachIndex101_13();
    testPrachIndex101_14();
    testPrachIndex101_15();
    testPrachIndex101_16();
    testPrachIndex101_17();
    testPrachIndex101_18();
    testPrachIndex101_19();
}

#endif
