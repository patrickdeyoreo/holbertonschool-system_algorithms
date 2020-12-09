#include <stdlib.h>

#include "heap.h"

/**
 * sift_down - heapifies node
 * @heap: heap
 */
static void _heap_extract_sift_down(heap_t *heap)
{
	binary_tree_node_t *node = heap->root;
	binary_tree_node_t *swap = node;
	binary_tree_node_t *lchild = NULL;
	binary_tree_node_t *rchild = NULL;
	void *data = node->data;

	while (node)
	{
		lchild = node->left;
		rchild = node->right;
		if (lchild && heap->data_cmp(swap->data, lchild->data) >= 0)
			swap = lchild;
		if (rchild && heap->data_cmp(swap->data, rchild->data) >= 0)
			swap = rchild;
		if (swap == node)
			return;
		node->data = swap->data;
		swap->data = data;
		node = swap;
	}
}


/**
 * _heap_extract - extract the value at the root of a binary heap
 *
 * @heap: pointer to the heap from which to extract data
 */
static void _heap_extract(heap_t *heap)
{
	binary_tree_node_t *parent = heap->root;
	size_t path = heap->size >> 1;
	size_t msb = 0;

	while ((path >> msb) > 1)
		msb += 1;
	while (msb--)
		parent = (path >> msb) & 1 ? parent->right : parent->left;
	if (heap->size & 1)
	{
		heap->root->data = parent->right->data;
		free(parent->right);
		parent->right = NULL;
	}
	else
	{
		heap->root->data = parent->left->data;
		free(parent->left);
		parent->left = NULL;
	}
	_heap_extract_sift_down(heap);
}


/**
 * heap_extract - extract the value at the root of a binary heap
 *
 * @heap: pointer to the heap from which to extract data
 *
 * Return: If heap is NULL or empty, return NULL.
 * Otherwise, returh a pointer the extracted data.
 */
void *heap_extract(heap_t *heap)
{
	void *data = NULL;

	if (!heap || !heap->size)
		return (NULL);
	data = heap->root->data;
	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
	}
	else
	{
		_heap_extract(heap);
		heap->size -= 1;
	}
	return (data);
}
