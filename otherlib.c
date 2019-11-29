//
// Created by daniel on 11/29/19.
//

#include <stdbool.h>
#include <errno.h>
#include "otherlib.h"
#include <stdlib.h>

char *inputTags[] = {"years:", "coal:", "solar:", "wind:", "hydro:", "nuclear:", "biomass:", "gas:", "other:"}; //names of input tags in config file


bool checkVars(long *vars);

void parseConfiguration(char *filename)
{
    char tag[TAG_MAX_LEN];
    int c;
    long values[NUMBER_OF_INPUT_TAGS];

    FILE *fd;
    fd = fopen(filename, "r");
    if(fd == NULL)
    {
        printf("%i", errno);
        return; //nepovedlo se otevrit sooubor
    }
    for (int i = 0; i < NUMBER_OF_INPUT_TAGS; i++)
    {
        for (int j = 0; j < TAG_MAX_LEN; j++)
        {
            if((c = fgetc(fd)) == EOF)
            {
                fclose(fd);
                return; //spatny format souboru
            }
            if(c != inputTags[i][j])
            {
                fclose(fd);
                return; //spatny format souboru
            }
            if(c == ':') //konec tagu
            {
                if((values[i] = parseValue(fd)) == -1)
                {
                    fclose(fd);
                    return; //chyba
                }
                break;
            }
        }
    }
    fclose(fd);
    if(!checkVars(values))
    {
        return; //chyba
    }
    setVarNamesFromConfFile(values);
}

bool checkVars(long *vars) {
    //check if finalPercentageProduce give 100% in the sum
    long sum = 100;
    for(int i = 1; i < 9; i++)
        sum -= vars[i];
    if(sum)
        return false;
    return true;
}

void setVarNamesFromConfFile(const long *values) {
    int i = 0;
    MlimitYears = values[i++];
    MfinalPercentageProduceCoal = values[i++];
    MfinalPercentageProduceSolar = values[i++];
    MfinalPercentageProduceWind = values[i++];
    MfinalPercentageProduceHydro = values[i++];
    MfinalPercentageProduceNuclear = values[i++];
    MfinalPercentageProduceBiomass = values[i++];
    MfinalPercentageProduceGas = values[i++];
    MfinalPercentageProduceOther = values[i++];
}


long parseValue(FILE *fd)
{
    int c;
    char value[VALUE_MAX_LEN];
    long retValue;
    char *endptr;

    for (int i = 0; i < VALUE_MAX_LEN-1; i++)
    {
        if((c = fgetc(fd)) == EOF)
        {
            return -1; //spatny format souboru
        }
        if(c == '\n' && i == 0)
        {
            return -1;
        }
        if(c == '\n') //the end of value
        {
            value[i] = '\0';
            errno = 0;
            retValue = strtol(value, &endptr, 10);
            if(strcmp("", endptr) != 0)
            {
                return -1;
            }
            if(errno != 0)
                return -1;
            return retValue;
        }
        else
            value[i] = (char) c;
    }
}
































