//
// Created by daniel on 11/29/19.
//

#ifndef IMS_MODELIB_H
#define IMS_MODELIB_H

long Mdays; //days of simulation passed
long Myears; //years of simulation passed
long MlimitYears; //number of years after the simulation stops

long long MfinalCF; //final output of carbon footprint
double MdailyCF; //daily output of CF

//const int MsourceTypesNumber = 8;
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
int randomRange(int lower, int upper);


#endif //IMS_MODELIB_H
