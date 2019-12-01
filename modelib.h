//
// Created by daniel on 11/29/19.
//

#ifndef IMS_MODELIB_H
#define IMS_MODELIB_H

#include <stdbool.h>

//TODO berry check INIT_DAILY_PRODUCE_GWH
#define INIT_DAILY_PRODUCE_GWH 88002 //daily production of electricity in GWH at the beginning of simulation
//TODO berry spocitej daily deltu a zapis ji do makra nize
#define DAILY_INCREASE_PRODUCE_KWH 000 //daily increase of electricity consumption

//TODO berry prosim doplnit vse nize + mi sem poznamenej jednotky (vsude stejne samozrejme :D)
//installed power of each type in JEDNOTKA per OBDOBI at the beginning of simulation
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


long Mdays; //days of simulation passed
long Myears; //years of simulation passed
long MlimitYears; //number of years after the simulation stops

long long MfinalCF; //final output of carbon footprint
long long MyearCF; //yearly output of carbon footprint
double MdailyCF; //daily output of CF

long MdailyProduceGWH; //how much energy needs to be produced in a day (GWH)

//what percentage of energy should generate each source at the end of simulation
long MfinalPercentageProduceCoal;
long MfinalPercentageProduceNuclear;
long MfinalPercentageProduceWind;
long MfinalPercentageProduceHydro;
long MfinalPercentageProduceBiomass;
long MfinalPercentageProduceSolar;
long MfinalPercentageProduceGas;
long MfinalPercentageProduceOther;

//Yearly change of percentage of energy production of each source (linear from start state to final year state)
float MyearlyChangePercentageProduceCoal;
float MyearlyChangePercentageProduceNuclear;
float MyearlyChangePercentageProduceWind;
float MyearlyChangePercentageProduceHydro;
float MyearlyChangePercentageProduceBiomass;
float MyearlyChangePercentageProduceSolar;
float MyearlyChangePercentageProduceGas;
float MyearlyChangePercentageProduceOther;

const int MsourceTypesNumber; //number of used types of sources
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

void MgetYearlyChangePercentageProduceAllSources();

/**
 * inits all variables for start of simulation, also reads from config file
 * @return true on success
 */
bool MinitSimulation();

void startSimulation();


#endif //IMS_MODELIB_H
