#include <math.h>
#include <stdlib.h>
#include "region.h"
#include "err_codes.h"


region make_region(const hypercube *h, unsigned fdim)
{
     region R;
     R.h = make_hypercube(h->dim, h->data, h->data + h->dim);
     R.splitDim = 0;
     R.fdim = fdim;
     R.ee = R.h.data ? (esterr *) malloc(sizeof(esterr) * fdim) : NULL;
     R.errmax = HUGE_VAL;
     return R;
}

void destroy_region(region *R)
{
     destroy_hypercube(&R->h);
     free(R->ee);
     R->ee = 0;
}

int cut_region(region *R, region *R2)
{
     unsigned d = R->splitDim, dim = R->h.dim;
     *R2 = *R;
     R->h.data[d + dim] *= 0.5;
     R->h.vol *= 0.5;
     R2->h = make_hypercube(dim, R->h.data, R->h.data + dim);
     if (!R2->h.data) return FAILURE;
     R->h.data[d] -= R->h.data[d + dim];
     R2->h.data[d] += R->h.data[d + dim];
     R2->ee = (esterr *) malloc(sizeof(esterr) * R2->fdim);
     return R2->ee == NULL;
}