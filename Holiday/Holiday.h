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

#define DEBUG_ERROR_CODE 1

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
} HOLIDAY__collectedOptionalArgument;

/* This struct will store all arguments that are collected from argv after processed, it is for positional type*/
typedef struct{
    char argumentID[DEFAULT_ARRAY_SIZE];
    char *value;
} HOLIDAY__collectedPositionalArgument;

/* This struct is used to store all information that addOptionalArgument function will get */
typedef struct{
    char longArgumentName[DEFAULT_ARRAY_SIZE];
    char shortArgumentName[3];
    int needValue;
    int isRequired;
    char helpMessage[DEFAULT_ARRAY_SIZE];
} HOLIDAY__neededOptionalArgument;

/* This struct is used to store all information that addPositionalArgument function will get */
typedef struct{
    char argumentID[DEFAULT_ARRAY_SIZE];
    char helpMessage[DEFAULT_ARRAY_SIZE];
} HOLIDAY__neededPositionalArgument;

typedef struct{
    int argc;
    char **argv;
    char programName[DEFAULT_ARRAY_SIZE];
    char programAbout[DEFAULT_ARRAY_SIZE];  
    HOLIDAY__neededPositionalArgument necessaryPositionalArguments[DEFAULT_ARRAY_SIZE];
    HOLIDAY__neededOptionalArgument necessaryOptionalArguments[DEFAULT_ARRAY_SIZE];
    HOLIDAY__collectedOptionalArgument allCollectedOptionalArguments[DEFAULT_ARRAY_SIZE];
    HOLIDAY__collectedPositionalArgument allCollectedPositionalArguments[DEFAULT_ARRAY_SIZE];
    int necessaryPositionalArgumentsIndex;
    int necessaryOptionalArgumentsIndex;
    int allCollectedOptionalArgumentsIndex;
    int allCollectedPositionalArgumentsIndex;
} argParserData;



/* Principals functions */
argParserData argParserInit(int argc, char *argv[], char *programName, char *programAbout);
void addOptionalArgument(argParserData *data, char *longArgumentName, char *shortArgumentName, int needValue, char *helpMessage, int isRequired);
void addPositionalArgument(argParserData *data, char *argumentID, char *helpMessage);
void parseArguments(argParserData *data, int possibleErrorCode);
int optionalWasSet(argParserData *data, char *argumentName);
char* getOptionalArgumentValue(argParserData *data, char *argumentName);
char* getPositionalArgumentValue(argParserData *data, char *argumentID);

int HOLIDAY__checkIfArgumentIsNumeric(char *argument);
int HOLIDAY__checkIfUnknowArgumentsWerePassedToProgram(argParserData *data);
int HOLIDAY__checkIfCountOfCollectedPositionalArgumentsIsCorrect(argParserData *data);
int HOLIDAY__checkIfAllRequiredArgumentsWasGiven(argParserData *data);
void HOLIDAY__showHelpMessage(argParserData *data, int exitCode);
int HOLIDAY__checkIfShortArgumentNameWasAlreadyGiven(argParserData *data, char *argumentName);
int HOLIDAY__checkIfLongNameArgumentWasAlreadyGiven(argParserData *data, char *argumentName);
char HOLIDAY__createNewShortArgumentName(argParserData *data);
int HOLIDAY__pickupAllPositionalArguments(argParserData *data);
void HOLIDAY__addPositionalArgumentInArray(argParserData *data, int *allCollectedPositionalArgumentBegin, int i);
int HOLIDAY__pickupAllShortArgumentNames(argParserData *data, int *argvPosition);
int HOLIDAY__checkIfOptionalArgumentIsRequired(argParserData *data, char *argument);
int HOLIDAY__checkIfOptionalArgumentNeedValue(argParserData *data, char *argument);
names HOLIDAY__getOppositeSizeOfArgumentName(argParserData *data, char *argumentName);
int HOLIDAY__pickupAllLongArgumentNames(argParserData *data, int *argvPosition);
HOLIDAY__neededPositionalArgument HOLIDAY__createNecessaryPositionalArgument(char *argumentID, char *helpMessage);
HOLIDAY__neededOptionalArgument HOLIDAY__createNecessaryOptionalArgument(argParserData *data, char *longArgumentName, char *shortArgumentName, int needValue, char *helpMessage, int isRequired);
int HOLIDAY__dashesChecking(char *argument, int isLongArgumentName, int *dashesInBeginOutput);
int HOLIDAY__retrieveArgumentNameSize(char *argument);
void HOLIDAY__checkDashesInStringBeginning(char *buffer);
