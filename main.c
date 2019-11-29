#include <stdio.h>
#include "modelib.h"

int main() {
    printf("Hello, World!\n");
    int pole[] = {0,0,0,0,0};
    for (int i = 0; i < 10000; ++i) {
        pole[randomRange(1,5)%5]++;
    }
    for (int j = 0; j < 5; ++j) {

        printf("%i\n", pole[j]);
    }
    return 0;
}
