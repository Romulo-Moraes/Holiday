#include <string.h>
#include "./../Holiday.h"


argParserData argParserInit(int argc, char *argv[], char *programName, char *programAbout){
    argParserData data;

    data.argc = argc;
    data.argv = argv;

    memset(data.programName, '\0', sizeof(data.programName));
    memset(data.necessaryOptionalArguments, '\0', sizeof(data.necessaryOptionalArguments));
    memset(data.necessaryPositionalArguments, '\0', sizeof(data.necessaryPositionalArguments));
    memset(data.allCollectedOptionalArguments, '\0', sizeof(data.allCollectedOptionalArguments));
    memset(data.allCollectedPositionalArguments, '\0', sizeof(data.allCollectedPositionalArguments));

    data.necessaryOptionalArgumentsIndex = 0;
    data.allCollectedOptionalArgumentsIndex = 0;
    data.necessaryPositionalArgumentsIndex = 0;
    data.allCollectedPositionalArgumentsIndex = 0;

    strcpy(data.programName, programName);
    strcpy(data.programAbout, programAbout);

    return data;
}   