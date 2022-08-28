#include "./../Holiday.h"
#include <string.h>
#include <stdlib.h>

void parseArguments(argParserData *data, int enableBreak){
    /* This if case is executed in sequence and if any error is reported from any process the program show the help message and exit */
    if(pickupAllLongArgumentNames(data) != 0 || pickupAllShortArgumentNames(data) != 0 || pickupAllPositionalArguments(data) != 0 || checkIfAllRequiredArgumentsWasGiven(data) == 0 || checkIfCountOfCollectedPositionalArgumentsIsCorrect(data) == 0 || checkIfUnknowArgumentsWasPassedToProgram(data) != 0){
        showHelpMessage(data, 0);
    }
}

int checkIfUnknowArgumentsWasPassedToProgram(argParserData *data){
    int found = FALSE;

    /* The strategy here is run the collected array and compare if each element exists in the necessary array */
    for(int i = 0; i < data->allCollectedOptionalArgumentsIndex; i++){
        for(int j = 0; j < data->necessaryOptionalArgumentsIndex; j++){
            if(strcmp(data->necessaryOptionalArguments[j].longArgumentName, data->allCollectedOptionalArguments[i].longArgumentName) == 0 || strcmp(data->necessaryOptionalArguments[j].shortArgumentName, data->allCollectedOptionalArguments[i].shortArgumentName) == 0){
                found = TRUE;
            }
        }

        if(found == TRUE){
            found == FALSE;
        }
        else{
            return TRUE;
        }
    }

    return FALSE;
}

int checkIfCountOfCollectedPositionalArgumentsIsCorrect(argParserData *data){
    if(data->allCollectedPositionalArgumentsIndex == data->necessaryPositionalArgumentsIndex){
        return TRUE;
    }

    return FALSE;
}

int checkIfAllRequiredArgumentsWasGiven(argParserData *data){
    int found = FALSE;

    /* The strategy here is run the necessary array and compare if each element exists in collected array */
    for(int i = 0; i < data->necessaryOptionalArgumentsIndex; i++){
        if(data->necessaryOptionalArguments[i].isRequired == TRUE){
            for(int j = 0; j < data->allCollectedOptionalArgumentsIndex; j++){
                if(strcmp(data->allCollectedOptionalArguments[j].longArgumentName, data->necessaryOptionalArguments[i].longArgumentName) == 0 || strcmp(data->allCollectedOptionalArguments[j].shortArgumentName, data->necessaryOptionalArguments[i].shortArgumentName) == 0){
                    found = TRUE;
                }
            }

            if(found == TRUE){
                found = FALSE;
            }
            else{
                return FALSE;
            }
        }
    }

    return TRUE;
}

int pickupAllPositionalArguments(argParserData *data){
    int allCollectedPositionalArgumentBegin = 0;
    char bufferOfFormat[3] = {0};


    for(int i = 1; i < data->argc; i++){

        /* The positional argument consists in not starting with dashes */
        if(data->argv[i][0] != '-' && strncmp(data->argv[i], "--", 2) != 0){
            if(i != 1){

                /* Checking if the previous argv argument is a optional flag of type short*/
                if(data->argv[i - 1][0] == '-' && strncmp(data->argv[i - 1], "--" , 2) != 0){
                    sprintf(bufferOfFormat, "-%c", data->argv[i - 1][strlen(data->argv[i - 1]) - 1]);

                    /* Checking if the previous argument flag need a value, if not, the current value probably is a positional argument */
                    if(checkIfOptionalArgumentNeedValue(data, bufferOfFormat) == FALSE){
                        addPositionalArgumentInArray(data, &allCollectedPositionalArgumentBegin, i);
                    }
                }
                else{

                    /* Checking if the previous argv argument is a optional flag of type long */
                    if(strncmp(data->argv[i - 1], "--", 2) == 0){

                        /* If the previous flag don't need a value, then the current value is a positional argument */
                        if(checkIfOptionalArgumentNeedValue(data, data->argv[i - 1]) == FALSE){
                            addPositionalArgumentInArray(data, &allCollectedPositionalArgumentBegin, i);
                        }
                    }
                    else{

                        /* The code flow only reach here if the previous argument looks like a positional argument too,
                           in that case, there's no problem, and the current argument is positional */
                        addPositionalArgumentInArray(data, &allCollectedPositionalArgumentBegin, i);
                    }
                }
            }
            else{

                /* The code flow only reach here if the index 1 of argv looks like a positional argument, not exists a possible
                   previous flag, then the current argument is positional */
                addPositionalArgumentInArray(data, &allCollectedPositionalArgumentBegin, i);
            }
        }
    }

    return 0;
}

void addPositionalArgumentInArray(argParserData *data, int *allCollectedPositionalArgumentBegin, int i){
    strcpy(data->allCollectedPositionalArguments[*allCollectedPositionalArgumentBegin].argumentID, data->necessaryPositionalArguments[*allCollectedPositionalArgumentBegin].argumentID);

    data->allCollectedPositionalArguments[*allCollectedPositionalArgumentBegin].value = data->argv[i];

    *allCollectedPositionalArgumentBegin += 1;
    data->allCollectedPositionalArgumentsIndex += 1;
}

