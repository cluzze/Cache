#include "../include/hash_table.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct htab_node_t htab_node_t;

struct htab_node_t
{
	htab_node_t *next;
	htab_node_t *prev;
	list_node_t *node;
};

struct htab_t
{
	htab_node_t **buckets;
	list_t *list;
	int size;
	int load_factor; 
	int (*hash)(keyT);
};

int defolt_hash(keyT) 
{
	return 1;
}

htab_t *htab_create(int size, int (*hash)(keyT)) 
{
	htab_t *htab = (htab_t *) calloc(1, sizeof(htab_t));
	htab->buckets = (htab_node_t **) calloc(size + 1, sizeof(htab_node_t *));
	htab->size = size;
	htab->load_factor = 0;
	htab->list = list_create();


	if (hash == NULL) 
	{
		htab->hash = &defolt_hash;
	}
	else 
	{
		htab->hash = hash;
	}

	return htab;
}

void htab_free(htab_t *htab) 
{
	free(htab->buckets);
	list_free(htab->list);

	htab->load_factor = 0;
	htab->size = 0;
	htab->hash = NULL;

	free(htab);
}

int htab_size(htab_t *htab) 
{
	return htab->size;
}

int htab_load_factor(htab_t *htab)
{
	return htab->load_factor;
}


// list_node_t *htab_find(htab_t *htab, keyT key) 
// {
// 	int hash = htab->hash(key);
// 	htab_node_t *node = htab->buckets[hash];
// }


// void htab_erase(htab_t *htab, keyT key) 
// {
// 	int hash = htab->hash(key);
// 	list_node_t *node_key = htab_find(htab, key);

// }