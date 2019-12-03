//
// Created by daniel on 11/29/19.
//

#include <stdlib.h>
#include <time.h>
#include "modelib.h"
#include "otherlib.h"

const int MsourceTypesNumber = 8;


unsigned long long
MincreaseInstalledPower(enum MsourceTypes type, double realDailySourceProduction,
                        unsigned long *actualInstalledSourcePowerKw);

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
            ret =  MrandomRange(1877, 2515);//aritmetický průměr
            break;
        default:
            ret = -1;
            break;
    }
    return ret/10.0*powerAmountKWH; //the CFs upper are 10x bigger than real ones to easily generate random nums, so it needs to be divided
}

//NOTE: Uhlí má při produkci elektřiny tak brutální emise, že bych deharmonizací všechno spíš znepřesnil, plyn se řídí uhlím
double MgetSourceTypeBuildCF(enum MsourceTypes type, long installedPowerKW) {
    long ret;
    switch (type) {
        case coal:
            ret = 1; //v pomeru k produkci zanedbatelna a nedohledatelna (rozhodně pod 1 %, vzhledem k číslům odhaduji tak kolem 0.001%)
            break;
        case nuclear:
            ret = MrandomRange(2279 * pow10(6), 2416* pow10(6))*+739*pow10(3); //přičítaná hodnota je za výrobu, vzhledem k výrobě je tak malá, že by nešla rozpočítat
            break;
        case solar:
            ret = MrandomRange(107 * pow10(5), 148 * pow10(5));
            break;
        case gas:
            ret = 1; //viz uhlí
            break;
        case hydro:
            ret = MrandomRange(1752 * pow10(4), 55188*pow10(4));
            break;
        case wind:
            ret = MrandomRange(1406 * pow10(6), 3514* pow10(6));
            break;
        case biomass:
            ret = MrandomRange(876*pow10(3), 105*pow10(5));
            break;
        case other:
            ret = MrandomRange(5*pow10(7),1*pow10(8)); //aritmetický průměr ostatních
            break;
        default:
            ret = -1;
            break;
    }
    return ((double)ret) * installedPowerKW;
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

    MactualInstalledPowerKWCoal = INIT_INSTALLED_POWER_COAL;
    MactualInstalledPowerKWNuclear = INIT_INSTALLED_POWER_NUCLEAR;
    MactualInstalledPowerKWWind = INIT_INSTALLED_POWER_WIND;
    MactualInstalledPowerKWHydro = INIT_INSTALLED_POWER_HYDRO;
    MactualInstalledPowerKWBiomass = INIT_INSTALLED_POWER_BIOMASS;
    MactualInstalledPowerKWSolar = INIT_INSTALLED_POWER_SOLAR;
    MactualInstalledPowerKWGas = INIT_INSTALLED_POWER_GAS;
    MactualInstalledPowerKWOther = INIT_INSTALLED_POWER_OTHER;

    MsetYearlyChangePercentageProduces();

    //koeficient vyuziti pro celou simulaci bude vychazet z koeficientu pocatecnich
    MutilizationRatioCoal = INIT_DAILY_PRODUCE_KWH * (float) INIT_PERCENTAGE_PRODUCE_COAL / 100 / 24 /INIT_INSTALLED_POWER_COAL;
    MutilizationRatioNuclear = INIT_DAILY_PRODUCE_KWH * (float) INIT_PERCENTAGE_PRODUCE_NUCLEAR / 100 / 24 /INIT_INSTALLED_POWER_NUCLEAR;
    MutilizationRatioWind = INIT_DAILY_PRODUCE_KWH * (float) INIT_PERCENTAGE_PRODUCE_WIND / 100 / 24 /INIT_INSTALLED_POWER_WIND;
    MutilizationRatioHydro = INIT_DAILY_PRODUCE_KWH * (float) INIT_PERCENTAGE_PRODUCE_HYDRO / 100 / 24 /INIT_INSTALLED_POWER_HYDRO;
    MutilizationRatioBiomass = INIT_DAILY_PRODUCE_KWH * (float) INIT_PERCENTAGE_PRODUCE_BIOMASS / 100 / 24 /INIT_INSTALLED_POWER_BIOMASS;
    MutilizationRatioSolar = INIT_DAILY_PRODUCE_KWH * (float) INIT_PERCENTAGE_PRODUCE_SOLAR / 100 / 24 /INIT_INSTALLED_POWER_SOLAR;
    MutilizationRatioGas = INIT_DAILY_PRODUCE_KWH * (float) INIT_PERCENTAGE_PRODUCE_GAS / 100 / 24 /INIT_INSTALLED_POWER_GAS;
    MutilizationRatioOther = INIT_DAILY_PRODUCE_KWH * (float) INIT_PERCENTAGE_PRODUCE_OTHER / 100 / 24 /INIT_INSTALLED_POWER_OTHER;

    return true;
}

