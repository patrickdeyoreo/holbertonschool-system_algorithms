#include "rb_trees.h"


/**
 * rb_tree_node - create a red-black tree node
 * @parent: pointer to the parent node of the node to create
 * @value: value to put in the new node
 * @color: color of the node
 *
 * Return: Upon failure, return NULL. Otherwise, return a pointer to the node.
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *node = malloc(sizeof(*node));

	if (node)
	{
		node->n = value;
		node->color = color;
		node->parent = parent;
		node->left = NULL;
		node->right = NULL;
	}
	return (node);
}
