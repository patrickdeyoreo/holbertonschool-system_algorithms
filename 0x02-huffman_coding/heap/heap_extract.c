#include "heap.h"

/**
 * swap - swap data of two nodes
 * @n1: node1
 * @n2: node2
 */
void swap(binary_tree_node_t *n1, binary_tree_node_t *n2)
{
	void *temp;

	temp = n1->data;
	n1->data = n2->data;
	n2->data = temp;
}

/**
 * sift_down - heapifies node
 * @heap: heap
 */
void sift_down(heap_t *heap)
{
	binary_tree_node_t *largest, *node;

	if (!heap || !heap->root || heap->size < 2)
		return;
	node = heap->root;
	while (node->left)
	{
		largest = node->left;
		if (node->right && heap->data_cmp(node->data, node->right->data) >= 0
		    && heap->data_cmp(node->right->data, node->left->data) < 0)
		{
			swap(node->right, node);
			largest = node->right;
		}
		else if (heap->data_cmp(node->left->data, node->data) <= 0)
		{
			swap(node->left, node);
		}
		node = largest;
	}
}

/**
 * heap_extract - extracts root node from heap (min value)
 * @heap: heap
 * Return: data of root node
 */
void *heap_extract(heap_t *heap)
{
	binary_tree_node_t *last_node;
	void *data;

	if (!heap || !heap->root || heap->size <= 0)
		return (NULL);
	data = heap->root->data;
	last_node = get_nth_node(heap->root, heap->size);
	heap->root->data = last_node->data;
	if (last_node->parent)
	{
		if (last_node->parent->left == last_node)
			last_node->parent->left = NULL;
		else
			last_node->parent->right = NULL;
	}
	else
	{
		heap->root = NULL;
	}
	free(last_node);
	heap->size -= 1;
	sift_down(heap);
	return (data);
}
