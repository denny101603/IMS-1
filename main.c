/**
 * @author Daniel Bubenicek (xbuben05)
 * Projekt do predmetu IMS na FIT VUT v Brne (2019/2020)
 * @date 5.12.2019
 */

#include "modelib.h"
#include "otherlib.h"


int main() {
    if(!MinitSimulation())
        messageAndExit();

    MstartSimulation();
    return 0;
}





