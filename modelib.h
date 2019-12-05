/**
 * @authors Daniel Bubenicek (xbuben05) - kod, Jan Beran (xberan43) - inicializacni data
 * Projekt do predmetu IMS na FIT VUT v Brne (2019/2020)
 * @date 5.12.2019
 */

#ifndef IMS_MODELIB_H
#define IMS_MODELIB_H

#include <stdbool.h>

#define INIT_DAILY_PRODUCE_KWH 241101370 //daily production of electricity in kWh at the beginning of simulation

//viz tabulka 3 (hodnoty zde deleny 365) //todo berry tenhle koment asi taky uplne nesedi?
#define DAILY_INCREASE_PRODUCE_KWH 4218 //daily increase of electricity consumption
#define DAILY_INCREASE_PRODUCE_KWH_DYNAMIC (2848000/365) //daily increase of electricity consumption //todo berry neco s tim udelat

//installed power of each type in kW at the beginning of simulation
#define INIT_INSTALLED_POWER_COAL 9130000
#define INIT_INSTALLED_POWER_NUCLEAR 4290000
#define INIT_INSTALLED_POWER_WIND 277000
#define INIT_INSTALLED_POWER_HYDRO 1090000
#define INIT_INSTALLED_POWER_BIOMASS 950000
#define INIT_INSTALLED_POWER_SOLAR 2030000
#define INIT_INSTALLED_POWER_GAS 1610000
#define INIT_INSTALLED_POWER_OTHER 700000 //odhad

//percentage of really produced electricity of each source at the beginning of simulation
#define INIT_PERCENTAGE_PRODUCE_COAL 46.8
#define INIT_PERCENTAGE_PRODUCE_NUCLEAR 34.0
#define INIT_PERCENTAGE_PRODUCE_WIND 0.7
#define INIT_PERCENTAGE_PRODUCE_HYDRO 1.9
#define INIT_PERCENTAGE_PRODUCE_BIOMASS 5.5
#define INIT_PERCENTAGE_PRODUCE_SOLAR 2.7
#define INIT_PERCENTAGE_PRODUCE_GAS 7.1
#define INIT_PERCENTAGE_PRODUCE_OTHER 1.3


//every source type has it's own AVERAGE_LIFESPAN in years before it has to be changed
#define AVERAGE_LIFESPAN_COAL 50
#define AVERAGE_LIFESPAN_NUCLEAR 50
#define AVERAGE_LIFESPAN_WIND 25
#define AVERAGE_LIFESPAN_HYDRO 50
#define AVERAGE_LIFESPAN_BIOMASS 25
#define AVERAGE_LIFESPAN_SOLAR 25
#define AVERAGE_LIFESPAN_GAS 50
#define AVERAGE_LIFESPAN_OTHER 35

int Mverbose; //todo denny parsovat verbose a logovaci frekvenci z vstupniho souboru - frekvenci budes asi pouzivat ty, takze si ji uprav podle sveho :)
typedef enum{
    daily, yearly, total
}Mfrequency;
Mfrequency MlogFrequency;


int Mdays; //days of simulation passed
int Myears; //years of simulation passed
int MlimitYears; //number of years after the simulation stops

unsigned long long MfinalCFkg; //final output of carbon footprint
unsigned long long MyearCF; //yearly output of carbon footprint
double MdailyCF; //daily output of CF

long MdailyProductionKWH; //how much energy needs to be produced in a day (kWH)
long MyearlyProductionGWH; //how much energy was produced during the actual year (GWH)
//what percentage of energy should generate each source at the end of simulation
float MfinalPercentageProduceCoal;
float MfinalPercentageProduceNuclear;
float MfinalPercentageProduceWind;
float MfinalPercentageProduceHydro;
float MfinalPercentageProduceBiomass;
float MfinalPercentageProduceSolar;
float MfinalPercentageProduceGas;
float MfinalPercentageProduceOther;

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

//real produced power/installed power ratio (number 0 to 1)
float MutilizationRatioCoal; //todo berry přejměnování na "utilization factor" - je to terminus technikus
float MutilizationRatioNuclear;
float MutilizationRatioWind;
float MutilizationRatioHydro;
float MutilizationRatioBiomass;
float MutilizationRatioSolar;
float MutilizationRatioGas;
float MutilizationRatioOther;

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
 * @param installedPowerKW
 * @return
 */
double MgetSourceTypeBuildCF(enum MsourceTypes type, unsigned long installedPowerKW);

/**
 * return random number between lower and upper number
 * @param lower
 * @param upper
 * @return
 */
long MrandomRange(long lower, long upper);

float MgetYearlyChangePercentageProduce(float startPercentage, float finalPercentage);

void MsetYearlyChangePercentageProduces();

/**
 * inits all variables for start of simulation, also reads from config file
 * @return true on success
 */
bool MinitSimulation(char *filename);

/**
 * performs the simulation
 */
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

/**
 * returns cf of building new power plants, updates actual installed power according to percentage of each source and its utilization factor
 * @return
 */
unsigned long long McorrectInstalledPowerAll();

/**
 * returns necessary installed power to produce daily amount of energy (kWH)
 * @param type
 * @return
 */
unsigned long MgetNecessaryInstalledPowerKW(enum MsourceTypes type);

/**
 * returns daily production of energy (kWH per day) of a source type by its actual percentage
 * @param actualSourcePercentage
 * @return
 */
double MgetActualDailyProductionBySource(float actualSourcePercentage);

/**
 * returns cf of yearly renewing power plants (every year is again "build" 1/lifespan of each power source)
 * @return
 */
unsigned long long MrenewPowerPlantsAll();

#endif //IMS_MODELIB_H
