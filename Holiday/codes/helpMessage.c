#include "./../Holiday.h"

void HOLIDAY__showHelpMessage(argParserData *data, int exitCode){
    int programAboutLength = strlen(data->programAbout);

    printf("%s --> How to use the program\n\n", strlen(data->programName) > 0 ? data->programName : data->argv[0]);

    printf("%s %s%s\n", strlen(data->programName) > 0 ? data->programName : data->argv[0], data->necessaryPositionalArgumentsIndex > 0 ? "<[Positional arguments]> " : " ", data->necessaryOptionalArgumentsIndex > 0 ? "--<[Optional argument]> or -<[Short optional argument]> <[Short optional argument value]>" : "");

    if(programAboutLength > 0){
        printf("About: %s\n\n", data->programAbout);
    }

    for(int i = 0; i < data->necessaryPositionalArgumentsIndex; i++){
        printf("%s --> %s (required)\n", data->necessaryPositionalArguments[i].argumentID, data->necessaryPositionalArguments[i].helpMessage);
    }

    for(int i = 0; i < data->necessaryOptionalArgumentsIndex; i++){
        printf("%s / %s --> %s %s\n", data->necessaryOptionalArguments[i].longArgumentName, data->necessaryOptionalArguments[i].shortArgumentName, data->necessaryOptionalArguments[i].helpMessage, data->necessaryOptionalArguments[i].isRequired ? "(required)" : "");
    }

    puts("\nEnd of help message");  
    exit(exitCode);
}