/* This function will load everything that is long argument from argv, right into allCollectedOptionalArguments array.
   This version is for short argument name */
int pickupAllShortArgumentNames(argParserData *data){
    names argumentNames;
    char bufferOfFormat[3] = {0};

    /* Loop to run through the whole argv */
    for(int i = 1; i < data->argc; i++){

        /* If the first char of string is a dash but the two first isn't dashes, then it is a short argument block */
        if(data->argv[i][0] == '-' && strncmp(data->argv[i], "--", 2) != 0){
            for(int j = 1; j < strlen(data->argv[i]); j++){
                sprintf(bufferOfFormat, "-%c", data->argv[i][j]);
                if(checkIfOptionalArgumentIsRequired(data, bufferOfFormat) == TRUE){
                    if(checkIfOptionalArgumentNeedValue(data, bufferOfFormat) == TRUE){

                        /* -1 represent the last char of string*/
                        if(j == strlen(data->argv[i]) - 1){
                            if(i + 1 < data->argc){
                                data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].needValue = TRUE;
                                data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].value = data->argv[i + 1];
                            }
                            else{
                                return ARGUMENT_WITHOUT_VALUE;
                            }
                        }
                        else{
                            return ARGUMENT_WITHOUT_VALUE;
                        }
                    }

                    argumentNames = getOppositeSizeOfArgumentName(data, bufferOfFormat);

                    strcpy(data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].longArgumentName, argumentNames.longArgumentName);
                    strcpy(data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].shortArgumentName, argumentNames.shortArgumentName);

                    data->allCollectedOptionalArgumentsIndex += 1;
                }
                else{
                    return ARGUMENT_NOT_REQUIRED;
                }
            }
        }
    }

    return 0;
}











/* This function will load everything that is long argument from argv, right into allCollectedOptionalArguments array.
   This version is for long argument name */
int pickupAllLongArgumentNames(argParserData *data){
    names argumentNames;

    /* Run through the whole argv to try find long arguments */
    for(int i = 1; i < data->argc; i++){

        /* Is possible know if is a long argument if it start with two dashes. "--" */
        if(strncmp(data->argv[i], "--", 2) == 0){

            /* Checking if the found argument is required by the programmer */
            if(checkIfOptionalArgumentIsRequired(data, data->argv[i]) == TRUE){

                /* Checking if the found argument need a value with it */
                if(checkIfOptionalArgumentNeedValue(data, data->argv[i]) == TRUE){
                    if(i + 1 < data->argc){
                        data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].needValue = TRUE;
                        data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].value = data->argv[i + 1];
                    }
                    else{
                        return ARGUMENT_WITHOUT_VALUE;
                    }
                }

                argumentNames = getOppositeSizeOfArgumentName(data, data->argv[i]);
                
                strcpy(data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].longArgumentName, argumentNames.longArgumentName);
                strcpy(data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].shortArgumentName, argumentNames.shortArgumentName);

                data->allCollectedOptionalArgumentsIndex += 1;
            }
            else{
                return ARGUMENT_NOT_REQUIRED;
            }
        }
    }

    return 0;
}


names getOppositeSizeOfArgumentName(argParserData *data, char *argumentName){
    names argumentNames;

    for(int i = 0; i < data->necessaryOptionalArgumentsIndex; i++){
        if(strcmp(data->necessaryOptionalArguments[i].longArgumentName, argumentName) == 0 || strcmp(data->necessaryOptionalArguments[i].shortArgumentName, argumentName) == 0){
            strcpy(argumentNames.longArgumentName, data->necessaryOptionalArguments[i].longArgumentName);
            strcpy(argumentNames.shortArgumentName, data->necessaryOptionalArguments[i].shortArgumentName);
        }
    }

    return argumentNames;
}


/* This function will check if a optional argument need a value after it */
int checkIfOptionalArgumentNeedValue(argParserData *data, char *argument){
    for(int i = 0; i < data->necessaryOptionalArgumentsIndex; i++){

        /* It's right that in some time this "if" will be true, but in the end has a return just to compiler be happy */
        if(strcmp(data->necessaryOptionalArguments[i].longArgumentName, argument) == 0 || strcmp(data->necessaryOptionalArguments[i].shortArgumentName, argument) == 0){
            return data->necessaryOptionalArguments[i].needValue;
        }
    }

    return FALSE;
}

/* Check if a argument was declared in code, if found in array of necessaries it was declared */
int checkIfOptionalArgumentIsRequired(argParserData *data, char *argument){
    for(int i = 0; i < data->necessaryOptionalArgumentsIndex; i++){
        if(strcmp(data->necessaryOptionalArguments[i].longArgumentName, argument) == 0 || strcmp(data->necessaryOptionalArguments[i].shortArgumentName, argument) == 0){
            return TRUE;
        }
    }

    return FALSE;
}