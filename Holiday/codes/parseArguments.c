#include "./../Holiday.h"

int parseArguments(argParserData *data){
    int argvPosition = 1;
    int heapAllocationStatus = HEAP_REQUEST_FINE;

    while(argvPosition < data->argc){
        if(HOLIDAY__pickupAllLongArgumentNames(data, &argvPosition, &heapAllocationStatus) == 0){
            if(heapAllocationStatus == HEAP_REQUEST_FINE){
                if(argvPosition < data->argc){
                    if(HOLIDAY__pickupAllShortArgumentNames(data, &argvPosition, &heapAllocationStatus) != 0){
                        HOLIDAY__showHelpMessage(data);
                    }
                    else{
                        if(heapAllocationStatus == HEAP_REQUEST_FAULT){
                            if(data->notifyOnMemoryFault == TRUE){
                                return HEAP_REQUEST_FAULT;
                            }
                            else{
                                puts(HEAP_ALLOCATION_FAULT_MESSAGE);
                                exit(1);
                            }
                        }
                    }
                }   
            }
            else{
                if(data->notifyOnMemoryFault == TRUE){
                    return HEAP_REQUEST_FAULT;
                }
                else{
                    puts(HEAP_ALLOCATION_FAULT_MESSAGE);
                    exit(1);
                }
            }
        }
        else{
            HOLIDAY__showHelpMessage(data);
        }
    }

    HOLIDAY__pickupAllPositionalArguments(data, &heapAllocationStatus);
    if(heapAllocationStatus == HEAP_REQUEST_FAULT){
        if(data->notifyOnMemoryFault == TRUE){
            return HEAP_REQUEST_FAULT;
        }
        else{
            puts(HEAP_ALLOCATION_FAULT_MESSAGE);
            exit(1);
        }
    }

    /* This if case is executed in sequence and if any error is reported from any process the program show the help message and exit */
    if(HOLIDAY__checkIfAllRequiredArgumentsWereGiven(data) == 0 || HOLIDAY__checkIfCountOfCollectedPositionalArgumentsIsCorrect(data) == 0 || HOLIDAY__checkIfUnknowArgumentsWerePassedToProgram(data) != 0){
        HOLIDAY__showHelpMessage(data);
    }


    return HEAP_REQUEST_FINE;
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
    }

    return FALSE;
}

int HOLIDAY__checkIfCountOfCollectedPositionalArgumentsIsCorrect(argParserData *data){
    if(data->allCollectedPositionalArgumentsIndex == data->necessaryPositionalArgumentsIndex){
        return TRUE;
    }
    
    return FALSE;
}

int HOLIDAY__checkIfAllRequiredArgumentsWereGiven(argParserData *data){
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
                p = p->next;
            }

            if(found == FALSE){
                return FALSE;
            }
            else{
                found = FALSE;
            }
        }

        q = q->next;
    }

    return TRUE;
}

/* This function will run through the entire argv and check which argument one is a positional argument,
   but to do that all optional arguments need be verified before */
int HOLIDAY__pickupAllPositionalArguments(argParserData *data, int *heapAllocationStatus){
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
                *heapAllocationStatus = HOLIDAY__appendCollectedPositional(data, &allCollectedPositionalArgumentBegin, i);
            }
        }
    }

    return 0;
}



/* This function will load everything that is long argument from argv, right into allCollectedOptionalArguments array.
   This version is for short argument name */
int HOLIDAY__pickupAllShortArgumentNames(argParserData *data, int *argvPosition, int *heapAllocationStatus){
    int alreadyJumpedToTwoDashesArgument = FALSE;
    names argumentNames;
    HOLIDAY__collectedOptionalArgumentListCell newCollectedOptionalArgument;
    char bufferOfFormat[3] = {0};
    int currentArgvPosition = *argvPosition;
    int currentArgumentSize;

    /* Loop to run through the whole argv */

    /* If the first char of string is a dash but the two first isn't dashes, then it is a short argument block */
    if(data->argv[currentArgvPosition][0] == '-' && strncmp(data->argv[currentArgvPosition], "--", 2) != 0){
        currentArgumentSize = strlen(data->argv[currentArgvPosition]);
        if(HOLIDAY__checkIfArgumentIsNumeric(&data->argv[currentArgvPosition][1]) == FALSE){
            for(int j = 1; j < currentArgumentSize; j++){
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

                    *heapAllocationStatus = HOLIDAY__appendCollectedOptionalArgument(data, newCollectedOptionalArgument);

                    data->allCollectedOptionalArgumentsIndex += 1;

                    // The pointer of current argument in argv can only walk if
                    // reached the last flag of short argument block
                    if(j == currentArgumentSize - 1){
                        *argvPosition += 1;
                    }

                    alreadyJumpedToTwoDashesArgument = strncmp(data->argv[*argvPosition], "--", 2) == 0 ? TRUE : FALSE;
                }
                else{
                    return ARGUMENT_NOT_REQUIRED;
                }
            }
        }

    }

    if(strncmp(data->argv[currentArgvPosition], "--", 2) != 0 && alreadyJumpedToTwoDashesArgument == FALSE){
        *argvPosition += 1;
    }

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
int HOLIDAY__pickupAllLongArgumentNames(argParserData *data, int *argvPosition, int *heapAllocationStatus){
    names argumentNames;
    HOLIDAY__collectedOptionalArgumentListCell newCollectedOptionalArgument;
    memset(&newCollectedOptionalArgument, '\0', sizeof(HOLIDAY__collectedOptionalArgumentListCell));
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

            *heapAllocationStatus = HOLIDAY__appendCollectedOptionalArgument(data, newCollectedOptionalArgument);

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
    HOLIDAY__neededOptionalArgumentListCell *theArgument = HOLIDAY__searchNeededOptionalValueInList(argumentName, argumentName, data->necessaryOptionalArguments);

    strcpy(argumentNames.longArgumentName, theArgument->longArgumentName);
    strcpy(argumentNames.shortArgumentName, theArgument->shortArgumentName);

    return argumentNames;
}


/* This function will check if a optional argument need a value after it */
int HOLIDAY__checkIfOptionalArgumentNeedValue(argParserData *data, char *argument){
    return HOLIDAY__searchNeededOptionalValueInList(argument,argument, data->necessaryOptionalArguments)->needValue;
}

/* Check if a argument was declared in code, if found in array of necessaries it was declared */
int HOLIDAY__checkIfOptionalArgumentIsRequired(argParserData *data, char *argument){
    HOLIDAY__neededOptionalArgumentListCell *theArgument = HOLIDAY__searchNeededOptionalValueInList(argument, argument, data->necessaryOptionalArguments);

    return theArgument == NULL ? FALSE : TRUE;
}