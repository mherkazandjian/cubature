#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main(int argc, char **argv)
{
    heap regions;
    region *R = NULL;
    size_t nR_alloc = 0;
    esterr *ee = NULL;

    unsigned int fdim = 1;
    regions = heap_alloc(1, fdim);

    /*
       hypercube example usage
    */
    hypercube h;

    // define a hypercube of dimension 1 with a certain range (xmin,xmax)
    printf("Create a hypercube of dimension 1 with:\n");
    printf("      xrange (-1,1)\n");
    unsigned dim1 = 1;
    double xmin1[] = {-1};
    double xmax1[] = {1};

    // create the hypercube and print its content
    h = make_hypercube_range(dim1, xmin1, xmax1);
    print_hypercube(&h);
    destroy_hypercube(&h);
    printf("--------------------\n");

    // define a hypercube of dimension 2 with a certain range (xmin,xmax)
    // and (ymin,ymax)
    printf("Create a hypercube of dimension 2 with:\n");
    printf("      xmin (-1,-6)\n");
    printf("      xmax (1,-2)\n");
    unsigned dim2 = 2;
    double xmin2[] = {-1, -6};
    double xmax2[] = {1, -2};

    // create the hypercube and print its content
    h = make_hypercube_range(dim2, xmin2, xmax2);
    print_hypercube(&h);
    destroy_hypercube(&h);
    printf("--------------------\n");

    // define a hypercube of dimension 3 with a certain range (min,max)
    printf("Create a hypercube of dimension 3 with xrange (-1,1) and yrange (-6,-2)\n");
    printf("      xmin (-1, -6, 4)\n");
    printf("      xmax (1 , -2, 12)\n");

    unsigned dim3 = 3;
    double xmin3[] = {-1, -6, 4};
    double xmax3[] = {1, -2, 12};

    // create the hypercube and print its content
    h = make_hypercube_range(dim3, xmin3, xmax3);
    print_hypercube(&h);
    destroy_hypercube(&h);
    printf("--------------------\n");

    printf("hello world\n");
    exit(0);
}