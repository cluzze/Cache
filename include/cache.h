#pragma once

//SLRU cache interface

struct cache_t;

typedef struct cache_t cache_t;

cache_t *cache_create(int size);

void cache_free(cache_t *cache);

int cache_lookup_update(cache_t *cache, int key, int size, int time);

int cache_size(const cache_t *cache);

void cache_dump(const cache_t *cache);