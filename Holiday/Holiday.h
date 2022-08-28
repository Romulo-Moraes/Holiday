#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFAULT_ARRAY_SIZE 128

#define ARGUMENT_NOT_REQUIRED 2
#define ARGUMENT_WITHOUT_VALUE 3

#define TRUE 1
#define FALSE 0

#define LOWERCASE_CHARS_BEGIN 97
#define LOWERCASE_CHARS_END 122
#define UPPERCASE_CHARS_BEGIN 65
#define UPPERCASE_CHARS_END 90

typedef struct{  
    char longArgumentName[DEFAULT_ARRAY_SIZE];
    char shortArgumentName[3];
} names;

/* This struct will store all arguments that are collected from argv after processed, it is for optional type*/
typedef struct{
    int needValue;
    char longArgumentName[DEFAULT_ARRAY_SIZE];
    char shortArgumentName[3];
    char *value;
} collectedOptionalArgument;

/* This struct will store all arguments that are collected from argv after processed, it is for positional type*/
typedef struct{
    char argumentID[DEFAULT_ARRAY_SIZE];
    char *value;
} collectedPositionalArgument;

/* This struct is used to store all information that addOptionalArgument function will get */
typedef struct{
    char longArgumentName[DEFAULT_ARRAY_SIZE];
    char shortArgumentName[3];
    int needValue;
    int isRequired;
    char helpMessage[DEFAULT_ARRAY_SIZE];
} neededOptionalArgument;

/* This struct is used to store all information that addPositionalArgument function will get */
typedef struct{
    char argumentID[DEFAULT_ARRAY_SIZE];
    char helpMessage[DEFAULT_ARRAY_SIZE];
} neededPositionalArgument;

typedef struct{
    int argc;
    char **argv;
    char programName[DEFAULT_ARRAY_SIZE];
    char programAbout[DEFAULT_ARRAY_SIZE];  
    neededPositionalArgument necessaryPositionalArguments[DEFAULT_ARRAY_SIZE];
    neededOptionalArgument necessaryOptionalArguments[DEFAULT_ARRAY_SIZE];
    collectedOptionalArgument allCollectedOptionalArguments[DEFAULT_ARRAY_SIZE];
    collectedPositionalArgument allCollectedPositionalArguments[DEFAULT_ARRAY_SIZE];
    int necessaryPositionalArgumentsIndex;
    int necessaryOptionalArgumentsIndex;
    int allCollectedOptionalArgumentsIndex;
    int allCollectedPositionalArgumentsIndex;
} argParserData;



/* Principals functions */
argParserData argParserInit(int argc, char *argv[], char *programName, char *programAbout);
void addOptionalArgument(argParserData *data, char *longArgumentName, char *shortArgumentName, int needValue, char *helpMessage, int isRequired);
void addPositionalArgument(argParserData *data, char *argumentID, char *helpMessage);
void parseArguments(argParserData *data, int enableBreak);
int optionalWasSet(argParserData *data, char *argumentName);
char* getOptionalArgumentValue(argParserData *data, char *argumentName);
char* getPositionalArgumentValue(argParserData *data, char *argumentID);


int checkIfUnknowArgumentsWasPassedToProgram(argParserData *data);
int checkIfCountOfCollectedPositionalArgumentsIsCorrect(argParserData *data);
int checkIfAllRequiredArgumentsWasGiven(argParserData *data);
void showHelpMessage(argParserData *data, int exitCode);
int checkIfShortArgumentNameWasAlreadyGiven(argParserData *data, char *argumentName);
int checkIfLongNameArgumentWasAlreadyGiven(argParserData *data, char *argumentName);
char createNewShortArgumentName(argParserData *data);
int pickupAllPositionalArguments(argParserData *data);
void addPositionalArgumentInArray(argParserData *data, int *allCollectedPositionalArgumentBegin, int i);
int pickupAllShortArgumentNames(argParserData *data, int *argvPosition);
int checkIfOptionalArgumentIsRequired(argParserData *data, char *argument);
int checkIfOptionalArgumentNeedValue(argParserData *data, char *argument);
names getOppositeSizeOfArgumentName(argParserData *data, char *argumentName);
int pickupAllLongArgumentNames(argParserData *data, int *argvPosition);
neededPositionalArgument createNecessaryPositionalArgument(char *argumentID, char *helpMessage);
neededOptionalArgument createNecessaryOptionalArgument(argParserData *data, char *longArgumentName, char *shortArgumentName, int needValue, char *helpMessage, int isRequired);
void controlDashesCountInLongArgumentName(char *argument, int isLongArgumentName);
int retrieveArgumentNameSize(char *argument);
void removeDashesFromPositionalArgument(char *argument, int argumentBufferSize);
