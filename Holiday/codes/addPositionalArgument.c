#include "./../Holiday.h"

/* This function will create a new require of arguments in argParserData struct, from there all arguments will be searched */
void addPositionalArgument(argParserData *data, char *argumentID, char *helpMessage){

    HOLIDAY__checkDashesInStringBeginning(argumentID);

    /* The argument ID should has at least two characters, with dashes not counting, if not, raise an "exception" */
    if(strlen(argumentID) < 2){    
        printf("[Holiday log] Positional argument ID \"%s\" should has 2 characters or more\n", argumentID);
        exit(DEBUG_ERROR_CODE);
    }

    if(isdigit(argumentID[0])){
        printf("[Holiday log] The first character of positional argument ID \"%s\" shouldn't be a number\n", argumentID);
        exit(DEBUG_ERROR_CODE);
    }

    data->necessaryPositionalArguments[data->necessaryPositionalArgumentsIndex] = HOLIDAY__createNecessaryPositionalArgument(argumentID, helpMessage);
    data->necessaryPositionalArgumentsIndex += 1;
}

/* This function help to create a positional argument requirement most easier */
HOLIDAY__neededPositionalArgument HOLIDAY__createNecessaryPositionalArgument(char *argumentID, char *helpMessage){
    HOLIDAY__neededPositionalArgument argument;

    strcpy(argument.argumentID, argumentID);    
    strcpy(argument.helpMessage, helpMessage);

    return argument;
}

/* 
    Positional arguments shouldn't have dashes on beginning, this function alert the programmer
    and crash the program if something like that happened 
*/
void HOLIDAY__checkDashesInStringBeginning(char *buffer){
    int foundNonDashes = FALSE;
    int dashesCount = 0;
    int i = 0;

    while(buffer[i] != '\0' && foundNonDashes == FALSE){
        if(buffer[i] == '-'){
            dashesCount++;
        }
        else{
            foundNonDashes = TRUE;
        }

        i++;
    }

    if(dashesCount != 0){
        printf("[Holiday log] Positional argument names can't start with dashes, \"%s\" started with: %d dashes\n", buffer, dashesCount);
        exit(DEBUG_ERROR_CODE);
    }
}
