#ifndef PRACH_INDEX_27_TEST
#define PRACH_INDEX_27_TEST

#include "general_definition.h"

extern Cell* cell;
extern UE* ue;

void testPrachIndex27_17(){
    int prachConfigIndex = 27;
    int msg1FDM = 8;
    double ssbPerRAO = 1.0 / 4.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int k = 0;k < 10;k++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(4);
            subframeExpect->push_back(5);
            subframeExpect->push_back(6);
            subframeExpect->push_back(7);
            expected.push_back(*subframeExpect);
            j++;
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        if(j >= simulationTime)
            break;
    }
    printExpects(expected);
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_16(){
    int prachConfigIndex = 27;
    int msg1FDM = 8;
    double ssbPerRAO = 1.0 / 2.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int k = 0;k < 10;k++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(2);
            subframeExpect->push_back(3);
            expected.push_back(*subframeExpect);
            j++;
        }
        if(j >= simulationTime)
            break;
    }
    printExpects(expected);
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_15(){
    int prachConfigIndex = 27;
    int msg1FDM = 4;
    double ssbPerRAO = 1.0 / 2.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int k = 0;k < 5;k++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(2);
            subframeExpect->push_back(3);
            expected.push_back(*subframeExpect);
            j++;
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            //printf("%d\t%d\n", j, j %(associationFrame * 10));
            j++;
        }
        if(j >= simulationTime)
            break;
    }
    printExpects(expected);
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_14(){
    int prachConfigIndex = 27;
    int msg1FDM = 2;
    double ssbPerRAO = 1.0 / 2.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            //printf("%d\t%d\n", j, j %(associationFrame * 10));
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(2);
        subframeExpect->push_back(3);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 5){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            //printf("%d\t%d\n", j, j %(associationFrame * 10));
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
    printExpects(expected);
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_13(){
    int prachConfigIndex = 27;
    int msg1FDM = 8;
    double ssbPerRAO = 4;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int k = 0;k < 10;k++){
            subframeExpect = new vector<int>;
            for(int l = 0;l < 8;l++){
                subframeExpect->push_back(l);
            }
            expected.push_back(*subframeExpect);
            j++;
        }
        if(j >= simulationTime)
            break;
    }
    printExpects(expected);
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_12(){
    int prachConfigIndex = 27;
    int msg1FDM = 4;
    double ssbPerRAO = 4;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int k = 0;k < 10;k++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(0);
            subframeExpect->push_back(1);
            subframeExpect->push_back(2);
            subframeExpect->push_back(3);
            expected.push_back(*subframeExpect);
            j++;
        }
        if(j >= simulationTime)
            break;
    }
    printExpects(expected);
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_11(){
    int prachConfigIndex = 27;
    int msg1FDM = 2;
    double ssbPerRAO = 4;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int k = 0;k < 10;k++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(0);
            subframeExpect->push_back(1);
            expected.push_back(*subframeExpect);
            j++;
        }
        if(j >= simulationTime)
            break;
    }
    printExpects(expected);
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_10(){
    int prachConfigIndex = 27;
    int msg1FDM = 1;
    double ssbPerRAO = 4;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int k = 0;k < 10;k++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(0);
            expected.push_back(*subframeExpect);
            j++;
        }
        if(j >= simulationTime)
            break;
    }
    printExpects(expected);
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_9(){
    int prachConfigIndex = 27;
    int msg1FDM = 1;
    double ssbPerRAO = 2;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int k = 0;k < 5;k++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(0);
            expected.push_back(*subframeExpect);
            j++;
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            j++;
        }
        if(j >= simulationTime)
            break;
    }
    printExpects(expected);
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_7(){
    int prachConfigIndex = 27;
    int msg1FDM = 1;
    double ssbPerRAO = 1.0 / 8.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 4;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 8){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            //printf("%d\t%d\n", j, j %(associationFrame * 10));
            j++;
        }
        for(int k = 8;k < 16;k++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(k);
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
    printExpects(expected);
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_6(){
    int prachConfigIndex = 27;
    int msg1FDM = 1;
    double ssbPerRAO = 1.0 / 4.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 2;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 4){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            //printf("%d\t%d\n", j, j %(associationFrame * 10));
            j++;
        }
        for(int k = 4;k < 8;k++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(k);
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
    printExpects(expected);
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_5(){
    int prachConfigIndex = 27;
    int msg1FDM = 1;
    double ssbPerRAO = 1.0 / 2.0;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 2){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            //printf("%d\t%d\n", j, j %(associationFrame * 10));
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(2);
        expected.push_back(*subframeExpect);
        j++;
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
    printExpects(expected);
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_4(){
    int prachConfigIndex = 27;
    int msg1FDM = 8;
    double ssbPerRAO = 1;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        for(int j = 0;j < 10;j++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(1);
            subframeExpect->push_back(5);
            expected.push_back(*subframeExpect);
            //printf("%d\t%d\n", j, j %(associationFrame * 10));
        }
        if(j >= simulationTime)
            break;
    }
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_3(){
    int prachConfigIndex = 27;
    int msg1FDM = 4;
    double ssbPerRAO = 1;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        for(int j = 0;j < 10;j++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(1);
            expected.push_back(*subframeExpect);
            //printf("%d\t%d\n", j, j %(associationFrame * 10));
        }
        if(j >= simulationTime)
            break;
    }
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_2(){
    int prachConfigIndex = 27;
    int msg1FDM = 2;
    double ssbPerRAO = 1;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        for(int k = 0;k < 5;k++){
            subframeExpect = new vector<int>;
            subframeExpect->push_back(1);
            expected.push_back(*subframeExpect);
            j++;
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            //printf("%d\t%d\n", j, j %(associationFrame * 10));
            j++;
        }
        if(j >= simulationTime)
            break;
    }
    validation(expected, simulationTime, prachConfigIndex, msg1FDM, ssbPerRAO);
    destory();
}

void testPrachIndex27_1(){
    int prachConfigIndex = 27;
    int msg1FDM = 1;
    double ssbPerRAO = 1;
    initialize(prachConfigIndex, msg1FDM, ssbPerRAO);

    int simulationTime = 100;
    int associationFrame = 1;
    
    vector<vector<int>> expected;
    int round = getRound(simulationTime, associationFrame);
    vector<int> *subframeExpect;
    for(int i = 0;i < round;i++){
        int j = i * associationFrame * 10;
        
        while(j % (associationFrame * 10) < 1){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            //printf("%d\t%d\n", j, j %(associationFrame * 10));
            j++;
        }
        subframeExpect = new vector<int>;
        subframeExpect->push_back(1);
        expected.push_back(*subframeExpect);
        j++;
        while(j % (associationFrame * 10) < 5){
            subframeExpect = new vector<int>;
            expected.push_back(*subframeExpect);
            //printf("%d\t%d\n", j, j %(associationFrame * 10));
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

void testPrachIndex27(){
    testPrachIndex27_1();
    testPrachIndex27_2();
    testPrachIndex27_3();
    testPrachIndex27_4();
    testPrachIndex27_5();
    testPrachIndex27_6();
    testPrachIndex27_7();
    testPrachIndex27_9();
    testPrachIndex27_10();
    testPrachIndex27_11();
    testPrachIndex27_12();
    testPrachIndex27_13();
    testPrachIndex27_14();
    testPrachIndex27_15();
    testPrachIndex27_16();
    testPrachIndex27_17();
}
#endif
