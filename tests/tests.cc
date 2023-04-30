#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "hash_table.h"



int main() 
{
    
    htab_t *table = htab_create(5);
    htab_free(table);

    return 0;

}