//
// Created by daniel on 11/29/19.
//

#include <stdlib.h>
#include <time.h>
#include "modelib.h"
#include "otherlib.h"

const int MsourceTypesNumber = 8;


int MrandomRange(int lower, int upper) {
    static int init = 1;
    if(init)
    {
        srand(time(0)); //for little bit more realistic random
        init = 0;
    }
    return (rand() % (upper - lower + 1)) + lower;
}

double MgetSourceTypeCFPerUnit(enum MsourceTypes type) {
    long ret;
    switch (type)
    {
        case coal:
            ret = MrandomRange(8500, 10500);
            break;
        case nuclear:
        case solar:
            ret = 0;
            break;
        case gas:
            ret = MrandomRange(4500,6500);
            break;
        case hydro:
            ret = MrandomRange(45, 135);
            break;
        case wind:
            ret = MrandomRange(7, 18);
            break;
        case biomass:
            ret = MrandomRange(90, 450);
            break;
        case other:
            ret = 0; //TODO CF of other sources
            break;
        default:
            ret = -1;
            break;
    }
    return ret/10.0; //the CFs upper are 10x bigger than real ones to easily generate random nums, so it needs to be divided
}

bool MinitSimulation()
{
    err = 0;
    parseConfiguration(CONF_FILE_NAME);
    if(err)
        return false;

    Myears = 0;
    Mdays = 0;
    MdailyCF = 0;
    MyearCF = 0;
    MfinalCF = 0;

    return true;
}

void startSimulation()
{
    //todo :D
}