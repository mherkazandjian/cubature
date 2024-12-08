
#ifndef REGION_H
#define REGION_H

#include "hypercube.h"
/**
 * @brief Structure to hold a value and its associated error.
 */
typedef struct {
     double val; /**< The value. */
     double err; /**< The associated error. */
} esterr;

/**
 * @struct region
 * @brief Represents a region in a multidimensional space for integration purposes.
 *
 * This structure is used to define a region within a hypercube for numerical integration.
 * It contains information about the hypercube, the dimension along which the region is split,
 * the dimensionality of the vector integrand, and error estimates.
 *
 * @var region::h
 * Hypercube representing the region.
 *
 * @var region::splitDim
 * Dimension along which the region is split.
 *
 * @var region::fdim
 * Dimensionality of the vector integrand.
 *
 * @var region::ee
 * Array of error estimates for each dimension of the integrand.
 *
 * @var region::errmax
 * Maximum error estimate among all dimensions.
 */
typedef struct {
     hypercube h;
     unsigned splitDim;
     unsigned fdim; /* dimensionality of vector integrand */
     esterr *ee; /* array of length fdim */
     double errmax; /* max ee[k].err */
} region;

/**
 * @brief Creates a region from a given hypercube.
 *
 * @param h Pointer to the hypercube.
 * @param fdim The dimension of the function.
 * @return A region object.
 */
region make_region(const hypercube *h, unsigned fdim);

/**
 * @brief Destroys a given region.
 *
 * @param R Pointer to the region to be destroyed.
 */
void destroy_region(region *R);

/**
 * @brief Cuts a region into two regions.
 *
 * @param R Pointer to the original region which will be modified.
 * @param R2 Pointer to the second region which will be created.
 * @return An integer indicating success (0) or failure (non-zero).
 */
int cut_region(region *R, region *R2);

#endif


