#include <stdlib.h>

#include "heap/heap.h"
#include "huffman.h"

/**
 * _node_free - free priority queue data
 *
 * @data: pointer to priority queue data
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
 * huffman_extract_and_insert - extract two nodes and insert their sum
 *
 * @priority_queue: pointer to the priority queue to operate on
 *
 * Return: Upon success. return 1. Otherwise, return 0.
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node_a = NULL;
	binary_tree_node_t *node_b = NULL;
	binary_tree_node_t *node_c = NULL;
	symbol_t *symbol_a = NULL;
	symbol_t *symbol_b = NULL;
	symbol_t *symbol_c = NULL;

	if (!priority_queue || priority_queue->size < 2)
		return (0);
	node_a = heap_extract(priority_queue);
	node_b = heap_extract(priority_queue);
	symbol_a = node_a->data;
	symbol_b = node_b->data;
	symbol_c = symbol_create(-1, symbol_a->freq + symbol_b->freq);
	if (!symbol_c)
	{
		_node_free(node_a);
		_node_free(node_b);
		return (0);
	}
	node_c = binary_tree_node(NULL, symbol_c);
	if (!node_c)
	{
		_node_free(node_a);
		_node_free(node_b);
		free(symbol_c);
		return (0);
	}
	if (!heap_insert(priority_queue, node_c))
	{
		_node_free(node_a);
		_node_free(node_b);
		_node_free(node_c);
		return (0);
	}
	node_c->left = node_a;
	node_c->right = node_b;
	node_a->parent = node_c;
	node_b->parent = node_c;
	return (1);
}
