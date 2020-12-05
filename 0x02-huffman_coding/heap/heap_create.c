#include <stdlib.h>

#include "heap.h"

/**
 * heap_create - create a new heap
 *
 * @data_cmp: pointer to a function to compare two nodes' data
 *
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer to the instantiaed heap.
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap = malloc(sizeof(*heap));

	if (heap)
	{
		heap->size = 0;
		heap->root = NULL;
		heap->data_cmp = data_cmp;
	}
	return (heap);
}
