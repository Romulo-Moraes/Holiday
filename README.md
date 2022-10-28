<div align="center">
    <h1>Holiday</h1>
    <img width="520px" src="./assets/imagee.png">
    <p>Written by Cipher</p>
</div>


## What's that
Holiday is an argument parser for C programming language, this support optional arguments, positional arguments and some salt in each one. The library is not complex to use and is divided in one header file that need just be included in your code, and some code files that need be passed to your compiler

## Cross-platform
This lib only use C standard libraries in its includes then you can use it on any platform. These are the used C standard libs:
<ul>
    <li>string.h</li>
    <li>stdlib.h</li>
    <li>ctype.h</li>
    <li>stdio.h</li>
</ul>

## Optional arguments
As the name say, optional arguments don't need necessary be pass, and the program can run even without it. But with Holiday you can make them required if necessary. Optional argument don't interfere in any positional argument in CLI command. It's identified by flags that start with '--' or '-'.

## Positional arguments
Positional arguments is always required in program call, without it a crash is given. The order of required positional arguments in the C code is the order that need be pass in CLI program call. Positional argument is identified just by a name, but this name is only visible by the programmer.


## How to use


### Including the Holiday
For better understanding of me and any person that will use this code, all functions are separated by your type, but the header file "Holiday.h" has the prototype of all of them, and somes structs/macros. Simulating that you copied the Holiday folder to current directory of main file of your program, just import the Holiday.h file with the command: 
```c
#include "./Holiday/Holiday.h"
```

### Compilation time
All codes of Holiday lib are in Holiday/code, so to compile it you need to pass the entire code directory to the compiler, like in the following example that simulate as if Holiday folder is in current directory of main file of program, the main.c.

```sh
gcc main.c Holiday/codes/*.c -o main
```


### Using the Holiday
After including it you need to initialize a struct that will store all information about the Holiday, it need mainly of two arguments, argc and argv. the 3° and 4° argParserInit argument is optional, but should be filled at least with empty string "". The 3° give a default name for your program, and the 4° give a about section for your program, both are displayed in help message if the user get stuck.

```c
argParserData data = argParserInit(argc,argv, "calc", "Calculate two numbers given in program call");
```
after initializing the argParserData struct you can start programming the required arguments in your program. You have two ways, the optional argument and the positional argument.

Optional way
```c
// addOptionalArgument(<argParserData>, <long argument name>, <short argument name>, <if need value>, <a help that will be showed if the user get stuck>, <if this optional argument is required>);

addOptionalArgument(&data, "--name", "-n", TRUE, "Pass your name to program", FALSE);
```

### Optional way warnings !!!
addOptionalArgument function has a min/max size for full optional name and short optional name, and the program crash if not followed. The min size of full optional name is 2 characters beyond "--", and the min size of short optional name is 1, that is the same value for the max value. If the program crash, a log will be given to you know what happened.

Positional way
```c
// addPositionalArgument(<argParserData>, <identifier>, <a help that will be showed if the user get stuck>);

addPositionalArgument(&data, "age", "Pass your age to program");
```

### Positional way warnings !!!
Positional arguments need a min value length, anything greater or equal than 2 characters is good.

Parsing
```c
// parseArguments(<argParserData>, <exit error code if something wen't wrong, showing the help message together>);

parseArguments(&data, 0);
```

Checking if an optional argument was triggered
```c
// optionalWasSet(<argParserData>, <flag to check>);

// This return a boolean
optionalWasSet(data, "-n");
```

Getting a value from optional arguments
```c
// getOptionalArgumentValue(<argParserData>, <flag to get>);


// This function return a string or NULL if not found
getOptionalArgumentValue(&data, "--name");
```

Getting a value from positional arguments
```c
// getPositionalArgumentValue(<argParserData>, <ID to get>);

// This function return a string or NULL if not found
getPositionalArgumentValue(&data, "age");
```

Destroying the library's data
```c
// The library do some allocations in heap, then when you don't need the library data anymore you can just free all the allocations calling the DestroyHoliday function
destroyHoliday(&data);
```

This is a functional program with this library, using all functions above
```c
#include <stdio.h>
#include "Holiday/Holiday.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int number1, number2;
    argParserData data = argParserInit(argc, argv, "calc", "Calculate two numbers given in program call");

    addOptionalArgument(&data, "--operation", "-o", TRUE, "Math operator", FALSE);
    addPositionalArgument(&data, "number1", "Pass the first number");
    addPositionalArgument(&data, "number2", "Pass the second number");

    parseArguments(&data, TRUE);

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
```

Inputs / Outputs
```sh
./main 10 20 --operation "*"
200

./main 10 -o "-" 20
-10

./main --operation "+" 10 20
30
```

Note: the character '*' is interpreted different of just a symbol, to terminal it's all files in directory, then it must be passed with quotes.


Error message if just one or no one number is passed
```txt
Calculate two numbers given in program call

Usage: calc [OPTIONS]

Options:
        number1 --> Pass the first number (required)
        number2 --> Pass the second number (required)

        --operation / -o --> Math operator 

End of help message
```

### Negative number as argument value
Holiday can handle negative numbers, for both type of arguments, optional and positional.

Any value that comes after a long/short argument name will become a value if that long argument requires a value, then negative numbers to long argument names isn't a problem. Negative numbers is almost equal to short argument name, except that negative numbers only has numbers beyond the first dash. The short argument name filter will let the argument go away if there only has numbers after the dash, and will be catch up in positional argument filter.

### Names for arguments
Like in variable names, argument names of optional and positional types can't start with a numeric character, if that happens, a warning message will be displayed in terminal and exit will be called.