#include "./../Holiday.h"

void HOLIDAY__showHelpMessage(argParserData *data){
    HOLIDAY__neededPositionalArgumentListCell *requiredPositionalArgumentsPointerCopy = data->necessaryPositionalArguments;
    HOLIDAY__neededOptionalArgumentListCell * optionalArgumentsPointerCopy = data->necessaryOptionalArguments;
    int programAboutLength = strlen(data->programAbout);

    if(programAboutLength > 0){
        printf("%s\n\n", data->programAbout);
    }

    printf("Usage: %s [OPTIONS]\n\n", data->programName);


    printf("Options:\n");
    while(requiredPositionalArgumentsPointerCopy != NULL){
        printf("\t%s --> %s (required)\n", requiredPositionalArgumentsPointerCopy->argumentID, requiredPositionalArgumentsPointerCopy->helpMessage);
        requiredPositionalArgumentsPointerCopy = requiredPositionalArgumentsPointerCopy->next;
    }

    puts("");

    while(optionalArgumentsPointerCopy != NULL){
        printf("\t%s / %s %s --> %s %s\n", optionalArgumentsPointerCopy->longArgumentName, optionalArgumentsPointerCopy->shortArgumentName, optionalArgumentsPointerCopy->needValue == TRUE ? "<VALUE>" : "",optionalArgumentsPointerCopy->helpMessage, optionalArgumentsPointerCopy->isRequired ? "(required)" : "");
        optionalArgumentsPointerCopy = optionalArgumentsPointerCopy->next;
    }

    puts("\nEnd of help message");  
    exit(0);
}