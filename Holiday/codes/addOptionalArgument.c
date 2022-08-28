#include <string.h>
#include "./../Holiday.h"
#include <ctype.h>
#include <stdlib.h>

/* This function will create a new require of arguments in argParserData struct, from there all arguments will be searched */
void addOptionalArgument(argParserData *data, char *longArgumentName, char *shortArgumentName, int needValue, char *helpMessage, int isRequired){
    char newShortArgumentNameChar;

    /* Creating and copying to a buffer with more space */
    char longArgumentNameWithMoreSpace[DEFAULT_ARRAY_SIZE];
    char shortArgumentNameWithMoreSpace[DEFAULT_ARRAY_SIZE];

    strcpy(longArgumentNameWithMoreSpace, longArgumentName);
    strcpy(shortArgumentNameWithMoreSpace, shortArgumentName);

    /* Fixing if some optional argument comes with less or more dashes than expected */
    controlDashesCountInLongArgumentName(longArgumentNameWithMoreSpace, TRUE);
    controlDashesCountInLongArgumentName(shortArgumentNameWithMoreSpace, FALSE);

    /* long argument names should has more than 2 characters of length beyond the two dashes, if not, raise a "exception" */
    if(retrieveArgumentNameSize(longArgumentNameWithMoreSpace) < 2){
        puts("[Holiday log] Long argument names should has two or more characters in its name, beyond the dashes");
        exit(0);
    }

    /* long argument names should has only 1 character of length beyond the one dashe, if not, raise a "exception" */
    if(retrieveArgumentNameSize(shortArgumentNameWithMoreSpace) != 1){
        puts("[Holiday log] Short argument names should has only one character in its name, beyond the dash");
        exit(0);
    }

    if(checkIfLongNameArgumentWasAlreadyGiven(data, longArgumentNameWithMoreSpace) == TRUE){
        puts("[Holiday log] Long argument name already required by the programmer");
        exit(0);
    }

    if(checkIfShortArgumentNameWasAlreadyGiven(data, shortArgumentNameWithMoreSpace) == TRUE){
        shortArgumentNameWithMoreSpace[1] = isupper(shortArgumentNameWithMoreSpace[1]) ? tolower(shortArgumentNameWithMoreSpace[1]) : toupper(shortArgumentNameWithMoreSpace[1]);

        if(checkIfShortArgumentNameWasAlreadyGiven(data, shortArgumentNameWithMoreSpace) == TRUE){
            newShortArgumentNameChar = createNewShortArgumentName(data);

            if(newShortArgumentNameChar != '!'){
                shortArgumentNameWithMoreSpace[1] = newShortArgumentNameChar;
            }
            else{
                puts("[Holiday log] Short argument name already required by the programmer and can't find another one");
                exit(0);
            }
        }   
    }

    /* Create the required argument properly */
    data->necessaryOptionalArguments[data->necessaryOptionalArgumentsIndex] = createNecessaryOptionalArgument(data, longArgumentNameWithMoreSpace, shortArgumentNameWithMoreSpace, needValue, helpMessage, isRequired);
    data->necessaryOptionalArgumentsIndex += 1;
}

char createNewShortArgumentName(argParserData *data){
    char bufferOfFormat[3] = {0};

    for(int i = LOWERCASE_CHARS_BEGIN; i != LOWERCASE_CHARS_END; i++){
        sprintf(bufferOfFormat, "-%c", (char)i);

        if(checkIfShortArgumentNameWasAlreadyGiven(data, bufferOfFormat) == FALSE){
            return (char)i;
        }
    }

    for(int i = UPPERCASE_CHARS_BEGIN; i != UPPERCASE_CHARS_END; i++){
        sprintf(bufferOfFormat, "-%c", (char)i);

        if(checkIfShortArgumentNameWasAlreadyGiven(data, bufferOfFormat) == FALSE){
            return (char)i;                                                                     
        }
    }

    puts("sesgo");
    return '!';
}

int checkIfLongNameArgumentWasAlreadyGiven(argParserData *data, char *argumentName){
    for(int i = 0; i < data->necessaryOptionalArgumentsIndex; i++){
        if(strcmp(data->necessaryOptionalArguments[i].longArgumentName, argumentName) == 0){
            return TRUE;
        }
    }

    return FALSE;
}

int checkIfShortArgumentNameWasAlreadyGiven(argParserData *data, char *argumentName){
    for(int i = 0; i < data->necessaryOptionalArgumentsIndex; i++){
        if(strcmp(data->necessaryOptionalArguments[i].shortArgumentName, argumentName) == 0){
            return TRUE;
        }
    }

    return FALSE;
}

/* Function to make the argument creation most easy */
neededOptionalArgument createNecessaryOptionalArgument(argParserData *data, char *longArgumentName, char *shortArgumentName, int needValue, char *helpMessage, int isRequired){
    neededOptionalArgument argument;
    argument.needValue = needValue;
    argument.isRequired = isRequired;

    strcpy(argument.longArgumentName, longArgumentName);
    strcpy(argument.shortArgumentName, shortArgumentName);
    strcpy(argument.helpMessage, helpMessage);

    return argument;
}

/* Will get the size of argument name not counting the dashes */
int retrieveArgumentNameSize(char *argument){
    int i = 0;

    while(argument[i] == '-' && argument[i] != '\0'){
        i++;
    }

    return strlen(&argument[i]);
}

/* This function will control the number of dashes in an argument name */
void controlDashesCountInLongArgumentName(char *argument, int isLongArgumentName){
    char midwayBuffer[256] = {0};
    int dashesCount = 0;
    int i = 0;

    while(argument[i]  == '-'){
        dashesCount++;
        i++;
    }

    if(isLongArgumentName == TRUE){
        sprintf(midwayBuffer, "--%s", &argument[dashesCount]);
    }
    else{
        sprintf(midwayBuffer, "-%s", &argument[dashesCount]);
    }
    strcpy(argument, midwayBuffer); 
}