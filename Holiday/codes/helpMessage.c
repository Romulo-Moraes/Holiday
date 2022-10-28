#include "./../Holiday.h"

void HOLIDAY__showHelpMessage(argParserData *data, int exitCode){
    HOLIDAY__neededPositionalArgumentListCell *requiredPositionalArgumentsPointerCopy = data->necessaryPositionalArguments;
    HOLIDAY__neededOptionalArgumentListCell * optionalArgumentsPointerCopy = data->necessaryOptionalArguments;
    int programAboutLength = strlen(data->programAbout);

    if(programAboutLength > 0){
        printf("%s\n\n", data->programAbout);
    }

    //printf("%s --> How to use the program\n\n", strlen(data->programName) > 0 ? data->programName : data->argv[0]);
    printf("Usage: %s [OPTIONS]\n\n", data->programName);

    //printf("%s %s%s\n", strlen(data->programName) > 0 ? data->programName : data->argv[0], data->necessaryPositionalArgumentsIndex > 0 ? "<[Positional arguments]> " : " ", data->necessaryOptionalArgumentsIndex > 0 ? "--<[Optional argument]> or -<[Short optional argument]> <[Short optional argument value]>" : "");

    printf("Options:\n");
    while(requiredPositionalArgumentsPointerCopy != NULL){
        printf("\t%s --> %s (required)\n", requiredPositionalArgumentsPointerCopy->argumentID, requiredPositionalArgumentsPointerCopy->helpMessage);
        requiredPositionalArgumentsPointerCopy = requiredPositionalArgumentsPointerCopy->next;
    }

    puts("");

    while(optionalArgumentsPointerCopy != NULL){
        printf("\t%s / %s --> %s %s\n", optionalArgumentsPointerCopy->longArgumentName, optionalArgumentsPointerCopy->shortArgumentName, optionalArgumentsPointerCopy->helpMessage, optionalArgumentsPointerCopy->isRequired ? "(required)" : "");
        optionalArgumentsPointerCopy = optionalArgumentsPointerCopy->next;
    }

    puts("\nEnd of help message");  
    exit(exitCode);
}