#include "hypercube.h"
typedef struct {
     double val, err;
} esterr;

typedef struct {
     hypercube h;
     unsigned splitDim;
     unsigned fdim; /* dimensionality of vector integrand */
     esterr *ee; /* array of length fdim */
     double errmax; /* max ee[k].err */
} region;
