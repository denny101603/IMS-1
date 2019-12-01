//
// Created by daniel on 11/29/19.
//

#include <stdlib.h>
#include <time.h>
#include "modelib.h"
#include "otherlib.h"

const int MsourceTypesNumber = 8;



long MrandomRange(long lower, long upper) {
    static int init = 1;
    if(init)
    {
        srand(time(0)); //for little bit more realistic random
        init = 0;
    }
    return (rand() % (upper - lower + 1)) + lower;
}

double MgetCFBySourceType(enum MsourceTypes type, double powerAmountKWH) {
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
    return ret/10.0*powerAmountKWH; //the CFs upper are 10x bigger than real ones to easily generate random nums, so it needs to be divided
}

//todo berry doplnit fci nize o konkretni cisla (mas tam vzor, jak si myslim ze by to melo vypadat pro solar)
double MgetSourceTypeBuildCF(enum MsourceTypes type, long installedPowerKWH) {
    long ret;
    switch (type) {
        case coal:
            ret = MrandomRange(8500, 10500);
            break;
        case nuclear:
            ret = 1;
            break;
        case solar:
            ret = MrandomRange(6 * pow10(5), 12 * pow10(5)); //VZOR PRO BERRYHO
            break;
        case gas:
            ret = MrandomRange(4500, 6500);
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
    return ((double)ret) * installedPowerKWH;
}


float MgetYearlyChangePercentageProduce(int startPercentage, int finalPercentage)
{
    return ((float) (finalPercentage - startPercentage)) / (float) MlimitYears;
}

void MsetYearlyChangePercentageProduces()
{
    MyearlyChangePercentageProduceCoal = MgetYearlyChangePercentageProduce(INIT_PERCENTAGE_PRODUCE_COAL, MfinalPercentageProduceCoal);
    MyearlyChangePercentageProduceNuclear = MgetYearlyChangePercentageProduce(INIT_PERCENTAGE_PRODUCE_NUCLEAR, MfinalPercentageProduceNuclear);
    MyearlyChangePercentageProduceWind = MgetYearlyChangePercentageProduce(INIT_PERCENTAGE_PRODUCE_WIND, MfinalPercentageProduceWind);
    MyearlyChangePercentageProduceHydro = MgetYearlyChangePercentageProduce(INIT_PERCENTAGE_PRODUCE_HYDRO, MfinalPercentageProduceHydro);
    MyearlyChangePercentageProduceBiomass = MgetYearlyChangePercentageProduce(INIT_PERCENTAGE_PRODUCE_BIOMASS, MfinalPercentageProduceBiomass);
    MyearlyChangePercentageProduceSolar = MgetYearlyChangePercentageProduce(INIT_PERCENTAGE_PRODUCE_SOLAR, MfinalPercentageProduceSolar);
    MyearlyChangePercentageProduceGas = MgetYearlyChangePercentageProduce(INIT_PERCENTAGE_PRODUCE_GAS, MfinalPercentageProduceGas);
    MyearlyChangePercentageProduceOther = MgetYearlyChangePercentageProduce(INIT_PERCENTAGE_PRODUCE_OTHER, MfinalPercentageProduceOther);
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
    MfinalCFkg = 0;

    MdailyProductionKWH = INIT_DAILY_PRODUCE_KWH;

    MactualPercentageProduceCoal = INIT_PERCENTAGE_PRODUCE_COAL;
    MactualPercentageProduceNuclear = INIT_PERCENTAGE_PRODUCE_NUCLEAR;
    MactualPercentageProduceWind = INIT_PERCENTAGE_PRODUCE_WIND;
    MactualPercentageProduceHydro = INIT_PERCENTAGE_PRODUCE_HYDRO;
    MactualPercentageProduceBiomass = INIT_PERCENTAGE_PRODUCE_BIOMASS;
    MactualPercentageProduceSolar = INIT_PERCENTAGE_PRODUCE_SOLAR;
    MactualPercentageProduceGas = INIT_PERCENTAGE_PRODUCE_GAS;
    MactualPercentageProduceOther = INIT_PERCENTAGE_PRODUCE_OTHER;

    MsetYearlyChangePercentageProduces();


    return true;
}

void MstartSimulation()
{
    while (MlimitYears >= Myears)
    {
        MsimulateYear();
        updateProductionRatio();
        //todo postavit nove elektrarny
        //todo obnovit elektrarny
        //todo zabit elektrarny s prilis vysokym instalovanym vykonem vuci realne produkci
        MfinalCFkg += MyearCF / 1000; //g -> kg
        Myears++;
    }
}

void updateProductionRatio()
{
    MactualPercentageProduceCoal += MyearlyChangePercentageProduceCoal;
    MactualPercentageProduceNuclear += MyearlyChangePercentageProduceNuclear;
    MactualPercentageProduceWind += MyearlyChangePercentageProduceWind;
    MactualPercentageProduceHydro += MyearlyChangePercentageProduceHydro;
    MactualPercentageProduceBiomass += MyearlyChangePercentageProduceBiomass;
    MactualPercentageProduceSolar += MyearlyChangePercentageProduceSolar;
    MactualPercentageProduceGas += MyearlyChangePercentageProduceGas;
    MactualPercentageProduceOther += MyearlyChangePercentageProduceOther;
}

void MsimulateYear() 
{
    int daysInYear = 365;
    if(!Myears%4) //leap year
        daysInYear = 366;

    MyearCF = 0;

    for (int i = 0; i < daysInYear; ++i)
    {
        MsimulateDay();
        MyearCF += (unsigned long long) MdailyCF; //not important loose of precision
        MdailyProductionKWH += DAILY_INCREASE_PRODUCE_KWH;
        Mdays++;
    }
}

void MsimulateDay()
{
    MdailyCF = MgetCFBySourceType(coal, MactualPercentageProduceCoal / 100.0 * MdailyProductionKWH);
    MdailyCF += MgetCFBySourceType(nuclear, MactualPercentageProduceNuclear / 100.0 * MdailyProductionKWH);
    MdailyCF += MgetCFBySourceType(wind, MactualPercentageProduceWind / 100.0 * MdailyProductionKWH);
    MdailyCF += MgetCFBySourceType(hydro, MactualPercentageProduceHydro / 100.0 * MdailyProductionKWH);
    MdailyCF += MgetCFBySourceType(biomass, MactualPercentageProduceBiomass / 100.0 * MdailyProductionKWH);
    MdailyCF += MgetCFBySourceType(solar, MactualPercentageProduceSolar / 100.0 * MdailyProductionKWH);
    MdailyCF += MgetCFBySourceType(gas, MactualPercentageProduceGas / 100.0 * MdailyProductionKWH);
    MdailyCF += MgetCFBySourceType(other, MactualPercentageProduceOther / 100.0 * MdailyProductionKWH);
}

