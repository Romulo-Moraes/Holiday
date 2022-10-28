#include "./../Holiday.h"

void HOLIDAY__appendPositionalArgument(argParserData *data, HOLIDAY__neededPositionalArgumentListCell newNecessaryArgument){
    HOLIDAY__neededPositionalArgumentListCell *theNewArgument = (HOLIDAY__neededPositionalArgumentListCell*) malloc(sizeof(HOLIDAY__neededPositionalArgumentListCell));
    HOLIDAY__neededPositionalArgumentListCell *p = NULL, *q = NULL;

    if(theNewArgument!= NULL){
        strcpy(theNewArgument->argumentID, newNecessaryArgument.argumentID);
        strcpy(theNewArgument->helpMessage, newNecessaryArgument.helpMessage);
        newNecessaryArgument.next = NULL;

        if(data->necessaryPositionalArguments == NULL){
            data->necessaryPositionalArguments = theNewArgument;
        }
        else{
            p = data->necessaryPositionalArguments;
            q = p->next;

            while(q != NULL){
                p = q;
                q = q->next;
            }

            p->next = theNewArgument;
        }
    }
    else{
        //TODO!!! (Fail on get heap memory)
    }
}

void HOLIDAY__appendOptionalArgument(argParserData *data, HOLIDAY__neededOptionalArgumentListCell newNecessaryArgument){
    HOLIDAY__neededOptionalArgumentListCell *theNewArgument = (HOLIDAY__neededOptionalArgumentListCell*) malloc(sizeof(HOLIDAY__neededOptionalArgumentListCell));
    HOLIDAY__neededOptionalArgumentListCell *p = NULL, *q = NULL;


    if(theNewArgument!= NULL){
        strcpy(theNewArgument->longArgumentName, newNecessaryArgument.longArgumentName);
        strcpy(theNewArgument->shortArgumentName, newNecessaryArgument.shortArgumentName);
        strcpy(theNewArgument->helpMessage, newNecessaryArgument.helpMessage);
        theNewArgument->isRequired = newNecessaryArgument.isRequired;
        theNewArgument->needValue = newNecessaryArgument.needValue;
        theNewArgument->next = NULL;

        if(data->necessaryOptionalArguments == NULL){
            data->necessaryOptionalArguments = theNewArgument;
        }
        else{
            p = data->necessaryOptionalArguments;
            q = p->next;

            while(q != NULL){
                p = q;
                q = q->next;
            }

            p->next = theNewArgument;
        }
    }
    else{
        //TODO!!! (Fail on get heap memory)
    }
}


void HOLIDAY__appendCollectedOptionalArgument(argParserData *data, HOLIDAY__collectedOptionalArgumentListCell newArgument){   
    HOLIDAY__collectedOptionalArgumentListCell *theNewArgument = (HOLIDAY__collectedOptionalArgumentListCell*) malloc(sizeof(HOLIDAY__collectedOptionalArgumentListCell));
    HOLIDAY__collectedOptionalArgumentListCell *p = NULL, *q = NULL;

    if(theNewArgument != NULL){
        theNewArgument->needValue = newArgument.needValue;
        strcpy(theNewArgument->longArgumentName, newArgument.longArgumentName);
        strcpy(theNewArgument->shortArgumentName, newArgument.shortArgumentName);
        theNewArgument->value = newArgument.value;
        theNewArgument->next = NULL;

        if(data->allCollectedOptionalArguments == NULL){
            data->allCollectedOptionalArguments = theNewArgument;
        }
        else{
            p = data->allCollectedOptionalArguments;
            q = p->next;

            while(q != NULL){
                p = q;
                q = q->next;
            }

            p->next = theNewArgument;
        }
    }
    else{
        //TODO!!! (Fail on get heap memory)
    }
}

HOLIDAY__neededPositionalArgumentListCell *HOLIDAY__searchNeededPositionalValueInListByIndex(int index, HOLIDAY__neededPositionalArgumentListCell *neededList){
    for(int i = 0; i < index; i++){
        neededList = neededList->next;
    }

    return neededList;
}

void HOLIDAY__appendCollectedPositional(argParserData *data, int *allCollectedPositionalArgumentBegin, int i){
    HOLIDAY__collectedPositionalArgumentListCell *theNewArgument = (HOLIDAY__collectedPositionalArgumentListCell*) malloc(sizeof(HOLIDAY__collectedPositionalArgumentListCell));
    HOLIDAY__collectedPositionalArgumentListCell *p = NULL, *q = NULL;

    if(theNewArgument != NULL){
        strcpy(theNewArgument->argumentID, HOLIDAY__searchNeededPositionalValueInListByIndex(*allCollectedPositionalArgumentBegin, data->necessaryPositionalArguments)->argumentID);
        theNewArgument->value = data->argv[i];
        theNewArgument->next = NULL;

        if(data->allCollectedPositionalArguments == NULL){
            data->allCollectedPositionalArguments = theNewArgument;
        }
        else{
            p = data->allCollectedPositionalArguments;
            q = p->next;

            while(q != NULL){
                p = q;
                q = q->next;
            }

            p->next = theNewArgument;
        }
    }
    else{
        //TODO!!! (Fail on get heap memory)
    }

    *allCollectedPositionalArgumentBegin += 1;
    data->allCollectedPositionalArgumentsIndex += 1;
}

HOLIDAY__neededOptionalArgumentListCell *HOLIDAY__searchNeededOptionalValueInList(char fullName[128], char shortName[3], HOLIDAY__neededOptionalArgumentListCell *neededList){
    while(neededList != NULL && strcmp(neededList->longArgumentName, fullName) != 0 && strcmp(neededList->shortArgumentName, shortName) != 0){
        neededList = neededList->next;
    }

    return neededList;
}

HOLIDAY__collectedOptionalArgumentListCell *HOLIDAY__searchCollectedOptionalValueInList(char *argumentName, HOLIDAY__collectedOptionalArgumentListCell *collectedArgumentList){
    while(collectedArgumentList != NULL && strcmp(collectedArgumentList->longArgumentName, argumentName) != 0 && strcmp(collectedArgumentList->shortArgumentName, argumentName) != 0){
        collectedArgumentList = collectedArgumentList->next;
    }

    return collectedArgumentList;
}

HOLIDAY__collectedPositionalArgumentListCell *HOLIDAY__searchCollectedPositionalValueInList(char *argumentName, HOLIDAY__collectedPositionalArgumentListCell *collectedArgumentList){
    while(collectedArgumentList != NULL && strcmp(collectedArgumentList->argumentID, argumentName) != 0){
        collectedArgumentList = collectedArgumentList->next;
    }

    return collectedArgumentList;
}