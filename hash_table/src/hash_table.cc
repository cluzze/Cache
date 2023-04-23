#include "../include/hash_table.h"
#include "../list/include/list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// typedef struct htab_node_t htab_node_t;

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
	int (*hash)(keyT, int);
};

int defolt_hash(keyT key, int size) 
{
	int mod = rand();
	int num = rand();

	return ((key * num) % mod) % size;
} 


htab_t *htab_create(int size) 
{
	assert(size != 0 && "size == 0");
	htab_t *htab = (htab_t *) calloc(1, sizeof(htab_t));
	assert(htab && "null pointer after calloc in htab_create");

	htab->buckets = (htab_node_t **) calloc(size + 1, sizeof(htab_node_t *));
	assert(htab->buckets && "null pointer after calloc in htab_create");

	htab->size = size;
	htab->load_factor = 0;
	htab->list = list_create();
	assert(htab->list && "null pointer after list_create in htab_create");

	return htab;
}

void htab_free(htab_t *htab) 
{
	assert(htab && "null pointer in htab_free");
	free_node(htab);
	free(htab->buckets);
	list_free(htab->list);

	htab->load_factor = 0;
	htab->size = 0;
	htab->hash = NULL;

	free(htab);
}

int htab_size(htab_t *htab) 
{
	assert(htab && "null pointer in htab_size");

	return htab->size;
}

int htab_load_factor(htab_t *htab)
{
	assert(htab && "null pointer in htab_load_factor");

	return htab->load_factor;
}


list_node_t *htab_find_list_node(htab_t *htab, keyT key) 
{
	assert(htab && "null pointer in htab_find_list_node");

	htab_node_t *htab_node = htab_find_hash_node(htab, key);

	if (htab_node == NULL) 
		return NULL;
	
	return htab_node->node;
}

htab_node_t *htab_find_hash_node(htab_t *htab, keyT key) 
{
	assert(htab && "null pointer in htab_find_hash_node");

	int hash = htab->hash(key, htab->size);
	htab_node_t *htab_node = htab->buckets[hash];

	while (htab_node && node_key(htab_node->node) == key) 
	{
		htab_node = htab_node->next;
	}

	return htab_node;
}

void htab_insert(htab_t *htab, keyT key)
{ 
	assert(htab && "null pointer in htab_insert");

	int hash = htab->hash(key, htab->size);

	if (!htab_find_hash_node(htab, key)) 
	{
		return;
	}
	
	htab_node_t *node_htab = (htab_node_t *) calloc(1, sizeof(htab_node_t));
	assert(node_htab && "null pointer after calloc in insert");

	node_htab->next = htab->buckets[hash];
	
	if (htab->buckets[hash])
	{
		htab->buckets[hash]->prev = node_htab;
		htab->load_factor++;
	}

	list_push_front(htab->list, key, 0);
	node_htab->node = list_front(htab->list);

}

void htab_insert_list_node(htab_t *htab, list_node_t *list_node) 
{
	assert(htab && "null pointer in htab_insert");
	keyT key = node_key(list_node);
	htab_insert(htab, key);
}

void htab_erase(htab_t *htab, keyT key) 
{
	assert(htab && "null pointer in htab_erase");

	int hash = 0;
	htab_node_t *node_hash = htab_find_hash_node(htab, key);

	if (!node_hash->next && !node_hash->prev) 
	{
		hash = htab->hash(key, htab->size); 
		htab->buckets[hash] = NULL;
		htab->load_factor--;
	}
	else if (!node_hash->next)
	{
		node_hash->prev->next = NULL;
	}
	else if (!node_hash->prev) 
	{
		hash = htab->hash(key, htab->size); 
		htab->buckets[hash] = node_hash->next;
		node_hash->next->prev = NULL;
	}
	else 
	{
		node_hash->next->prev = node_hash->prev;
		node_hash->prev->next = node_hash->next;
	}
	
	list_erase(htab->list, node_hash->node);
	free(node_hash);
}

void free_node(htab_t *htab)
{
	assert(htab && "null pointer in free_node");
	
	htab_node_t *next = NULL;
	htab_node_t *node = NULL;

	for (int i = 0; i < htab->size; i++)
	{
		node = htab->buckets[i];

		while (node) 
		{
			next = node->next;
			free(node);
			node = next;			
		}
	}
	
}

void htab_rehash(htab_t *htab, int new_size, int (*hash)(keyT))
{
	assert(htab && "null pointer in htab_rehash");
	
	list_node_t *list_node = list_front(htab->list);
	free_node(htab);

	htab->buckets = (htab_node_t **) realloc(htab->buckets, new_size);
	assert(htab->buckets && "null pointer after realloc");
	htab->size = new_size;

	for (int i = 0; i < list_size(htab->list); i++)
	{
		htab_insert_list_node(htab, list_node);
		list_node = list_next(htab->list, list_node);
	}

}


void htab_dump(const htab_t *htab)
{
	int i = 0;
	htab_node_t *htab_node = NULL;

	for (i = 0; i < htab->size; i++)
	{
		htab_node = htab->buckets[i];

		while (htab_node)
		{
			printf("number: %d\n", i);
			printf("key:  %d\n", node_key(htab_node->node));	
			htab_node = htab_node->next;
		}
	}
}

