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


htab_t *htab_create(int size, int (*hash)(keyT, int)) 
{
	assert(size != 0 && "size == 0");
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
	assert(htab && "null pointer in htab_free");
	free(htab->buckets);
	list_free(htab->list);

	htab->load_factor = 0;
	htab->size = 0;
	htab->hash = NULL;

	free(htab);
	// добавить очистку каждого элемента по нодам в бакете тк в функции добавления память будет выделяться
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
//потом добавить функцию поиска для каждого значения
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
	// node_htab = htab_find_hash_node(htab, key);

	if (!htab_find_hash_node(htab, key)) 
	{
		return;
	}
	
	htab_node_t *node_htab = (htab_node_t *) calloc(1, sizeof(htab_node_t));

	node_htab->next = htab->buckets[hash];
	
	if (htab->buckets[hash])
	{
		htab->buckets[hash]->prev = node_htab;
		htab->load_factor++;
	}

	list_push_front(htab->list, key, 0);
	node_htab->node = list_front(htab->list);

}

void htab_erase(htab_t *htab, keyT key) 
{
	int hash = 0;
	// убать хэш в ифы
	htab_node_t *node_hash = htab_find_hash_node(htab, key);

	// случаи
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

void htab_rehash(htab_t *htab, int size, int (*hash)(keyT))
{
	htab_t *new_htab = htab_create(size, hash);

// удалить все ноды в функцию
// реалок массива
// прохожусь по списку и делаю инсерт для каждого значения списка
// инсерт новый нужен или модифицирую функцию 
// impull работа только с htab

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
			// printf("hash: %d\n", htab->hash(htab_node->node->key));
			// номер бакета
			printf("key:  %s\n", node_key(htab_node->node));	
			htab_node = htab_node->next;
		}
	}
}

