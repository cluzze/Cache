#pragma once

struct lru_cache_t;

typedef const char* keyT;
typedef struct lru_cache_t lru_cache_t;
typedef keyT (*slow_get)();

lru_cache_t *lru_create(int size);

void lru_free(lru_cache_t *lru);

int lru_lookup_update(lru_cache_t *lru, keyT key);