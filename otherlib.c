/**
 * @author Daniel Bubenicek (xbuben05)
 * Projekt do predmetu IMS na FIT VUT v Brne (2019/2020)
 * @date 5.12.2019
 */

#include <stdbool.h>
#include <errno.h>
#include "otherlib.h"

char *inputFlags[] = {"years:", "coal:", "solar:", "wind:", "hydro:", "nuclear:", "biomass:", "gas:", "other:", "verbose:", "frequency:"}; //names of input flags in config file


bool checkVars(long *vars);

void parseConfiguration(char *filename)
{
    char flag[FLAG_MAX_LEN];
    int c;
    long values[NUMBER_OF_INPUT_FLAGS];

    FILE *fd;
    fd = fopen(filename, "r");
    if(fd == NULL)
    {
        err = errFileOpen;
        return; //nepovedlo se otevrit sooubor
    }
    for (int i = 0; i < NUMBER_OF_INPUT_FLAGS; i++)
    {
        for (int j = 0; j < FLAG_MAX_LEN; j++)
        {
            if((c = fgetc(fd)) == EOF)
            {
                fclose(fd);
                err = errFileFormat;
                return; //spatny format souboru
            }
            if(c != inputFlags[i][j])
            {
                fclose(fd);
                err = errFileFormat;
                return; //spatny format souboru
            }
            if(c == ':') //konec flagu
            {
                if((values[i] = parseValue(fd)) == -1)
                {
                    fclose(fd);
                    err = errFileFormat;
                    return;
                }
                break;
            }
        }
    }
    fclose(fd);
    if(!checkVars(values))
    {
        err = errSum100;
        return;
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
    MlimitYears = (int) values[i++];
    MfinalPercentageProduceCoal = (float) values[i++];
    MfinalPercentageProduceSolar = (float) values[i++];
    MfinalPercentageProduceWind = (float) values[i++];
    MfinalPercentageProduceHydro = (float) values[i++];
    MfinalPercentageProduceNuclear = (float) values[i++];
    MfinalPercentageProduceBiomass = (float) values[i++];
    MfinalPercentageProduceGas = (float) values[i++];
    MfinalPercentageProduceOther = (float) values[i++];
    Mverbose = (int) values[i++];
    MlogFrequency = (int) values[i++];
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
        if(c == '\r')
            continue;
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
    return -1;
}

void messageAndExit() {
    switch (err)
    {
        case errFileFormat:
            fprintf(stderr, "Config file has wrong format!\n");
            break;
        case errFileOpen:
            fprintf(stderr, "Config file cannot be opened!\n");
            break;
        case errSum100:
            fprintf(stderr, "Sum of final ratio of sources is not 100 %%! Please check imsConf.txt.\n");
            break;
        default:
            fprintf(stderr, "Unspecified error!\n");
            break;
    }
    exit(err);
}

long Mpow10(unsigned int power)
{
    long base = 10;
    long result = 1;
    for (unsigned int i = 0; i < power; i++) {
        result *= base;
    }
    return result;
}






























