#include <stdlib.h>

#include "heap.h"

/**
 * _heap_insert_sift_up - sift data upward
 *
 * @heap: pointer to the heap in which data was inserted
 * @node: pointer to the inserted node
 *
 * Return: pointer to the node containing the inserted data
 */
static binary_tree_node_t *_heap_insert_sift_up(
	heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *parent = node->parent;
	void *data = node->data;

	while (parent && heap->data_cmp(parent->data, data) > 0)
	{
		node->data = parent->data;
		parent->data = data;
		data = node->data;
		node = parent;
		parent = node->parent;
	}
	return (node);
}

/**
 * _heap_insert - insert a value into a binary heap
 *
 * @heap: pointer to the heap in which to insert data
 * @node: pointer to the node to insert
 *
 * Return: pointer to the node containing the inserted data
 */
static binary_tree_node_t *_heap_insert(
	heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t **child = NULL;
	binary_tree_node_t *parent = heap->root;
	size_t path = ++heap->size >> 1;
	size_t msb = 0;

	while ((path >> msb) > 1)
		msb += 1;
	while (msb--)
		parent = (path >> msb) % 2 ? parent->right : parent->left;
	child = heap->size % 2 ? &parent->right : &parent->left;
	*child = node;
	node->parent = parent;
	return (_heap_insert_sift_up(heap, node));
}

/**
 * heap_insert - insert a value into a binary heap
 *
 * @heap: pointer to the heap in which to insert data
 * @data: pointer to the data to insert
 *
 * Return: If heap is NULL or memory allocation fails, return NULL.
 * Otherwise, returh a pointer to the node containing data.
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node = heap ? binary_tree_node(NULL, data) : NULL;

	if (!node)
		return (NULL);
	if (!heap->size)
	{
		heap->root = node;
		heap->size = 1;
		return (node);
	}
	return (_heap_insert(heap, node));
}
