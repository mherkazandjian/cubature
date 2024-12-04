/**
 * @file region.h
 * @brief Defines the region structure used for numerical integration in a multidimensional space.
 *
 * This file contains the definition of the `region` structure, which represents a region within a hypercube
 * for the purpose of numerical integration. It includes information about the hypercube, the dimension along
 * which the region is split, the dimensionality of the vector integrand, and error estimates.
 */

#ifndef REGION_H
#define REGION_H

#include "hypercube.h"
typedef struct {
     double val, err;
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

#endif
