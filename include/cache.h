#pragma once

struct cache_t;

typedef struct cache_t cache_t;

cache_t *cache_create(int size);

int cache_lookup_update(cache_t *cache, keyT key, int keySize);