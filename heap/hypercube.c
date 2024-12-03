#include <stdlib.h>
#include "hypercube.h"

double compute_vol(const hypercube *h)
{
     unsigned i;
     double vol = 1;
     for (i = 0; i < h->dim; ++i)
       vol *= 2 * h->data[i + h->dim];
     return vol;
}

hypercube make_hypercube(unsigned dim, const double *center, const double *halfwidth)
{
     unsigned i;
     hypercube h;
     h.dim = dim;
     h.data = (double *) malloc(sizeof(double) * dim * 2);
     h.vol = 0;
     if (h.data) {
       for (i = 0; i < dim; ++i) {
            h.data[i] = center[i];
            h.data[i + dim] = halfwidth[i];
       }
       h.vol = compute_vol(&h);
     }
     return h;
}

hypercube make_hypercube_range(unsigned dim, const double *xmin, const double *xmax)
{
     hypercube h = make_hypercube(dim, xmin, xmax);
     unsigned i;
     if (h.data) {
       for (i = 0; i < dim; ++i) {
            h.data[i] = 0.5 * (xmin[i] + xmax[i]);
            h.data[i + dim] = 0.5 * (xmax[i] - xmin[i]);
       }
       h.vol = compute_vol(&h);
     }
     return h;
}

void destroy_hypercube(hypercube *h)
{
     free(h->data);
     h->dim = 0;
}
