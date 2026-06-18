#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main(int argc, char **argv)
{
    printf("\n\n");
    printf("***************************************************************\n");
    printf("********************** hypercube example **********************\n");
    printf("***************************************************************\n");

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

    printf("\n\n");
    printf("***************************************************************\n");
    printf("************************ heap example *************************\n");
    printf("***************************************************************\n");

    heap regions;

    // basic operations of alloc, resize and free
    regions = heap_alloc(1, 1);
    heap_resize(&regions, 32);
    heap_free(&regions);

    // push some elements onto the heap
    regions = heap_alloc(10, 1);

    // make a region and define its error estimates and value and the region
    // properties using the hypercube range and push it to the heap
    double xmin_R1 = {-1};
    double xmax_R1 = {1};
    hypercube R1 = make_hypercube_range(1, xmin1, xmax1);
    region r1 = make_region(&R1, 1);
    r1.ee[0].val = 1;
    r1.ee[0].err = 0.1;
    r1.errmax = 0.1;
    heap_push(&regions, r1);

    // define the two sub-regions and push them to the heap
    double xmin_R1l[] = {-1};
    double xmax_R1l[] = {0};
    hypercube R1l = make_hypercube_range(1, xmin_R1l, xmax_R1l);
    region r1l = make_region(&R1l, 1);
    r1l.ee[0].val = 2;
    r1l.ee[0].err = 0.2;
    r1l.errmax = 0.2;
    heap_push(&regions, r1l);

    double xmin_R1r[] = {0};
    double xmax_R1r[] = {1};
    hypercube R1r = make_hypercube_range(1, xmin_R1r, xmax_R1r);
    region r1r = make_region(&R1r, 1);
    r1r.ee[0].val = 2;
    r1r.ee[0].err = 0.2;
    r1r.errmax = 0.2;
    heap_push(&regions, r1r);

    // print the heap in a tree format
    print_heap(&regions);
    exit(0);
}
