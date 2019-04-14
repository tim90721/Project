#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "general_definition.h"
#include "RAOtestPrachConfig16.cpp"
#include "RAOtestPrachConfig19.cpp"
#include "RAOtestPrachConfig22.cpp"
#include "RAOtestPrachConfig27.cpp"
#include "RAOtestPrachConfig101.cpp"
#include "RAOtestPrachConfig106.cpp"

int main(){
    testPrachIndex16();
    testPrachIndex27();
    testPrachIndex101();
    testPrachIndex106();
    testPrachIndex19();
    testPrachIndex22();
    printf("test correct\n");
    return 0;
}


