#include <stdlib.h>

#include "heap/heap.h"
#include "huffman.h"

/**
 * _data_free - free priority queue data
 *
 * @data: pointer to priority queue data
 */
static void _data_free(void *data)
{
	binary_tree_node_t *node = data;

	if (node)
	{
		_data_free(node->left);
		_data_free(node->right);
		free(node->data);
		free(node);
	}
}

/**
 * huffman_tree - build a huffman tree
 *
 * @data: array of characters
 * @freq: array of corresponding frequencies
 * @size: size of the arrays
 *
 * Return: If memory allocation fails, or if data or freq is NULL, return NULL.
 * Otherwise, return a pointer to the root of the resulting huffman tree.
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue = huffman_priority_queue(data, freq, size);
	binary_tree_node_t *tree = NULL;

	if (!priority_queue)
		return (NULL);
	while (priority_queue->size > 1)
	{
		if (!huffman_extract_and_insert(priority_queue))
		{
			heap_delete(priority_queue, _data_free);
			return (NULL);
		}
	}
	tree = priority_queue->root->data;
	heap_delete(priority_queue, NULL);
	return (tree);
}
