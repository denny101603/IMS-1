/**
 * @author Daniel Bubenicek (xbuben05)
 * Projekt do predmetu IMS na FIT VUT v Brne (2019/2020)
 * @date 5.12.2019
 */

#ifndef IMS_OTHERLIB_H
#define IMS_OTHERLIB_H

#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "modelib.h"
#include <stdio.h>

int err;

#define NUMBER_OF_INPUT_FLAGS 11 //number of tags in config file
#define FLAG_MAX_LEN 32 //maximum length of input tag in file
#define VALUE_MAX_LEN 32 //maximum length of input value in file

#define CONF_FILE_NAME "imsConf.txt"

/**
 * parses, checks and sets all variables initialized by config file
 * @param filename
 */
void parseConfiguration(char *filename);


/**
 * Reads value from file position in file needs to be set to ':' prior first char of value
 * @param fd
 * @return -1 in case of error, number if it is ok
 */
long parseValue(FILE *fd);

/**
 * Sets all variables initiated from config file
 * @param values of variables in the right order
 */
void setVarNamesFromConfFile(const long *values);

enum errors{
    errFileOpen = 1, errFileFormat
};

void messageAndExit();

/**
 * Returns 10**power, works only for power >= 0!
 * @param power
 * @return
 */
long Mpow10(unsigned int power);


#endif //IMS_OTHERLIB_H
