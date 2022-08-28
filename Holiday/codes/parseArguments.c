#include "./../Holiday.h"

void parseArguments(argParserData *data, int enableBreak){
    int argvPosition = 1;

    while(argvPosition < data->argc){
        if(pickupAllLongArgumentNames(data, &argvPosition) == 0){
            if(argvPosition < data->argc){
                if(pickupAllShortArgumentNames(data, &argvPosition) != 0){
                    showHelpMessage(data, 0);
                }    
            }
            
        }
        else{
            showHelpMessage(data, 0);
        }
    }

    /* This if case is executed in sequence and if any error is reported from any process the program show the help message and exit */
    if(pickupAllPositionalArguments(data) != 0 || checkIfAllRequiredArgumentsWasGiven(data) == 0 || checkIfCountOfCollectedPositionalArgumentsIsCorrect(data) == 0 || checkIfUnknowArgumentsWasPassedToProgram(data) != 0){
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

/* This function will run through the entire argv and check which argument one is a positional argument,
   but to do that all optional arguments need be verified before */
int pickupAllPositionalArguments(argParserData *data){
    char bufferOfFormat[3] = {0};
    int allCollectedPositionalArgumentBegin = 0;


    /* Loop to run through the entire argv to find all positional arguments */
    for(int i = 1; i < data->argc; i++){

        /* Check if the current argument is a long argument name */
        if(strncmp(data->argv[i], "--", 2) == 0){

            /* If long argument need a value, then the current and the next argument can't be a positional argument */
            if(checkIfOptionalArgumentNeedValue(data, data->argv[i]) == TRUE){

                /* Advance the argv index to next position that will be advanced by the for loop too */
                i += 1;
            }
        }
        else{

            /* Check if the current argument is a short argument block */
            if(data->argv[i][0] == '-' && strncmp(data->argv[i], "--", 2) != 0){
                sprintf(bufferOfFormat, "-%c", data->argv[i][strlen(data->argv[i]) - 1]);

                /* Checking if the last flg of this block need a value */
                if(checkIfOptionalArgumentNeedValue(data, bufferOfFormat) == TRUE){

                    /* Advance the argv index to next position that will be advanced by the for loop too */
                    i += 1;
                }
            }
            else{

                /* If no one of options above was triggered, then the current argument is positional */
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
int pickupAllShortArgumentNames(argParserData *data, int *argvPosition){
    names argumentNames;
    char bufferOfFormat[3] = {0};
    int currentArgvPosition = *argvPosition;

    /* Loop to run through the whole argv */

    /* If the first char of string is a dash but the two first isn't dashes, then it is a short argument block */
    if(data->argv[currentArgvPosition][0] == '-' && strncmp(data->argv[currentArgvPosition], "--", 2) != 0){
        for(int j = 1; j < strlen(data->argv[currentArgvPosition]); j++){
            sprintf(bufferOfFormat, "-%c", data->argv[currentArgvPosition][j]);
            if(checkIfOptionalArgumentIsRequired(data, bufferOfFormat) == TRUE){
                if(checkIfOptionalArgumentNeedValue(data, bufferOfFormat) == TRUE){

                    /* -1 represent the last char of string*/
                    if(j == strlen(data->argv[currentArgvPosition]) - 1){
                        if(currentArgvPosition + 1 < data->argc){
                            data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].needValue = TRUE;
                            data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].value = data->argv[currentArgvPosition + 1];

                            /* This addition will be added to the addition right down here to jump through the optional value */
                            *argvPosition += 1;
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
                *argvPosition += 1;

            }
            else{
                return ARGUMENT_NOT_REQUIRED;
            }
        }
    }
    
    *argvPosition += 1;
    return 0;
}











/* This function will load everything that is long argument from argv, right into allCollectedOptionalArguments array.
   This version is for long argument name */
int pickupAllLongArgumentNames(argParserData *data, int *argvPosition){
    names argumentNames;
    int currentArgvPosition = *argvPosition;

    /* Run through the whole argv to try find long arguments */

    /* Is possible know if is a long argument if it start with two dashes. "--" */
    if(strncmp(data->argv[currentArgvPosition], "--", 2) == 0){

        /* Checking if the found argument is required by the programmer */
        if(checkIfOptionalArgumentIsRequired(data, data->argv[currentArgvPosition]) == TRUE){

            /* Checking if the found argument need a value with it */
            if(checkIfOptionalArgumentNeedValue(data, data->argv[currentArgvPosition]) == TRUE){
                if(currentArgvPosition + 1 < data->argc){
                    data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].needValue = TRUE;
                    data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].value = data->argv[currentArgvPosition + 1];

                    /* This addition will be added to the addition right down here to jump through the optional value */
                    *argvPosition += 1;
                }
                else{
                    return ARGUMENT_WITHOUT_VALUE;
                }
            }

            argumentNames = getOppositeSizeOfArgumentName(data, data->argv[currentArgvPosition]);
                
            strcpy(data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].longArgumentName, argumentNames.longArgumentName);
            strcpy(data->allCollectedOptionalArguments[data->allCollectedOptionalArgumentsIndex].shortArgumentName, argumentNames.shortArgumentName);

            data->allCollectedOptionalArgumentsIndex += 1;
            *argvPosition += 1;

            return 0;
        }
        else{
            return ARGUMENT_NOT_REQUIRED;
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