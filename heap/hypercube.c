#include <stdlib.h>
#include "hypercube.h"

/**
 * @brief Computes the volume of a hypercube.
 *
 * This function calculates the volume of a given hypercube by multiplying
 * the lengths of its sides. Each side length is determined by the data
 * stored in the hypercube structure.
 *
 * @param h Pointer to the hypercube structure.
 * @return The volume of the hypercube.
 */
double compute_vol(const hypercube *h)
{
     unsigned i;
     double vol = 1;
     for (i = 0; i < h->dim; ++i)
       vol *= 2 * h->data[i + h->dim];
     return vol;
}

/**
 * @brief Creates a hypercube structure with specified dimensions, center, and half-widths.
 *
 * This function allocates memory for the hypercube data, initializes it with the provided
 * center and half-width values, and computes the volume of the hypercube.
 *
 * @param dim The number of dimensions of the hypercube.
 * @param center A pointer to an array of doubles representing the center coordinates of the hypercube.
 * @param halfwidth A pointer to an array of doubles representing the half-widths of the hypercube along each dimension.
 * @return A hypercube structure initialized with the provided parameters. If memory allocation fails, the volume will be 0.
 */
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

/**
 * @brief Creates a hypercube with specified range.
 *
 * This function initializes a hypercube structure with the given dimension,
 * minimum and maximum bounds. It calculates the center and half-length of
 * each dimension and stores them in the hypercube's data array. The volume
 * of the hypercube is also computed and stored.
 *
 * @param dim The dimension of the hypercube.
 * @param xmin Pointer to an array containing the minimum bounds for each dimension.
 * @param xmax Pointer to an array containing the maximum bounds for each dimension.
 * @return A hypercube structure initialized with the specified range.
 */
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

/**
 * @brief Functions for displaying hypercube information
 *
 * This file contains functions for printing the content of a hypercube.
 * The printed content includes:
 *   - the dimension of the hypercube
 *   - the data of the hypercube (in each dimension)
 *       - dim X:
 *           - the center of the hypercube
 *           - the half-widths of the hypercube
 *   - the volume of the hypercube
 *
 * Example usage:
 *
 * For dim = 1:
 *   usage
 *     unsigned dim = 1;
 *     double xmin[] = {-1.0};
 *     double xmax[] = {1.0};
 *     hypercube h = make_hypercube_range(1, xmin, xmax);
 *     print_hypercube(&h);
 *   expected output:
 *     dim = 1
 *       dim 0: center = 0.000000, half-width = 1.000000
 *     vol = 2.000000
 *
 * For dim = 2:
 *   usage
 *     unsigned dim = 2;
 *     double center[] = {0.0, 0.0};
 *     double halfwidth[] = {1.0, 1.0};
 *     hypercube h2 = make_hypercube(2, center, halfwidth);
 *     print_hypercube(&h2);
 *     destroy_hypercube(&h2);
 *   expected output:
 *     dim = 2
 *       dim 0: center = 0.000000, half-width = 1.000000
 *       dim 1: center = 0.000000, half-width = 1.000000
 *     vol = 4.000000
 */
void print_hypercube(const hypercube *h)
{
     unsigned i;
     printf("dim = %u\n", h->dim);
     for (i = 0; i < h->dim; ++i)
       printf("  dim %u: center = %f, half-width = %f\n",
          i, h->data[i], h->data[i + h->dim]);
     printf("vol = %f\n", h->vol);
}

/**
 * @brief Destroys a hypercube object by freeing its allocated data and resetting its dimension.
 *
 * This function releases the memory allocated for the data of the given hypercube
 * and sets its dimension to 0.
 *
 * @param h Pointer to the hypercube object to be destroyed.
 */
void destroy_hypercube(hypercube *h)
{
     free(h->data);
     h->dim = 0;
}
