#include "./../Holiday.h"


argParserData argParserInit(int argc, char *argv[], char *programName, char *programAbout){
    argParserData data;

    data.argc = argc;
    data.argv = argv;

    memset(data.programName, '\0', sizeof(data.programName));

    data.necessaryOptionalArguments = NULL;
    data.necessaryPositionalArguments = NULL;
    data.allCollectedOptionalArguments = NULL;
    data.allCollectedPositionalArguments = NULL;

    data.necessaryOptionalArgumentsIndex = 0;
    data.allCollectedOptionalArgumentsIndex = 0;
    data.necessaryPositionalArgumentsIndex = 0;
    data.allCollectedPositionalArgumentsIndex = 0;

    strcpy(data.programName, programName);
    strcpy(data.programAbout, programAbout);

    return data;
}   