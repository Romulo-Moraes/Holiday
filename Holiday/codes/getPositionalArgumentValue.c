#include "./../Holiday.h"
#include <string.h>


char* getPositionalArgumentValue(argParserData *data, char *argumentID){

    /* This run through the entire collected array checking if argumentID match with some collected positional argument */
    for(int i = 0; i < data->allCollectedPositionalArgumentsIndex; i++){
        if(strcmp(data->allCollectedPositionalArguments[i].argumentID, argumentID) == 0){
            return data->allCollectedPositionalArguments[i].value;
        }
    }

    return NULL;
}