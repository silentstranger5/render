#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <string.h>

typedef struct
{
    void*   data;
    int     capacity;
    int     size;
    int     esize;
}
array;

int array_init(array *a, int esize);
int array_push(array *a, void *e);
void *array_get(array *a, int idx);
void array_free(array *a);

#endif
