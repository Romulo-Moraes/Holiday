#include "./../Holiday.h"

/* This function will create a new require of arguments in argParserData struct, from there all arguments will be searched */
void addOptionalArgument(argParserData *data, char *longArgumentName, char *shortArgumentName, int needValue, char *helpMessage, int isRequired){
    int dashesInBegin = 0;


    /* Checking if some arguments were passed wrong */
    if(HOLIDAY__dashesChecking(longArgumentName, TRUE, &dashesInBegin) != TRUE){
        printf("[Holiday log] Long optional argument name \"%s\" should start with two dashes, started with: %d\n", longArgumentName, dashesInBegin);
        exit(DEBUG_ERROR_CODE);
    }

    if(HOLIDAY__dashesChecking(shortArgumentName, FALSE, &dashesInBegin) != TRUE){
        printf("[Holiday log] Short optional argument name \"%s\" should start with one dash, started with: %d\n", shortArgumentName, dashesInBegin);
        exit(DEBUG_ERROR_CODE);
    }

    /* long argument names should has more than 2 characters of length beyond the two dashes, if not, raise a "exception" */
    if(HOLIDAY__retrieveArgumentNameSize(longArgumentName) < 2){
        puts("[Holiday log] Long argument names should has two or more characters in its name, beyond the dashes");
        exit(DEBUG_ERROR_CODE);
    }

    /* long argument names should has only 1 character of length beyond the one dashe, if not, raise a "exception" */
    if(HOLIDAY__retrieveArgumentNameSize(shortArgumentName) != 1){
        puts("[Holiday log] Short argument names should has only one character in its name, beyond the dash");
        exit(DEBUG_ERROR_CODE);
    }

    if(HOLIDAY__checkIfLongNameArgumentWasAlreadyGiven(data, longArgumentName) == TRUE){
        puts("[Holiday log] Long argument name already required by the programmer");
        exit(DEBUG_ERROR_CODE);
    }

    if(isdigit(longArgumentName[2])){
        puts("[Holiday log] The first character of long argument name shouldn't be a number");
        exit(DEBUG_ERROR_CODE);
    }

    if(isdigit(shortArgumentName[1])){
        puts("[Holiday log] The short optional name shouldn't be a number");
        exit(DEBUG_ERROR_CODE);
    }

    if(HOLIDAY__checkIfShortArgumentNameWasAlreadyGiven(data, shortArgumentName) == TRUE){
        printf("[Holiday log] Short argument name conflict, this name was used 2 times: %s\n", shortArgumentName);
        exit(DEBUG_ERROR_CODE);
    }

    /* Create the required argument properly */
    data->necessaryOptionalArguments[data->necessaryOptionalArgumentsIndex] = HOLIDAY__createNecessaryOptionalArgument(data, longArgumentName, shortArgumentName, needValue, helpMessage, isRequired);
    data->necessaryOptionalArgumentsIndex += 1;
}

char HOLIDAY__createNewShortArgumentName(argParserData *data){
    char bufferOfFormat[3] = {0};

    for(int i = LOWERCASE_CHARS_BEGIN; i != LOWERCASE_CHARS_END; i++){
        sprintf(bufferOfFormat, "-%c", (char)i);

        if(HOLIDAY__checkIfShortArgumentNameWasAlreadyGiven(data, bufferOfFormat) == FALSE){
            return (char)i;
        }
    }

    for(int i = UPPERCASE_CHARS_BEGIN; i != UPPERCASE_CHARS_END; i++){
        sprintf(bufferOfFormat, "-%c", (char)i);

        if(HOLIDAY__checkIfShortArgumentNameWasAlreadyGiven(data, bufferOfFormat) == FALSE){
            return (char)i;                                                                     
        }
    }


    return '!';
}

int HOLIDAY__checkIfLongNameArgumentWasAlreadyGiven(argParserData *data, char *argumentName){
    for(int i = 0; i < data->necessaryOptionalArgumentsIndex; i++){
        if(strcmp(data->necessaryOptionalArguments[i].longArgumentName, argumentName) == 0){
            return TRUE;
        }
    }

    return FALSE;
}

int HOLIDAY__checkIfShortArgumentNameWasAlreadyGiven(argParserData *data, char *argumentName){
    for(int i = 0; i < data->necessaryOptionalArgumentsIndex; i++){
        if(strcmp(data->necessaryOptionalArguments[i].shortArgumentName, argumentName) == 0){
            return TRUE;
        }
    }

    return FALSE;
}

/* Function to make the argument creation most easy */
HOLIDAY__neededOptionalArgument HOLIDAY__createNecessaryOptionalArgument(argParserData *data, char *longArgumentName, char *shortArgumentName, int needValue, char *helpMessage, int isRequired){
    HOLIDAY__neededOptionalArgument argument;
    argument.needValue = needValue;
    argument.isRequired = isRequired;

    strcpy(argument.longArgumentName, longArgumentName);
    strcpy(argument.shortArgumentName, shortArgumentName);
    strcpy(argument.helpMessage, helpMessage);

    return argument;
}

/* Will get the size of argument name not counting the dashes */
int HOLIDAY__retrieveArgumentNameSize(char *argument){
    int i = 0;

    while(argument[i] == '-' && argument[i] != '\0'){
        i++;
    }

    return strlen(&argument[i]);
}

/* This procedure will check the count of dashes for each type of argument */
int HOLIDAY__dashesChecking(char *argument, int isLongArgumentName, int *dashesInBeginOutput){
    int dashesInBegin = 0;
    int i = 0;
    int nonDashFound = FALSE;

    while(argument[i] != '\0' && nonDashFound == FALSE){
        if(argument[i] == '-'){
            dashesInBegin++;
        }
        else{
            nonDashFound = TRUE;
        }
        i++;
    }

    *dashesInBeginOutput =  dashesInBegin;

    if(isLongArgumentName == TRUE){
        if(dashesInBegin != 2){
            return FALSE;
        }
    }
    else{
        if(dashesInBegin != 1){
            return FALSE;
        }
    }

    return TRUE;
}