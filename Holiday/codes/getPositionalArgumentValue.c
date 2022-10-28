#include "./../Holiday.h"


char* getPositionalArgumentValue(argParserData *data, char *argumentID){
    HOLIDAY__collectedPositionalArgumentListCell *cellOfArgumentList = HOLIDAY__searchCollectedPositionalValueInList(argumentID, data->allCollectedPositionalArguments);

    return cellOfArgumentList == NULL ? NULL : cellOfArgumentList->value;
}