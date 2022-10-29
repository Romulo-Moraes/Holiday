#include "./../Holiday.h"

int optionalWasSet(argParserData *data, char *argumentName){
    HOLIDAY__collectedOptionalArgumentListCell *theArgument = HOLIDAY__searchCollectedOptionalValueInList(argumentName, data->allCollectedOptionalArguments);

    return theArgument == NULL ? FALSE : TRUE;
}