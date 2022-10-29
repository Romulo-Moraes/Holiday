#include <stdio.h>
#include "Holiday/Holiday.h"
#include <stdlib.h>

void printOptional(argParserData *data, char *argumentName){
    printf("%s triggered: %s\n", argumentName, optionalWasSet(data, argumentName) == TRUE ? "true" : "false");
    printf("%s value: %s\n\n", argumentName, getOptionalArgumentValue(data, argumentName) == NULL ? "NULL" : getOptionalArgumentValue(data, argumentName));
}
/*
void printCollectedArguments(argParserData *data){
    while(data->allCollectedOptionalArguments != NULL){
        printf("Long: %s\nShort: %s\nValue: %s\n\n", data->allCollectedOptionalArguments->longArgumentName, data->allCollectedOptionalArguments->shortArgumentName, data->allCollectedOptionalArguments->value);
        data->allCollectedOptionalArguments = data->allCollectedOptionalArguments->next;
    }
}
*/

int main(int argc, char *argv[])
{
    argParserData data = argParserInit(argc, argv, "calc", "Calculate two numbers given in program call", FALSE);

    addPositionalArgument(&data, "number1", "Pass a random number to program");
    addOptionalArgument(&data, "--age", "-a", TRUE, "Pass your age",FALSE);
    addPositionalArgument(&data, "number2", "Pass another random number");
    addOptionalArgument(&data, "--name", "-n", TRUE, "Pass your name", TRUE);
    addPositionalArgument(&data, "number3", "A lot of random numbers...");
    addOptionalArgument(&data, "--is-human", "-i", FALSE, "Say if you're human", TRUE);
    addPositionalArgument(&data, "number4", "Damn, stop of random numbers");
    addOptionalArgument(&data, "--straight", "-s", FALSE, "Say if you're straight", FALSE);


    parseArguments(&data);

    //printf("%d\n", optionalWasSet(&data, "--straight"));

    printf("Number1: %s\n\n", getPositionalArgumentValue(&data, "number1"));
    printOptional(&data, "--name");
    printf("Number2: %s\n\n", getPositionalArgumentValue(&data, "number2"));
    printOptional(&data, "--age");
    printf("Number3: %s\n\n", getPositionalArgumentValue(&data, "number3"));
    printOptional(&data, "--is-human");
    printf("Number4: %s\n\n", getPositionalArgumentValue(&data, "number4"));
    printOptional(&data, "-s");
    destroyHoliday(&data);
    return 0;
/*
    int number1, number2;
    argParserData data = argParserInit(argc, argv, "calc", "Calculate two numbers given in program call", TRUE);

    addPositionalArgument(&data, "name", "Your name");
    //addOptionalArgument(&data, "--name", "-n", TRUE, "Your name", TRUE);

    printf("%d\n", parseArguments(&data));

    //printf("%s\n", getOptionalArgumentValue(&data, "--name"));

    return 0;
*/
/*
    number1 = atoi(getPositionalArgumentValue(&data, "number1"));
    number2 = atoi(getPositionalArgumentValue(&data, "number2"));


    if (optionalWasSet(&data, "--operation") == TRUE)
    {
        switch (getOptionalArgumentValue(&data, "--operation")[0])
        {
        case '-':
            printf("%d\n", number1 - number2);
            break;
        case '+':
            printf("%d\n", number1 + number2);
            break;
        case '/':
            printf("%d\n", number1 / number2);
            break;
        case '*':
            printf("%d\n", number1 * number2);
            break;
        default:
            puts("Unknow operation");
            break;
        }
    }
    else
    {
        puts("Can't do the calculation without the operator");
    }

    destroyHoliday(&data);

    return 0;
*/
}