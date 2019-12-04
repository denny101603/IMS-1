#include <stdio.h>
#include <stdlib.h>
#include "modelib.h"
#include "otherlib.h"
#include <limits.h>


int main() {
    printf("Hello, World! \n" );
    printf("%lu\n", ULONG_MAX);
    printf("%llu\n", ULLONG_MAX);
    /*
    int pole[] = {0,0,0,0,0};
    for (int i = 0; i < 10000; ++i) {
        pole[MrandomRange(1, 5) % 5]++;
    }
    for (int j = 0; j < 5; ++j) {

        printf("%i\n", pole[j]);
    }
     */
/*
    parseConfiguration(CONF_FILE_NAME);
    printf("%li", MlimitYears);
    printf("%li", MfinalPercentageProduceCoal);
    printf("%li", MfinalPercentageProduceNuclear);
    printf("%li", MfinalPercentageProduceOther);
    */
    if(!MinitSimulation())
        messageAndExit();

    MstartSimulation();
    return 0;
}





