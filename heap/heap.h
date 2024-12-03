#include <stdlib.h> /* for size_t */
#include "region.h"
#include "err_codes.h"

#ifndef HEAP_H
#define HEAP_H

typedef region heap_item;
#define KEY(hi) ((hi).errmax)

typedef struct {
     size_t n, nalloc;
     heap_item *items;
     unsigned fdim;
     esterr *ee; /* array of length fdim of the total integrand & error */
} heap;

void heap_resize(heap *h, size_t nalloc);
heap heap_alloc(size_t nalloc, unsigned fdim);
void heap_free(heap *h);
int heap_push(heap *h, heap_item hi);
int heap_push_many(heap *h, size_t ni, heap_item *hi);
heap_item heap_pop(heap *h);

#endif
