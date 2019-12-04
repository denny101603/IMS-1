//
// Created by janbe on 04.12.2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "modelib.h"
#include "loglib.h"

void logDay(int verbosity)
{
    if(MlogFrequence > daily) return;
    printf("======================\n"
           "Daily log #%d\n"
           "----------------------\n",Mdays);
    printf("GHG [g CO2 eq.]: %lf\n", MdailyCF);
    if(verbosity > 0)
    {
        printf("Production [kWh]: %ld\n",MdailyProductionKWH);
        if(verbosity > 1)
        {
        }
    }
    printf("======================\n");
}


void logYear(int verbosity)
{
    if(MlogFrequence > yearly) return;
    printf("######################\n"
           "Yearly log #%d\n"
           "----------------------\n", Myears);
    printf("GHG [g CO2 eq.]: %lld\n", MyearCF);
    if(verbosity > 0)
    {
        printf("Production [GWh]: %ld\n",MyearlyProductionGWH);
        printf("Percentage of each power plant type:\n"
               "*Coal: %f %%\n"
               "*Nuclear: %f %%\n"
               "*Wind: %f %%\n"
               "*Hydro: %f %%\n"
               "*Biomass: %f %%\n"
               "*Solar: %f %%\n"
               "*Gas: %f %%\n"
               "*Other: %f %%\n",
               MactualPercentageProduceCoal, MactualPercentageProduceNuclear, MactualPercentageProduceWind,MactualPercentageProduceHydro,
               MactualPercentageProduceBiomass, MactualPercentageProduceSolar, MactualPercentageProduceGas, MactualPercentageProduceOther);
        if(verbosity > 1)
        {
            printf("Installed power of each power plant type:\n"
                   "*Coal: %ld kW\n"
                   "*Nuclear: %ld kW\n"
                   "*Wind: %ld kW\n"
                   "*Hydro: %ld kW\n"
                   "*Biomass: %ld kW\n"
                   "*Solar: %ld kW\n"
                   "*Gas: %ld kW\n"
                   "*Other: %ld kW\n",
                   MactualInstalledPowerKWCoal, MactualInstalledPowerKWNuclear, MactualInstalledPowerKWWind,MactualInstalledPowerKWHydro,
                   MactualInstalledPowerKWBiomass, MactualInstalledPowerKWSolar, MactualInstalledPowerKWGas, MactualInstalledPowerKWOther);
        }
    }
    printf("######################\n");

}


void logTotal(int verbosity)
{
    printf("**********************\n"
           "**********************\n"
           "Total log\n"
           "----------------------\n");
    printf("GHG [g CO2 eq.]: %lld\n", MfinalCFkg*1000);
    if(verbosity > 0)
    {
        printf("Years: %d\n", Myears);
        printf("Percentage of each power plant type:\n"
               "*Coal: %f %%\n"
               "*Nuclear: %f %%\n"
               "*Wind: %f %%\n"
               "*Hydro: %f %%\n"
               "*Biomass: %f %%\n"
               "*Solar: %f %%\n"
               "*Gas: %f %%\n"
               "*Other: %f %%\n",
               MactualPercentageProduceCoal, MactualPercentageProduceNuclear, MactualPercentageProduceWind,MactualPercentageProduceHydro,
               MactualPercentageProduceBiomass, MactualPercentageProduceSolar, MactualPercentageProduceGas, MactualPercentageProduceOther);
        if(verbosity > 1)
        {
            printf("Installed power of each power plant type:\n"
                   "*Coal: %ld kW\n"
                   "*Nuclear: %ld kW\n"
                   "*Wind: %ld kW\n"
                   "*Hydro: %ld kW\n"
                   "*Biomass: %ld kW\n"
                   "*Solar: %ld kW\n"
                   "*Gas: %ld kW\n"
                   "*Other: %ld kW\n",
                   MactualInstalledPowerKWCoal, MactualInstalledPowerKWNuclear, MactualInstalledPowerKWWind,MactualInstalledPowerKWHydro,
                   MactualInstalledPowerKWBiomass, MactualInstalledPowerKWSolar, MactualInstalledPowerKWGas, MactualInstalledPowerKWOther);
        }
    }
    printf("**********************\n"
           "**********************\n");
}