//
// Created by daniel on 11/29/19.
//

#ifndef IMS_MODELIB_H
#define IMS_MODELIB_H

#include <stdbool.h>

//TODO berry check INIT_DAILY_PRODUCE_KWH
#define INIT_DAILY_PRODUCE_KWH 88002000 //daily production of electricity in kWH at the beginning of simulation
//TODO berry spocitej daily deltu a zapis ji do makra nize
#define DAILY_INCREASE_PRODUCE_KWH 000 //daily increase of electricity consumption

//TODO berry prosim doplnit vse nize ve spravnych jednotkach
//installed power of each type in kW at the beginning of simulation
#define INIT_INSTALLED_POWER_COAL 0
#define INIT_INSTALLED_POWER_NUCLEAR 0
#define INIT_INSTALLED_POWER_WIND 0
#define INIT_INSTALLED_POWER_HYDRO 0
#define INIT_INSTALLED_POWER_BIOMASS 0
#define INIT_INSTALLED_POWER_SOLAR 0
#define INIT_INSTALLED_POWER_GAS 0
#define INIT_INSTALLED_POWER_OTHER 0

//percentage of really produced electricity of each source at the beginning of simulation
#define INIT_PERCENTAGE_PRODUCE_COAL 0
#define INIT_PERCENTAGE_PRODUCE_NUCLEAR 0
#define INIT_PERCENTAGE_PRODUCE_WIND 0
#define INIT_PERCENTAGE_PRODUCE_HYDRO 0
#define INIT_PERCENTAGE_PRODUCE_BIOMASS 0
#define INIT_PERCENTAGE_PRODUCE_SOLAR 0
#define INIT_PERCENTAGE_PRODUCE_GAS 0
#define INIT_PERCENTAGE_PRODUCE_OTHER 0

//every source type has it's own endurance in years before it has to be changed
#define ENDURANCE_COAL 0
#define ENDURANCE_NUCLEAR 0
#define ENDURANCE_WIND 0
#define ENDURANCE_HYDRO 0
#define ENDURANCE_BIOMASS 0
#define ENDURANCE_SOLAR 0
#define ENDURANCE_GAS 0
#define ENDURANCE_OTHER 0


int Mdays; //days of simulation passed
int Myears; //years of simulation passed
int MlimitYears; //number of years after the simulation stops

unsigned long long MfinalCFkg; //final output of carbon footprint
unsigned long long MyearCF; //yearly output of carbon footprint
double MdailyCF; //daily output of CF

long MdailyProductionKWH; //how much energy needs to be produced in a day (kWH)

//what percentage of energy should generate each source at the end of simulation
int MfinalPercentageProduceCoal;
int MfinalPercentageProduceNuclear;
int MfinalPercentageProduceWind;
int MfinalPercentageProduceHydro;
int MfinalPercentageProduceBiomass;
int MfinalPercentageProduceSolar;
int MfinalPercentageProduceGas;
int MfinalPercentageProduceOther;

//actual percentage of energy produced by each source at the time
float MactualPercentageProduceCoal;
float MactualPercentageProduceNuclear;
float MactualPercentageProduceWind;
float MactualPercentageProduceHydro;
float MactualPercentageProduceBiomass;
float MactualPercentageProduceSolar;
float MactualPercentageProduceGas;
float MactualPercentageProduceOther;

//Yearly change of percentage of energy production of each source (linear from start state to final year state)
float MyearlyChangePercentageProduceCoal;
float MyearlyChangePercentageProduceNuclear;
float MyearlyChangePercentageProduceWind;
float MyearlyChangePercentageProduceHydro;
float MyearlyChangePercentageProduceBiomass;
float MyearlyChangePercentageProduceSolar;
float MyearlyChangePercentageProduceGas;
float MyearlyChangePercentageProduceOther;

//actual installed power of each source type
unsigned long MactualInstalledPowerKWCoal;
unsigned long MactualInstalledPowerKWNuclear;
unsigned long MactualInstalledPowerKWWind;
unsigned long MactualInstalledPowerKWHydro;
unsigned long MactualInstalledPowerKWBiomass;
unsigned long MactualInstalledPowerKWSolar;
unsigned long MactualInstalledPowerKWGas;
unsigned long MactualInstalledPowerKWOther;

const int MsourceTypesNumber; //number of used types of sources
enum MsourceTypes
{
    coal, solar, wind, nuclear, gas, hydro, biomass, other
};

/**
 * Returns carbon footprint of produced powerAmountKWH for chosen source type in grams of CO2
 * @param type
 * @param powerAmountKWH
 * @return
 */
double MgetCFBySourceType(enum MsourceTypes type, double powerAmountKWH);

/**
 * Returns CF of building new source of power
 * @param type
 * @param installedPowerKWH
 * @return
 */
double MgetSourceTypeBuildCF(enum MsourceTypes type, long installedPowerKWH);

/**
 * return random number between lower and upper number
 * @param lower
 * @param upper
 * @return
 */
long MrandomRange(long lower, long upper);

float MgetYearlyChangePercentageProduce(int startPercentage, int finalPercentage);

void MsetYearlyChangePercentageProduces();

/**
 * inits all variables for start of simulation, also reads from config file
 * @return true on success
 */
bool MinitSimulation();

void MstartSimulation();

/**
 * Simulates one year, doesn't take care of incrementing Myears
 */
void MsimulateYear();

/**
 * simulates one day,  doesn't take care of incrementing Mdays
 */
void MsimulateDay();

/**
 * updates actual percentages of production of each source type
 */
void MupdateProductionRatio();

unsigned long long McorrectInstalledPower();

/**
 * returns necessary installed power to produce daily amount of energy (kWH)
 * @param type
 * @param powerAmount
 * @return
 */
unsigned long long MgetNecesaryInstalledPowerKW(enum MsourceTypes type, unsigned long long dailyEnergyAmountKWH);

/**
 * returns daily production of energy (kWH per day) of a source type by its actual percentage
 * @param actualSourcePercentage
 * @return
 */
double MgetActualDailyProductionBySource(float actualSourcePercentage);

#endif //IMS_MODELIB_H
