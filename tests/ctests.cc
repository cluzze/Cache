#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "hash_table.h"

int hash(keyT key) 
{
    return strlen(key);
}


int main() 
{
    
    htab_t *table = htab_create(5, &hash);
    htab_free(table);

    return 0;

}