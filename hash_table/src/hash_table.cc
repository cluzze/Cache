#include "hash_table.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h> 

// htab functions
// working with adding and removing elements
// working with rehash table 
// working with encapsulation htab

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
};

enum RESIZE_MULT
{
	SCALE = 2 
};

int default_hash(keyT key, int size) 
{
	// int mod = rand();
	// int num = rand();
	// printf("%d %d %d\n", key, size, key % size);
	return (key % size);
} 

htab_t *htab_create(int size) 
{
	assert(size != 0 || size < 0 && "size == 0");

	htab_t *htab = (htab_t *) calloc(1, sizeof(htab_t));
	if (htab == NULL) 
	{
		perror("htab null pointer after calloc in htab_create");
		exit(errno);
	}

	htab->buckets = (htab_node_t **) calloc(size + 1, sizeof(htab_node_t *));
	if (htab->buckets == NULL)
	{
		perror("htab->buckets null pointer after calloc in htab_create");
		exit(errno);
	}

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
	list_free(htab->list);

	htab->load_factor = 0;
	htab->size = 0;

	free(htab);
}

int htab_size(const htab_t *htab) 
{
	assert(htab && "null pointer in htab_size");

	return htab->size;
}

int htab_load_factor(const htab_t *htab)
{
	assert(htab && "null pointer in htab_load_factor");

	return htab->load_factor;
}

void htab_insert(htab_t *htab, keyT key, valueT value, int time)
{ 
	assert(htab && "null pointer in htab_insert");

	int hash = default_hash(key, htab->size);

	if (htab_find_hash_node(htab, key)) 
	{
		return;
	}

	list_push_front(htab->list, key, value, time);
	htab_insert_list_node(htab, list_front(htab->list));
}

list_node_t *htab_find_list_node(const htab_t *htab, keyT key) 
{
	assert(htab && "null pointer in htab_find_list_node");

	htab_node_t *htab_node = htab_find_hash_node(htab, key);

	if (htab_node == NULL) 
		return NULL;
	
	return htab_node->node;
}

htab_node_t *htab_find_hash_node(const htab_t *htab, keyT key) 
{
	assert(htab && "null pointer in htab_find_hash_node");

	int hash =  default_hash(key, htab->size);
	htab_node_t *htab_node = htab->buckets[hash];
	
	while (htab_node && !(node_key(htab_node->node) == key))
	{
		htab_node = htab_node->next;
	}

	return htab_node;
}

void htab_insert_list_node(htab_t *htab, list_node_t *list_node) 
{
	assert(htab && "null pointer in htab_insert");

	int hash = default_hash(node_key(list_node), htab->size);

	htab_node_t *node_htab = (htab_node_t *) calloc(1, sizeof(htab_node_t));
	
	if (node_htab == NULL)
	{
		perror("node_htab null pointer after calloc in htab_insert_list_node");
		exit(errno);
	}
	
	if (htab->load_factor/htab->size > 0.75) 
	{
		htab_rehash(htab, htab->size * SCALE);
	}

	node_htab->next = htab->buckets[hash];
	node_htab->node = list_node;
	if (htab->buckets[hash])
	{
		htab->buckets[hash]->prev = node_htab;
	}
	else
	{
	    htab->load_factor++;
	}

	htab->buckets[hash] = node_htab;
}

void htab_erase(htab_t *htab, keyT key) 
{
	assert(htab && "null pointer in htab_erase");

	int hash = 0;
	htab_node_t *node_hash = htab_find_hash_node(htab, key);

	if (!node_hash->next && !node_hash->prev) 
	{
		hash =  default_hash(key, htab->size); 
		htab->buckets[hash] = NULL;
		htab->load_factor--;
	}
	else if (!node_hash->next)
	{
		node_hash->prev->next = NULL;
	}
	else if (!node_hash->prev) 
	{
		hash = default_hash(key, htab->size); 
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
	free(htab->buckets);
}

void htab_rehash(htab_t *htab, int new_size)
{
	assert(htab && "null pointer in htab_rehash");
	
	list_node_t *list_node = NULL;

	free_node(htab);
	htab->buckets = (htab_node_t **) calloc(new_size, sizeof(htab_node_t *));
	
	if (htab->buckets == NULL) 
	{
		perror("htab->buckets null pointer after calloc in htab_rehash");
		exit(errno);
	}
	
	htab->size = new_size;
	htab->load_factor = 0;
	list_node = list_front(htab->list);

	assert(list_node && "null pointer after list_front in htab_rehash");

	for (int i = 0; i < list_size(htab->list); i++)
	{
		htab_insert_list_node(htab, list_node);
		list_node = node_next(list_node);
	}
}

void htab_dump(const htab_t *htab)
{
	assert(htab && "null pointer in htab_dump");

	int i = 0;
	htab_node_t *htab_node = NULL;

    //printf("%d\n", htab_size(htab));
    //printf("%d\n", htab_load_factor(htab));
	list_dump(htab->list);
	for (i = 0; i < htab->size; i++)
	{
		htab_node = htab->buckets[i];
		printf("%d:", i);
		while (htab_node)
		{
			printf("key: %d ", node_key(htab_node->node));	
			htab_node = htab_node->next;
		}
		printf("\n");
	}
}

list_t *htab_list(const htab_t *htab) 
{
	assert(htab && "null pointer in htab_list");
	
	return htab->list;
}

