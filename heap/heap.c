#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/***************************************************************************/
/* binary heap implementation (ala _Introduction to Algorithms_ by
   Cormen, Leiserson, and Rivest), for use as a priority queue of
   regions to integrate. */

void heap_resize(heap *h, size_t nalloc)
{
     h->nalloc = nalloc;
     if (nalloc)
         h->items = (heap_item *) realloc(h->items, sizeof(heap_item)*nalloc);
     else {
         /* BSD realloc does not free for a zero-sized reallocation */
         free(h->items);
         h->items = NULL;
     }
}

heap heap_alloc(size_t nalloc, unsigned fdim)
{
     heap h;
     unsigned i;
     h.n = 0;
     h.nalloc = 0;
     h.items = 0;
     h.fdim = fdim;
     h.ee = (esterr *) malloc(sizeof(esterr) * fdim);
     if (h.ee) {
       for (i = 0; i < fdim; ++i) h.ee[i].val = h.ee[i].err = 0;
       heap_resize(&h, nalloc);
     }
     return h;
}

/* note that heap_free does not deallocate anything referenced by the items */
void heap_free(heap *h)
{
     h->n = 0;
     heap_resize(h, 0);
     h->fdim = 0;
     free(h->ee);
}

int heap_push(heap *h, heap_item hi)
{
     int insert;
     unsigned i, fdim = h->fdim;

     for (i = 0; i < fdim; ++i) {
       h->ee[i].val += hi.ee[i].val;
       h->ee[i].err += hi.ee[i].err;
     }
     insert = h->n;
     if (++(h->n) > h->nalloc) {
       heap_resize(h, h->n * 2);
       if (!h->items) return FAILURE;
     }

     while (insert) {
       int parent = (insert - 1) / 2;
       if (KEY(hi) <= KEY(h->items[parent]))
            break;
       h->items[insert] = h->items[parent];
       insert = parent;
     }
     h->items[insert] = hi;
     return SUCCESS;
}

int heap_push_many(heap *h, size_t ni, heap_item *hi)
{
     size_t i;
     for (i = 0; i < ni; ++i)
       if (heap_push(h, hi[i])) return FAILURE;
     return SUCCESS;
}

heap_item heap_pop(heap *h)
{
     heap_item ret;
     int i, n, child;

     if (!(h->n)) {
       fprintf(stderr, "attempted to pop an empty heap\n");
       exit(EXIT_FAILURE);
     }

     ret = h->items[0];
     h->items[i = 0] = h->items[n = --(h->n)];
     while ((child = i * 2 + 1) < n) {
       int largest;
       heap_item swap;

       if (KEY(h->items[child]) <= KEY(h->items[i]))
            largest = i;
       else
            largest = child;
       if (++child < n && KEY(h->items[largest]) < KEY(h->items[child]))
            largest = child;
       if (largest == i)
            break;
       swap = h->items[i];
       h->items[i] = h->items[largest];
       h->items[i = largest] = swap;
     }

     {
       unsigned i, fdim = h->fdim;
       for (i = 0; i < fdim; ++i) {
            h->ee[i].val -= ret.ee[i].val;
            h->ee[i].err -= ret.ee[i].err;
       }
     }
     return ret;
}
