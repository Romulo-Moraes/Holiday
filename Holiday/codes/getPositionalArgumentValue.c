#include "./../Holiday.h"


char* getPositionalArgumentValue(argParserData *data, char *argumentID){
    HOLIDAY__collectedPositionalArgumentListCell *cellOfArgumentList = HOLIDAY__searchCollectedPositionalValueInList(argumentID, data->allCollectedPositionalArguments);

    if(cellOfArgumentList == NULL){
        return NULL;
    }
    else{
        return cellOfArgumentList->value;
    }
}