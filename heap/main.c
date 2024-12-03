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

    printf("hello world\n");
    exit(0);
}