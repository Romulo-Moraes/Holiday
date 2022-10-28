#include <stdio.h>
#include "Holiday/Holiday.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int number1, number2;
    argParserData data = argParserInit(argc, argv, "calc", "Calculate two numbers given in program call", FALSE);

    addOptionalArgument(&data, "--operation", "-o", TRUE, "Math operator", TRUE);
    addPositionalArgument(&data, "number1", "Pass the first number");
    addPositionalArgument(&data, "number2", "Pass the second number");
    addOptionalArgument(&data, "--name", "-n", FALSE, "The name", TRUE);

    parseArguments(&data);

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
}