#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "phonebook_opt_hash.h"

entry *findName(char lastName[], entry *e[])
{
    unsigned int hash_value = BKDRHash(lastName);
    entry *tmp = e[hash_value];

    while (tmp) {
        if (strcasecmp(lastName, tmp->lastName) == 0)
            return e[hash_value];
        tmp = tmp->pNext;
    }
    return NULL;
}

void append(char lastName[], entry *e[])
{
    /* allocate memory for the new entry and put lastName */
    unsigned int hash_value = BKDRHash(lastName);
    entry *tmp;

    if (!e[hash_value]) {
        e[hash_value] = (entry *) malloc(sizeof(entry));
        e[hash_value]->pNext = NULL;
        strcpy(e[hash_value]->lastName, lastName);
    } else {
        tmp = (entry *) malloc(sizeof(entry));
        tmp->pNext = e[hash_value];
        e[hash_value] = tmp;
        strcpy(e[hash_value]->lastName, lastName);
    }

}

unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str) {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF) % TABLE_SIZE;
}
