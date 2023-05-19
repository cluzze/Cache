#pragma once

typedef int keyT;

struct pss_cache_t;

typedef struct pss_cache_t pss_cache_t;

pss_cache_t *pss_cache_create(int size);

void pss_cache_free(pss_cache_t *cache);

int pss_cache_space(pss_cache_t *cache);

int pss_cache_lookup_update(pss_cache_t *cache, keyT key, int size, int time);

void pss_cache_dump(pss_cache_t *cache);