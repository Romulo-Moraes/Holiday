#include "./../Holiday.h"
#include <string.h>

char* getOptionalArgumentValue(argParserData *data, char *argumentName){

    /* This run the entire collected array checking if any short or long argument name match with argumentName, and then return the value */
    for(int i = 0; i < data->allCollectedOptionalArgumentsIndex; i++){
        if(strcmp(data->allCollectedOptionalArguments[i].longArgumentName, argumentName) == 0 || strcmp(data->allCollectedOptionalArguments[i].shortArgumentName, argumentName) == 0){
            return data->allCollectedOptionalArguments[i].value;
        }
    }

    return NULL;
}