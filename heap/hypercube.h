/**
 * @file hypercube.h
 * @brief Data structure and functions for handling hypercubes in R^dim.
 *
 * A hypercube is defined by a center and half-widths in each dimension.
 * The volume is cached for efficiency. The center is stored first in data,
 * followed by the half-widths. The volume is the product of the half-widths.
 *
 * For example, for a 1D hypercube (a segment between x=0 and x=1):
 * - .dim = 1
 * - .data = {0.5, 0.5}
 * - .vol = 1
 *
 * The .data contains the centroid and the width of each dimension in the
 * following order:
 * - .data = {center0, center1, ..., centerN, half-width0, half-width1, ..., half-widthN}
 *
 * For example, for .dim = 3:
 * - .data[] = {
 *     center0,       // i = 0
 *     center1,       // i = 1
 *     center2,       // i = 2
 *     half-width0,   // i = 0 + 3 = 0 + dim
 *     half-width1,   // i = 1 + 3 = 1 + dim
 *     half-width2    // i = 2 + 3 = 2 + dim
 *   }
 */

typedef struct {
    unsigned dim; /**< Dimension of the hypercube. */
    double *data; /**< Center and half-widths of the hypercube. */
    double vol; /**< Volume of the hypercube. */
} hypercube;

/**
 * @brief Compute the volume of the hypercube.
 *
 * @param h Pointer to the hypercube structure.
 * @return The volume of the hypercube.
 */
double compute_vol(const hypercube *h);

/**
 * @brief Create a hypercube given its dimension, center, and half-widths.
 *
 * @param dim The dimension of the hypercube.
 * @param center Array of center coordinates.
 * @param halfwidth Array of half-widths for each dimension.
 * @return A hypercube structure.
 */
hypercube make_hypercube(unsigned dim, const double *center, const double *halfwidth);

/**
 * @brief Create a hypercube given its dimension and range [xmin, xmax] in each dimension.
 *
 * @param dim The dimension of the hypercube.
 * @param xmin Array of minimum coordinates for each dimension.
 * @param xmax Array of maximum coordinates for each dimension.
 * @return A hypercube structure.
 */
hypercube make_hypercube_range(unsigned dim, const double *xmin, const double *xmax);

/**
 * @brief Print the details of the hypercube.
 *
 * @param h Pointer to the hypercube structure.
 */
void print_hypercube(const hypercube *h);

/**
 * @brief Destroy the hypercube and free allocated memory.
 *
 * @param h Pointer to the hypercube structure to be destroyed.
 */
void destroy_hypercube(hypercube *h);
