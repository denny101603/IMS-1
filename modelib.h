//
// Created by daniel on 11/29/19.
//

#ifndef IMS_MODELIB_H
#define IMS_MODELIB_H

#include <stdbool.h>

//TODO berry check INIT_DAILY_PRODUCE_GWH
#define INIT_DAILY_PRODUCE_GWH 88002 //daily production of electricity in GWH on the beginning of simulation
//TODO berry spocitej daily deltu a zapis ji do makra nize
#define DAILY_INCREASE_PRODUCE_KWH 000 //daily increase of electricity consumption

//TODO berry prosim doplnit vse nize + mi sem poznamenej jednotky (vsude stejne samozrejme :D)
#define INIT_INSTALLED_POWER_COAL
#define INIT_INSTALLED_POWER_NUCLEAR
#define INIT_INSTALLED_POWER_WIND
#define INIT_INSTALLED_POWER_HYDRO
#define INIT_INSTALLED_POWER_BIOMASS
#define INIT_INSTALLED_POWER_SOLAR
#define INIT_INSTALLED_POWER_GAS
#define INIT_INSTALLED_POWER_OTHER

long Mdays; //days of simulation passed
long Myears; //years of simulation passed
long MlimitYears; //number of years after the simulation stops

long long MfinalCF; //final output of carbon footprint
double MdailyCF; //daily output of CF



const int MsourceTypesNumber;
enum MsourceTypes
{
    coal, solar, wind, nuclear, gas, hydro, biomass, other
};

/**
 * Returns carbon footprint per produced kWh for chosen source type in grams of CO2
 * @param type
 * @return
 */
double MgetSourceTypeCFPerUnit(enum MsourceTypes type);

/**
 * return random number between lower and upper number
 * @param lower
 * @param upper
 * @return
 */
int MrandomRange(int lower, int upper);

//bool MinitSimulation(long maxYears)


#endif //IMS_MODELIB_H
