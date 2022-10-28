#include "./../Holiday.h"

char* getOptionalArgumentValue(argParserData *data, char *argumentName){
    HOLIDAY__collectedOptionalArgumentListCell *cellOfArgumentList = HOLIDAY__searchCollectedOptionalValueInList(argumentName, data->allCollectedOptionalArguments);

    return cellOfArgumentList == NULL ? NULL : cellOfArgumentList->value;
}