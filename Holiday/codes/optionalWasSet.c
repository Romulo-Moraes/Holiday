#include "./../Holiday.h"

int optionalWasSet(argParserData *data, char *argumentName){
    HOLIDAY__collectedOptionalArgumentListCell *theArgument = HOLIDAY__searchCollectedOptionalValueInList(argumentName, data->allCollectedOptionalArguments);

    if(theArgument == NULL){
        return FALSE;
    }
    else{
        return TRUE;
    }

    /*
    /* This will run through the entire collected array and check, one by one, if the argumentName match with that short or long argument name
    for(int i = 0; i < data->allCollectedOptionalArgumentsIndex; i++){
        if(strcmp(data->allCollectedOptionalArguments[i].longArgumentName, argumentName) == 0 || strcmp(data->allCollectedOptionalArguments[i].shortArgumentName, argumentName) == 0 ){
            return TRUE;
        }
    }

    return FALSE;
    */
}