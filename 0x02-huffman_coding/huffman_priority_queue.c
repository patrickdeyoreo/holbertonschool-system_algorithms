#include <stdlib.h>

#include "heap/heap.h"
#include "huffman.h"

/**
 * _symbol_cmp - compare the respective frequencies of two symbols
 *
 * @a: pointer to a symbol to compare
 * @b: pointer to a symbol to compare
 *
 * Return: difference between the respective frequencies of symbols a and b
 */
static int _symbol_cmp(void *a, void *b)
{
	symbol_t *symbol_a = a;
	symbol_t *symbol_b = b;

	if (!symbol_a && !symbol_b)
		return (0);
	if (!symbol_a)
		return (-1);
	if (!symbol_b)
		return (1);
	return (symbol_a->freq - symbol_b->freq);
}

/**
 * _node_cmp - compare the respective frequencies of two nodes' symbols
 *
 * @a: pointer to a node to compare
 * @b: pointer to a node to compare
 *
 * Return: difference between the respective frequencies of nodes a and b
 */
static int _node_cmp(void *a, void *b)
{
	binary_tree_node_t *node_a = a;
	binary_tree_node_t *node_b = b;

	if (!node_a && !node_b)
		return (0);
	if (!node_a)
		return (-1);
	if (!node_b)
		return (1);
	return (_symbol_cmp(node_a->data, node_b->data));
}

/**
 * _node_free - delete a binary tree node containing a symbol as data
 *
 * @data: pointer to the node to delete
 */
static void _node_free(void *data)
{
	binary_tree_node_t *node = data;

	if (node)
	{
		_node_free(node->left);
		_node_free(node->right);
		free(node->data);
		free(node);
	}
}

/**
 * huffman_priority_queue - create a priority queue for huffman coding
 *
 * @data: array of characters
 * @freq: array of corresponding frequencies
 * @size: size of the arrays
 *
 * Return: If memory allocation fails, or if data or freq is NULL, return NULL.
 * Otherwise, return a pointer to the resulting priority queue.
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue = NULL;
	symbol_t *symbol = NULL;
	binary_tree_node_t *node = NULL;
	size_t index = 0;

	if (!data || !freq || !size)
		return (NULL);
	priority_queue = heap_create(_node_cmp);
	if (!priority_queue)
		return (NULL);
	while (index < size)
	{
		if (freq[index])
		{
			symbol = symbol_create(data[index], freq[index]);
			if (!symbol)
			{
				heap_delete(priority_queue, _node_free);
				return (NULL);
			}
			node = binary_tree_node(NULL, symbol);
			if (!node)
			{
				free(symbol);
				heap_delete(priority_queue, _node_free);
				return (NULL);
			}
			if (!heap_insert(priority_queue, node))
			{
				free(symbol);
				free(node);
				heap_delete(priority_queue, _node_free);
				return (NULL);
			}
		}
		index += 1;
	}
	return (priority_queue);
}
