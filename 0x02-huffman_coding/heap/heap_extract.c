#include <stdlib.h>

#include "heap.h"

/**
 * sift_down - heapifies node
 * @heap: heap
 */
static void _heap_extract_sift_down(heap_t *heap)
{
	binary_tree_node_t *node = heap->root;
	binary_tree_node_t *largest = node;
	void *data = node->data;

	while (node)
	{
		largest = node->left;
		if (node->right && heap->data_cmp(node->data, node->right->data) >= 0
		    && heap->data_cmp(node->right->data, node->left->data) < 0)
		{
			node->data = node->right->data;
			node->right->data = data;
			largest = node->right;
		}
		else if (node->left && heap->data_cmp(node->left->data, node->data) <= 0)
		{
			node->data = node->left->data;
			node->left->data = data;
		}
		node = largest;
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
