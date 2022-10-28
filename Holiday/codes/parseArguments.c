#include "./../Holiday.h"

void parseArguments(argParserData *data, int possibleErrorCode){
    int argvPosition = 1;

    while(argvPosition < data->argc){
        if(HOLIDAY__pickupAllLongArgumentNames(data, &argvPosition) == 0){
            if(argvPosition < data->argc){
                if(HOLIDAY__pickupAllShortArgumentNames(data, &argvPosition) != 0){
                    HOLIDAY__showHelpMessage(data, possibleErrorCode);
                }    
            }
            
        }
        else{
            HOLIDAY__showHelpMessage(data, possibleErrorCode);
        }
    }

    /* This if case is executed in sequence and if any error is reported from any process the program show the help message and exit */
    if(HOLIDAY__pickupAllPositionalArguments(data) != 0 || HOLIDAY__checkIfAllRequiredArgumentsWasGiven(data) == 0 || HOLIDAY__checkIfCountOfCollectedPositionalArgumentsIsCorrect(data) == 0 || HOLIDAY__checkIfUnknowArgumentsWerePassedToProgram(data) != 0){
        HOLIDAY__showHelpMessage(data, possibleErrorCode);
    }
}

int HOLIDAY__checkIfUnknowArgumentsWerePassedToProgram(argParserData *data){
    int found = FALSE;
    HOLIDAY__collectedOptionalArgumentListCell *q = data->allCollectedOptionalArguments;

    /* The strategy here is run the collected array and compare if each element exists in the necessary array */
    for(int i = 0; i < data->allCollectedOptionalArgumentsIndex; i++){
        if(HOLIDAY__searchNeededOptionalValueInList(q->longArgumentName, q->shortArgumentName, data->necessaryOptionalArguments) == NULL){
            return TRUE;
        }
        else{
            q = q->next;
        }
        /*
        if(strcmp(data->necessaryOptionalArguments[j].longArgumentName, data->allCollectedOptionalArguments[i].longArgumentName) == 0 || strcmp(data->necessaryOptionalArguments[j].shortArgumentName, data->allCollectedOptionalArguments[i].shortArgumentName) == 0){
            found = TRUE;
        }
        */
    }

    return FALSE;
}

int HOLIDAY__checkIfCountOfCollectedPositionalArgumentsIsCorrect(argParserData *data){
    if(data->allCollectedPositionalArgumentsIndex == data->necessaryPositionalArgumentsIndex){
        return TRUE;
    }
    
    return FALSE;
}

int HOLIDAY__checkIfAllRequiredArgumentsWasGiven(argParserData *data){
    int found = FALSE;
    HOLIDAY__neededOptionalArgumentListCell *q = data->necessaryOptionalArguments;
    HOLIDAY__collectedOptionalArgumentListCell *p;

    /* The strategy here is run the necessary array and compare if each element exists in collected array */
    for(int i = 0; i < data->necessaryOptionalArgumentsIndex; i++){
        p = data->allCollectedOptionalArguments;
        if(q->isRequired == TRUE){
            for(int j = 0; j < data->allCollectedOptionalArgumentsIndex; j++){
                if(strcmp(p->longArgumentName, q->longArgumentName) == 0 || strcmp(p->shortArgumentName, q->shortArgumentName) == 0){
                    found = TRUE;
                }
            }

            if(found == FALSE){
                return FALSE;
            }
            else{
                found = FALSE;
            }
            /*
            if(found == TRUE){
                found = FALSE;
            }
            else{
                return FALSE;
            }
            */
        }

        q = q->next;
    }

    return TRUE;
}

/* This function will run through the entire argv and check which argument one is a positional argument,
   but to do that all optional arguments need be verified before */
int HOLIDAY__pickupAllPositionalArguments(argParserData *data){
    char bufferOfFormat[3] = {0};
    int allCollectedPositionalArgumentBegin = 0;


    /* Loop to run through the entire argv to find all positional arguments */
    for(int i = 1; i < data->argc; i++){

        /* Check if the current argument is a long argument name */
        if(strncmp(data->argv[i], "--", 2) == 0){

            /* If long argument need a value, then the current and the next argument can't be a positional argument */
            if(HOLIDAY__checkIfOptionalArgumentNeedValue(data, data->argv[i]) == TRUE){

                /* Advance the argv index to next position that will be advanced by the for loop too */
                i += 1;
            }
        }
        else{

            /* Check if the current argument is a short argument block */
            if(data->argv[i][0] == '-' && strncmp(data->argv[i], "--", 2) != 0 && HOLIDAY__checkIfArgumentIsNumeric(&data->argv[i][1]) == FALSE){
                sprintf(bufferOfFormat, "-%c", data->argv[i][strlen(data->argv[i]) - 1]);

                /* Checking if the last flg of this block need a value */
                if(HOLIDAY__checkIfOptionalArgumentNeedValue(data, bufferOfFormat) == TRUE){

                    /* Advance the argv index to next position that will be advanced by the for loop too */
                    i += 1;
                }
            }
            else{

                /* If no one of options above was triggered, then the current argument is positional */
                HOLIDAY__appendCollectedPositional(data, &allCollectedPositionalArgumentBegin, i);
            }
        }
    }

    return 0;
}



/* This function will load everything that is long argument from argv, right into allCollectedOptionalArguments array.
   This version is for short argument name */
