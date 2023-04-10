#include "hash_table.h"

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
};