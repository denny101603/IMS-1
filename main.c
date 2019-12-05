/**
 * @author Daniel Bubenicek (xbuben05)
 * Projekt do predmetu IMS na FIT VUT v Brne (2019/2020)
 * @date 5.12.2019
 */

#include "modelib.h"
#include "otherlib.h"

int main(int argc, char **argv)
{
    char filename[FILENAME_MAX_LEN];
    parseArg(argc, argv, filename);
	if(err)
		messageAndExit();

    if(!MinitSimulation(filename))
        messageAndExit();

    MstartSimulation();
    return 0;
}