int HOLIDAY__pickupAllShortArgumentNames(argParserData *data, int *argvPosition){
    names argumentNames;
    HOLIDAY__collectedOptionalArgumentListCell newCollectedOptionalArgument;
    char bufferOfFormat[3] = {0};
    int currentArgvPosition = *argvPosition;

    /* Loop to run through the whole argv */

    /* If the first char of string is a dash but the two first isn't dashes, then it is a short argument block */
    if(data->argv[currentArgvPosition][0] == '-' && strncmp(data->argv[currentArgvPosition], "--", 2) != 0){
        if(HOLIDAY__checkIfArgumentIsNumeric(&data->argv[currentArgvPosition][1]) == FALSE){
            for(int j = 1; j < strlen(data->argv[currentArgvPosition]); j++){
                sprintf(bufferOfFormat, "-%c", data->argv[currentArgvPosition][j]);
                if(HOLIDAY__checkIfOptionalArgumentIsRequired(data, bufferOfFormat) == TRUE){
                    if(HOLIDAY__checkIfOptionalArgumentNeedValue(data, bufferOfFormat) == TRUE){

                        /* -1 represent the last char of string*/
                        if(j == strlen(data->argv[currentArgvPosition]) - 1){
                            if(currentArgvPosition + 1 < data->argc){
                                newCollectedOptionalArgument.needValue = TRUE;
                                newCollectedOptionalArgument.value = data->argv[currentArgvPosition + 1];

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

                    argumentNames = HOLIDAY__getOppositeSizeOfArgumentName(data, bufferOfFormat);

                    strcpy(newCollectedOptionalArgument.longArgumentName, argumentNames.longArgumentName);
                    strcpy(newCollectedOptionalArgument.shortArgumentName, argumentNames.shortArgumentName);

                    HOLIDAY__appendCollectedOptionalArgument(data, newCollectedOptionalArgument);

                    data->allCollectedOptionalArgumentsIndex += 1;
                    *argvPosition += 1;
                }
                else{
                    return ARGUMENT_NOT_REQUIRED;
                }
            }
        }

    }
    
    *argvPosition += 1;
    return 0;
}

int HOLIDAY__checkIfArgumentIsNumeric(char *argument){
    int isNumeric = TRUE;
    short argumentLength = strlen(argument);
    int i = 0;

    while(i < argumentLength && isNumeric == TRUE){
        if(!isdigit(argument[i])){
            isNumeric = FALSE;
        }

        i++;
    }


    return isNumeric;
}



/* This function will load everything that is long argument from argv, right into allCollectedOptionalArguments array.
   This version is for long argument name */
int HOLIDAY__pickupAllLongArgumentNames(argParserData *data, int *argvPosition){
    names argumentNames;
    HOLIDAY__collectedOptionalArgumentListCell newCollectedOptionalArgument;
    int currentArgvPosition = *argvPosition;

    /* Run through the whole argv to try find long arguments */

    /* Is possible know if is a long argument if it start with two dashes. "--" */
    if(strncmp(data->argv[currentArgvPosition], "--", 2) == 0){

        /* Checking if the found argument is required by the programmer */
        if(HOLIDAY__checkIfOptionalArgumentIsRequired(data, data->argv[currentArgvPosition]) == TRUE){

            /* Checking if the found argument need a value with it */
            if(HOLIDAY__checkIfOptionalArgumentNeedValue(data, data->argv[currentArgvPosition]) == TRUE){
                if(currentArgvPosition + 1 < data->argc){
                    newCollectedOptionalArgument.needValue = TRUE;
                    newCollectedOptionalArgument.value = data->argv[currentArgvPosition + 1];

                    /* This addition will be added to the addition right down here to jump through the optional value */
                    *argvPosition += 1;
                }
                else{
                    return ARGUMENT_WITHOUT_VALUE;
                }
            }

            argumentNames = HOLIDAY__getOppositeSizeOfArgumentName(data, data->argv[currentArgvPosition]);
                
            strcpy(newCollectedOptionalArgument.longArgumentName, argumentNames.longArgumentName);
            strcpy(newCollectedOptionalArgument.shortArgumentName, argumentNames.shortArgumentName);

            HOLIDAY__appendCollectedOptionalArgument(data, newCollectedOptionalArgument);

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


names HOLIDAY__getOppositeSizeOfArgumentName(argParserData *data, char *argumentName){
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
int HOLIDAY__checkIfOptionalArgumentNeedValue(argParserData *data, char *argument){
    for(int i = 0; i < data->necessaryOptionalArgumentsIndex; i++){

        /* It's right that in some time this "if" will be true, but in the end has a return just to compiler be happy */
        if(strcmp(data->necessaryOptionalArguments[i].longArgumentName, argument) == 0 || strcmp(data->necessaryOptionalArguments[i].shortArgumentName, argument) == 0){
            return data->necessaryOptionalArguments[i].needValue;
        }
    }

    return FALSE;
}

/* Check if a argument was declared in code, if found in array of necessaries it was declared */
int HOLIDAY__checkIfOptionalArgumentIsRequired(argParserData *data, char *argument){
    for(int i = 0; i < data->necessaryOptionalArgumentsIndex; i++){
        if(strcmp(data->necessaryOptionalArguments[i].longArgumentName, argument) == 0 || strcmp(data->necessaryOptionalArguments[i].shortArgumentName, argument) == 0){
            return TRUE;
        }
    }

    return FALSE;
}