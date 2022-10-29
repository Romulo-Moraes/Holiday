#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFAULT_ARRAY_SIZE 128
#define HEAP_REQUEST_FINE 1
#define HEAP_REQUEST_FAULT -1
#define HEAP_ALLOCATION_FAULT_MESSAGE "[LOG] Program exited due to fail on heap allocation [LOG]"

#define ARGUMENT_NOT_REQUIRED 2
#define ARGUMENT_WITHOUT_VALUE 3
#define PASSED_MORE_POSITIONAL_ARGUMENT_THAN_NECESSARY 4

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
typedef struct collectedOptionalArgument{
    int needValue;
    char longArgumentName[DEFAULT_ARRAY_SIZE];
    char shortArgumentName[3];
    char *value;
    struct collectedOptionalArgument *next;
} HOLIDAY__collectedOptionalArgumentListCell;

/* This struct will store all arguments that are collected from argv after processed, it is for positional type*/
typedef struct collectedPositionArgument{
    char argumentID[DEFAULT_ARRAY_SIZE];
    char *value;
    struct collectedPositionArgument *next;
} HOLIDAY__collectedPositionalArgumentListCell;

/* This struct is used to store all information that addOptionalArgument function will get */
typedef struct neededOptionalArgument{
    char longArgumentName[DEFAULT_ARRAY_SIZE];
    char shortArgumentName[3];
    int needValue;
    int isRequired;
    char helpMessage[DEFAULT_ARRAY_SIZE];
    struct neededOptionalArgument *next;
} HOLIDAY__neededOptionalArgumentListCell;

/* This struct is used to store all information that addPositionalArgument function will get */
typedef struct neededPositionalArgument{
    char argumentID[DEFAULT_ARRAY_SIZE];
    char helpMessage[DEFAULT_ARRAY_SIZE];
    struct neededPositionalArgument *next;
} HOLIDAY__neededPositionalArgumentListCell;

typedef struct{
    int argc;
    char **argv;
    char programName[DEFAULT_ARRAY_SIZE];
    char programAbout[DEFAULT_ARRAY_SIZE];  
    HOLIDAY__neededPositionalArgumentListCell *necessaryPositionalArguments;
    HOLIDAY__neededOptionalArgumentListCell *necessaryOptionalArguments;
    HOLIDAY__collectedOptionalArgumentListCell *allCollectedOptionalArguments;
    HOLIDAY__collectedPositionalArgumentListCell *allCollectedPositionalArguments;
    int notifyOnMemoryFault;
    int necessaryPositionalArgumentsIndex;
    int necessaryOptionalArgumentsIndex;
    int allCollectedOptionalArgumentsIndex;
    int allCollectedPositionalArgumentsIndex;
} argParserData;



/* Principals functions */
argParserData argParserInit(int argc, char *argv[], char *programName, char *programAbout, int notifyOnMemoryFault);
int addOptionalArgument(argParserData *data, char *longArgumentName, char *shortArgumentName, int needValue, char *helpMessage, int isRequired);
int addPositionalArgument(argParserData *data, char *argumentID, char *helpMessage);
int parseArguments(argParserData *data);
int optionalWasSet(argParserData *data, char *argumentName);
char* getOptionalArgumentValue(argParserData *data, char *argumentName);
char* getPositionalArgumentValue(argParserData *data, char *argumentID);
void destroyHoliday(argParserData *data);

int HOLIDAY__checkIfArgumentIsNumeric(char *argument);
int HOLIDAY__checkIfUnknowArgumentsWerePassedToProgram(argParserData *data);
int HOLIDAY__checkIfCountOfCollectedPositionalArgumentsIsCorrect(argParserData *data);
int HOLIDAY__checkIfAllRequiredArgumentsWereGiven(argParserData *data);
void HOLIDAY__showHelpMessage(argParserData *data);
int HOLIDAY__checkIfShortArgumentNameWasAlreadyGiven(argParserData *data, char *argumentName);
int HOLIDAY__checkIfLongNameArgumentWasAlreadyGiven(argParserData *data, char *argumentName);
char HOLIDAY__createNewShortArgumentName(argParserData *data);
int HOLIDAY__pickupAllPositionalArguments(argParserData *data, int *heapAllocationStatus);
int HOLIDAY__pickupAllShortArgumentNames(argParserData *data, int *argvPosition, int *heapAllocationStatus);
int HOLIDAY__checkIfOptionalArgumentIsRequired(argParserData *data, char *argument);
int HOLIDAY__checkIfOptionalArgumentNeedValue(argParserData *data, char *argument);
names HOLIDAY__getOppositeSizeOfArgumentName(argParserData *data, char *argumentName);
int HOLIDAY__pickupAllLongArgumentNames(argParserData *data, int *argvPosition, int *heapAllocationStatus);
HOLIDAY__neededPositionalArgumentListCell HOLIDAY__createNecessaryPositionalArgument(char *argumentID, char *helpMessage);
HOLIDAY__neededOptionalArgumentListCell HOLIDAY__createNecessaryOptionalArgument(argParserData *data, char *longArgumentName, char *shortArgumentName, int needValue, char *helpMessage, int isRequired);
int HOLIDAY__dashesChecking(char *argument, int isLongArgumentName, int *dashesInBeginOutput);
int HOLIDAY__retrieveArgumentNameSize(char *argument);
void HOLIDAY__checkDashesInStringBeginning(char *buffer);
int HOLIDAY__appendOptionalArgument(argParserData *data, HOLIDAY__neededOptionalArgumentListCell newNecessaryArgument);
int HOLIDAY__appendPositionalArgument(argParserData *data, HOLIDAY__neededPositionalArgumentListCell newNecessaryArgument);
int HOLIDAY__appendCollectedOptionalArgument(argParserData *data, HOLIDAY__collectedOptionalArgumentListCell newArgument);
int HOLIDAY__appendCollectedPositional(argParserData *data, int *allCollectedPositionalArgumentBegin, int i);
void HOLIDAY__destroyNeededPositionalArguments(HOLIDAY__neededPositionalArgumentListCell **theArgumentList);
void HOLIDAY__destroyNeededOptionalArguments(HOLIDAY__neededOptionalArgumentListCell **theArgumentList);
void HOLIDAY__destroyCollectedPositionalArguments(HOLIDAY__collectedPositionalArgumentListCell **theArgumentList);
void HOLIDAY__destroyCollectedOptionalArguments(HOLIDAY__collectedOptionalArgumentListCell **theArgumentList);
HOLIDAY__neededOptionalArgumentListCell *HOLIDAY__searchNeededOptionalValueInList(char fullName[128], char shortName[3], HOLIDAY__neededOptionalArgumentListCell *neededList);
HOLIDAY__neededPositionalArgumentListCell *HOLIDAY__searchNeededPositionalValueInListByIndex(int index, HOLIDAY__neededPositionalArgumentListCell *neededList);
HOLIDAY__collectedOptionalArgumentListCell *HOLIDAY__searchCollectedOptionalValueInList(char *argumentName, HOLIDAY__collectedOptionalArgumentListCell *collectedArgumentList);
HOLIDAY__collectedPositionalArgumentListCell *HOLIDAY__searchCollectedPositionalValueInList(char *argumentName, HOLIDAY__collectedPositionalArgumentListCell *collectedArgumentList);