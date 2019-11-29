//
// Created by daniel on 11/29/19.
//

#include <stdlib.h>
#include "modelib.h"

int randomRange(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

double MgetSourceTypeCFPerUnit(enum MsourceTypes type) {
    long ret;
    switch (type)
    {
        case coal:
            ret = 0;
            break;
        case nuclear:
            ret = 0;
            break;
        case gas:
            ret = 0;
            break;
        case solar:
            ret = 0;
            break;
        case hydro:
            ret = 0;
            break;
        case wind:
            ret = 0;
            break;
        case biomass:
            ret = 0;
            break;
        case other:
            ret = 0;
            break;
        default:
            ret = -1;
            break;
    }
    return ret;
}
