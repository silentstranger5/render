#include "array.h"

int array_init(array *a, int esize)
{
    a->size = 0;
    a->esize = esize;
    a->capacity = 1 << 10;
    a->data = malloc(a->capacity * a->esize);
    return a->data != NULL;
}

int array_push(array *a, void *e)
{
    if (a->size >= a->capacity)
    {
        a->capacity *= 2;
        void *ptr = a->data;
        a->data = realloc(a->data, a->capacity * a->esize);
        if (!a->data) return 0;
    }
    void *ptr = memcpy((char*) a->data + a->size++ * a->esize, e, a->esize);
    return ptr != NULL;
}

void* array_get(array *a, int idx)
{
    if (idx < 0 || idx > a->size)
        return NULL;
    return (void*) ((char*) a->data + idx * a->esize);
}

void array_free(array *a)
{
    free(a->data);
}
