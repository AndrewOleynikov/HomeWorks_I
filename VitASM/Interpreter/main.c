#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

int main()
{
    struct Interpreter inter;
    startInterpretr(&inter);

    FILE *progFile = fopen("program.txt", "r");
    if (!progFile)
    {
        printf("ERROR");
        exit(1);
    }
    parsingLabels(&inter, progFile);
    fclose(progFile);

    progFile = fopen("program.txt", "r");
    if (!progFile)
    {
        printf("ERROR");
        exit(1);
    }
    createByteCode(&inter, progFile);
    fclose(progFile);

    execuite(&inter);
    endInterpretr(&inter);

    return 0;
}
