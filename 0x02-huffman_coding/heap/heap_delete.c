#include <stdlib.h>

#include "heap.h"

/**
 * _heap_delete - delete a heap
 *
 * @root: pointer to the root of the heap to delete
 * @data_free: pointer to a function to free a node's data
 */
static void _heap_delete(binary_tree_node_t *root, void (*data_free)(void *))
{
	if (!root)
		return;
	_heap_delete(root->left, data_free);
	_heap_delete(root->right, data_free);
	if (data_free)
		data_free(root->data);
	free(root);
}

/**
 * heap_delete - delete a heap
 *
 * @heap: pointer to the heap to delete
 * @data_free: pointer to a function to free a node's data
 */
void heap_delete(heap_t *heap, void (*data_free)(void *))
{
	if (!heap)
		return;
	_heap_delete(heap->root, data_free);
	free(heap);
}
