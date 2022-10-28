#include "./../Holiday.h"

void destroyHoliday(argParserData *data){
    HOLIDAY__destroyNeededPositionalArguments(&data->necessaryPositionalArguments);
    HOLIDAY__destroyNeededOptionalArguments(&data->necessaryOptionalArguments);
    HOLIDAY__destroyCollectedPositionalArguments(&data->allCollectedPositionalArguments);
    HOLIDAY__destroyCollectedOptionalArguments(&data->allCollectedOptionalArguments);
}

void HOLIDAY__destroyNeededPositionalArguments(HOLIDAY__neededPositionalArgumentListCell **theArgumentList){
    HOLIDAY__neededPositionalArgumentListCell *q, *p;

    if(*theArgumentList != NULL){
        p = *theArgumentList;
        q = p->next;

        while(q != NULL){
            free(p);
            p = q;
            q = q->next;
        }

        free(p);

        *theArgumentList = NULL;
    }
}

void HOLIDAY__destroyNeededOptionalArguments(HOLIDAY__neededOptionalArgumentListCell **theArgumentList){
    HOLIDAY__neededOptionalArgumentListCell *q, *p;

    if(*theArgumentList != NULL){
        p = *theArgumentList;
        q = p->next;

        while(q != NULL){
            free(p);
            p = q;
            q = q->next;
        }

        free(p);

        *theArgumentList = NULL;
    }
}

void HOLIDAY__destroyCollectedPositionalArguments(HOLIDAY__collectedPositionalArgumentListCell **theArgumentList){
    HOLIDAY__collectedPositionalArgumentListCell *q, *p;

    if(*theArgumentList != NULL){
        p = *theArgumentList;
        q = p->next;

        while(q != NULL){
            free(p);
            p = q;
            q = q->next;
        }

        free(p);

        *theArgumentList = NULL;
    }
}

void HOLIDAY__destroyCollectedOptionalArguments(HOLIDAY__collectedOptionalArgumentListCell **theArgumentList){
    HOLIDAY__collectedOptionalArgumentListCell *q, *p;

    if(*theArgumentList != NULL){
        p = *theArgumentList;
        q = p->next;

        while(q != NULL){
            free(p);
            p = q;
            q = q->next;
        }

        free(p);

        *theArgumentList = NULL;
    }
}