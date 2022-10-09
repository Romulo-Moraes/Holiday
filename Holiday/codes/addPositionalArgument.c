#include "./../Holiday.h"

/* This function will create a new require of arguments in argParserData struct, from there all arguments will be searched */
void addPositionalArgument(argParserData *data, char *argumentID, char *helpMessage){
    char argumentIDWithMoreSpace[256] = {0};

    strcpy(argumentIDWithMoreSpace, argumentID);
    HOLIDAY__removeDashesFromPositionalArgument(argumentIDWithMoreSpace, sizeof(argumentIDWithMoreSpace));

    /* The argument ID should has at least two characters, with dashes not counting, if not, raise an "exception" */
    if(strlen(argumentIDWithMoreSpace) < 2){    
        puts("[Holiday log] Positional argument ID should has 2 characters or more, dashes don't count");
        exit(DEBUG_ERROR_CODE);
    }

    if(isdigit(argumentIDWithMoreSpace[0])){
        puts("[Holiday log] The first character of positional argument ID shouldn't be a number");
        exit(DEBUG_ERROR_CODE);
    }

    data->necessaryPositionalArguments[data->necessaryPositionalArgumentsIndex] = HOLIDAY__createNecessaryPositionalArgument(argumentIDWithMoreSpace, helpMessage);
    data->necessaryPositionalArgumentsIndex += 1;
}

/* This function help to create a positional argument requirement most easier */
HOLIDAY__neededPositionalArgument HOLIDAY__createNecessaryPositionalArgument(char *argumentID, char *helpMessage){
    HOLIDAY__neededPositionalArgument argument;

    strcpy(argument.argumentID, argumentID);    
    strcpy(argument.helpMessage, helpMessage);

    return argument;
}

/* This function will remove any dashes on the begin of a string, if has any */
void HOLIDAY__removeDashesFromPositionalArgument(char *argument, int argumentBufferSize){
    char midwayBuffer[256] = {0};
    int i = 0;


    while(argument[i] == '-' && argument[i] != '\0'){
        i++;
    }

    strcpy(midwayBuffer, &argument[i]);
    memset(argument, '\0', argumentBufferSize);

    strcpy(argument, midwayBuffer);
}
