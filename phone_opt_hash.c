#include <stdio.h>
#include <string.h>

#include "phonebook_orig.h"

entry *findName(char lastName[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

void append(char lastName[], entry *e[])
{
    /* allocate memory for the new entry and put lastName */
    unsigned int hash_value = BKDRHash(lastName);

    while (e[hash_value]->pNext != NULL)
        e[hash_value] = e[hash_value]->pNext;

    e[hash_value]->pNext = (entry *) malloc(sizeof(entry));
    e[hash_value] = e[hash_value]->pNext;
    strcpy(e[hash_value]->lastName, lastName);
    e[hash_value]->pNext = NULL;

}

unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str) {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}
