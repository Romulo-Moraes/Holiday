#include "./../Holiday.h"
#include <string.h>

/* This function will create a new require of arguments in argParserData struct, from there all arguments will be searched */
void addPositionalArgument(argParserData *data, char *argumentID, char *helpMessage){
    char argumentIDWithMoreSpace[256] = {0};

    strcpy(argumentIDWithMoreSpace, argumentID);
    removeDashesFromPositionalArgument(argumentIDWithMoreSpace, sizeof(argumentIDWithMoreSpace));

    /* The argument ID should has at least two characters, with dashes not counting, if not, raise an "exception" */
    if(strlen(argumentIDWithMoreSpace) < 2){    
        // TODO. crash !!!
    }

    data->necessaryPositionalArguments[data->necessaryPositionalArgumentsIndex] = createNecessaryPositionalArgument(argumentIDWithMoreSpace, helpMessage);
    data->necessaryPositionalArgumentsIndex += 1;
}

/* This function help to create a positional argument requirement most easier */
neededPositionalArgument createNecessaryPositionalArgument(char *argumentID, char *helpMessage){
    neededPositionalArgument argument;

    strcpy(argument.argumentID, argumentID);    
    strcpy(argument.helpMessage, helpMessage);

    return argument;
}

/* This function will remove any dashes on the begin of a string, if has any */
void removeDashesFromPositionalArgument(char *argument, int argumentBufferSize){
    char midwayBuffer[256] = {0};
    int i = 0;


    while(argument[i] == '-' && argument[i] != '\0'){
        i++;
    }

    strcpy(midwayBuffer, &argument[i]);
    memset(argument, '\0', argumentBufferSize);

    strcpy(argument, midwayBuffer);
}