void MstartSimulation()
{
    while (MlimitYears >= Myears)
    {

        MsimulateYear();
        MupdateProductionRatio();
        //todo postavit nove elektrarny
        MyearCF += McorrectInstalledPower();
        //todo obnovit elektrarny
        MfinalCFkg += MyearCF / 1000; //g -> kg
        Myears++;
    }
}

unsigned long long McorrectInstalledPower()
{
    //todo zabit elektrarny s prilis vysokym instalovanym vykonem vuci realne produkci
    unsigned long long cf = 0;
    cf += MincreaseInstalledPower(coal, MgetActualDailyProductionBySource(MactualPercentageProduceCoal), &MactualInstalledPowerKWCoal);
    //todo copy for all source types
}

unsigned long long MincreaseInstalledPower(enum MsourceTypes type, double realDailySourceProduction, unsigned long *actualInstalledSourcePowerKw)
{
    //todo
    return 0;
}

void MupdateProductionRatio()
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
        MdailyProductionKWH += DAILY_INCREASE_PRODUCE_KWH_CONSERVATIVE;
        Mdays++;
    }
}

void MsimulateDay()
{
    MdailyCF = MgetCFBySourceType(coal, MgetActualDailyProductionBySource(MactualPercentageProduceCoal));
    MdailyCF += MgetCFBySourceType(nuclear, MgetActualDailyProductionBySource(MactualPercentageProduceNuclear));
    MdailyCF += MgetCFBySourceType(wind, MgetActualDailyProductionBySource(MactualPercentageProduceWind));
    MdailyCF += MgetCFBySourceType(hydro, MgetActualDailyProductionBySource(MactualPercentageProduceHydro));
    MdailyCF += MgetCFBySourceType(biomass, MgetActualDailyProductionBySource(MactualPercentageProduceBiomass));
    MdailyCF += MgetCFBySourceType(solar, MgetActualDailyProductionBySource(MactualPercentageProduceSolar));
    MdailyCF += MgetCFBySourceType(gas, MgetActualDailyProductionBySource(MactualPercentageProduceGas));
    MdailyCF += MgetCFBySourceType(other, MgetActualDailyProductionBySource(MactualPercentageProduceOther));
}

double MgetActualDailyProductionBySource(float actualSourcePercentage)
{
    return actualSourcePercentage / 100.0 * MdailyProductionKWH;
}

unsigned long long MgetNecessaryInstalledPowerKW(enum MsourceTypes type)
{
    float coefficient = -1;
    float percentage = -1;
    switch (type)
    {
        case coal:
            coefficient = MutilizationRatioCoal;
            percentage = MactualPercentageProduceCoal;
            break;
        case nuclear:
            coefficient = MutilizationRatioNuclear;
            percentage = MactualPercentageProduceCoal;
            break;
        case solar:
            coefficient = MutilizationRatioSolar;
            percentage = MactualPercentageProduceSolar;
            break;
        case wind:
            coefficient = MutilizationRatioWind;
            percentage = MactualPercentageProduceWind;
            break;
        case gas:
            coefficient = MutilizationRatioGas;
            percentage = MactualPercentageProduceGas;
            break;
        case hydro:
            coefficient = MutilizationRatioHydro;
            percentage = MactualPercentageProduceHydro;
            break;
        case biomass:
            coefficient = MutilizationRatioBiomass;
            percentage = MactualPercentageProduceBiomass;
            break;
        case other:
            coefficient = MutilizationRatioOther;
            percentage = MactualPercentageProduceOther;
            break;
    }
    if (coefficient < 0 || percentage < 0)
        return -1;

    // instalovaný výkon*koeficient využití = průměrný výkon
    return MdailyProductionKWH / 24 * percentage / 100 / coefficient;
}

