#include <math.h>
#include <stdlib.h>
#include "region.h"
#include "err_codes.h"

/**
 * @brief Create a region from a given hypercube and vector integrand dimensionality.
 *
 * This function initializes a region structure using the provided hypercube and
 * the dimensionality of the vector integrand. It makes a copy of the hypercube
 * and sets up the region's properties accordingly.
 *
 * @param h Pointer to the hypercube structure to be copied.
 * @param fdim The dimensionality of the vector integrand.
 * @return A region structure initialized with the given hypercube and integrand dimensionality.
 *
 * The region structure contains:
 * - A copy of the provided hypercube.
 * - The dimension along which the region will be split, initialized to 0.
 * - The dimensionality of the vector integrand.
 * - An array of estimated errors for each dimension of the integrand, allocated dynamically.
 * - The maximum error estimate, initialized to a large value (HUGE_VAL).
 *
 * Note: The caller is responsible for freeing the dynamically allocated memory
 * for the estimated errors array (R.ee) when it is no longer needed.
*/
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

/**
 * @brief Destroys a region and frees associated resources.
 *
 * This function deallocates the memory associated with a given region.
 * It first destroys the hypercube contained within the region, then frees
 * the memory allocated for the error estimates array, and finally sets
 * the pointer to the error estimates array to NULL.
 *
 * @param R Pointer to the region to be destroyed.
 */
void destroy_region(region *R)
{
     destroy_hypercube(&R->h);
     free(R->ee);
     R->ee = 0;
}

/**
 * @brief Cuts a region into two subregions.
 *
 * This function takes a region `R` and splits it into two subregions, `R` and `R2`.
 * The split is performed along the dimension specified by `R->splitDim`.
 * Both R and R2 are modified to reflect the split, and memory is allocated for
 * the error estimates array in R2. It is assumed that R2 is not already initialized
 * and it is only a pointer to a region structure.
 *
 * @param R Pointer to the original region to be split.
 * @param R2 Pointer to the second region that will be created as a result of the split.
 * @return Returns 0 on success, or FAILURE if the operation fails.
 *
 * The function performs the following steps:
 *   - Copies the original region `R` to `R2`.
 *   - Halves the volume and the data of the original region `R` along the split dimension.
 *   - Creates a new hypercube for `R2` using the modified data.
 *   - Adjusts the data of both regions to reflect the split.
 *   - Allocates memory for the `esterr` structure in `R2`.
 *
 * @note If memory allocation for `R2->ee` fails, the function returns FAILURE.
 */
int cut_region(region *R, region *R2)
{
     unsigned split_dim = R->splitDim;
     unsigned dim = R->h.dim;

     *R2 = *R;

     R->h.data[split_dim + dim] *= 0.5;
     R->h.vol *= 0.5;

     R2->h = make_hypercube(dim, R->h.data, R->h.data + dim);
     if (!R2->h.data) return FAILURE;

     R->h.data[split_dim] -= R->h.data[split_dim + dim];
     R2->h.data[split_dim] += R->h.data[split_dim + dim];
     R2->ee = (esterr *) malloc(sizeof(esterr) * R2->fdim);

     return R2->ee == NULL;
}
