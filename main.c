#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "modelib.h"
#include "otherlib.h"

int main() {
    printf("Hello, World!\n");
    /*
    int pole[] = {0,0,0,0,0};
    for (int i = 0; i < 10000; ++i) {
        pole[MrandomRange(1, 5) % 5]++;
    }
    for (int j = 0; j < 5; ++j) {

        printf("%i\n", pole[j]);
    }
     */

    parseConfiguration(CONF_FILE_NAME);
    printf("%li", MlimitYears);
    printf("%li", MfinalPercentageProduceCoal);
    printf("%li", MfinalPercentageProduceNuclear);
    printf("%li", MfinalPercentageProduceOther);
    return 0;
}

