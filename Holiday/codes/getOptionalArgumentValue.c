#include "./../Holiday.h"

char* getOptionalArgumentValue(argParserData *data, char *argumentName){
    HOLIDAY__collectedOptionalArgumentListCell *cellOfArgumentList = HOLIDAY__searchCollectedOptionalValueInList(argumentName, data->allCollectedOptionalArguments);

    if(cellOfArgumentList == NULL){
        return NULL;
    }
    else{
        return cellOfArgumentList->value;
    }
}