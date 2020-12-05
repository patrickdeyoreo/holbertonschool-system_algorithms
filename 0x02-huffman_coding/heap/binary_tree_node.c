#include <stdlib.h>

#include "heap.h"

/**
 * binary_tree_node - create a new binary tree node
 *
 * @parent: pointer to the parent
 * @data: pointer to the data
 *
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer to the instantiaed node.
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *node = malloc(sizeof(*node));

	if (node)
	{
		node->left = NULL;
		node->right = NULL;
		node->parent = parent;
		node->data = data;
	}
	return (node);
}
