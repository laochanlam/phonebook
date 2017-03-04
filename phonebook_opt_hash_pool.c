#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "phonebook_opt_hash_pool.h"

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
        e[hash_value] = memory_pool->next;
        memory_pool->next += sizeof(entry *);
        e[hash_value]->pNext = NULL;
        strcpy(e[hash_value]->lastName, lastName);
    } else {
        tmp = memory_pool->next;
        memory_pool->next += sizeof(entry *);
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

void memory_pool_init()
{
    memory_pool = (pool *) malloc( sizeof(pool) );
    memory_pool->head = (void *) malloc( 350000 * sizeof(entry) );
    memory_pool->tail = memory_pool + 350000 * sizeof(entry) ;
    memory_pool->next = memory_pool->head;
}
