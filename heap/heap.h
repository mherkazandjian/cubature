#include <stdlib.h> /* for size_t */
#include "region.h"
#include "err_codes.h"

#ifndef HEAP_H
#define HEAP_H

typedef region heap_item;
#define KEY(heap_item) ((heap_item).errmax)

/**
 * @brief A structure representing a heap.
 *
 * This structure is used to manage a heap of items, with additional
 * information about the heap's size, allocated size, and associated
 * error estimates.
 */
typedef struct {
     size_t n;          /**< The current number of items in the heap. */
     size_t nalloc;     /**< The allocated size of the heap (maximum number of items it can hold). */
     heap_item *items;  /**< Pointer to the array of heap items. */
     unsigned fdim;     /**< The dimension of the function being integrated. */
     esterr *ee;        /**< Array of length fdim containing the total integrand and error estimates. */
} heap;

/**
 * @brief Allocates and initializes a new heap.
 *
 * @param nalloc Initial allocation size for the heap.
 * @param fdim Dimension of the function space.
 * @return A new heap structure.
 */
heap heap_alloc(size_t nalloc, unsigned fdim);


/**
 * @brief Resizes the heap to accommodate a new allocation size.
 *
 * @param h Pointer to the heap structure.
 * @param nalloc New allocation size for the heap.
 */
void heap_resize(heap *h, size_t nalloc);


/**
 * @brief Frees the memory allocated for the heap.
 *
 * @param h Pointer to the heap structure to be freed.
 */
void heap_free(heap *h);

/**
 * @brief Pushes a single item onto the heap.
 *
 * @param h Pointer to the heap structure.
 * @param hi The heap item to be pushed onto the heap.
 * @return 0 on success, non-zero on failure.
 */
int heap_push(heap *h, heap_item hi);

/**
 * @brief Pushes multiple items onto the heap.
 *
 * @param h Pointer to the heap structure.
 * @param ni Number of items to be pushed onto the heap.
 * @param hi Array of heap items to be pushed onto the heap.
 * @return 0 on success, non-zero on failure.
 */
int heap_push_many(heap *h, size_t ni, heap_item *hi);

/**
 * @brief Pops the top item from the heap.
 *
 * @param h Pointer to the heap structure.
 * @return The heap item that was popped from the heap.
 */
heap_item heap_pop(heap *h);


/**
 * @brief Prints the elements of the heap.
 *
 * This function takes a pointer to a heap structure and prints its elements.
 *
 * @param h Pointer to the heap structure to be printed.
 */
void print_heap(heap *h);
#endif
