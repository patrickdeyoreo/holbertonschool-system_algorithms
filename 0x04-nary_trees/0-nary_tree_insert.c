#include <stdlib.h>
#include <string.h>

#include "nary_trees.h"

/**
 * nary_tree_insert - insert a node into an N-ary tree
 *
 * @parent: pointer to the parent node
 * @str: string to be stored in the created node
 *
 * Description: The string str will be duplicated and the dynamically allocaed
 * duplicate will be stored in the new node. If parent is not NULL, the created
 * node will be added at the beginning of the parent’s children linked list.
 *
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer * to the created node.
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *node = malloc(sizeof(*node));

	if (!node)
		return (NULL);

	node->content = strdup(str);

	if (!node->content)
	{
		free(node);
		return (NULL);
	}

	node->parent = parent;
	node->nb_children = 0;
	node->children = NULL;

	if (parent)
	{
		node->next = parent->children;
		parent->children = node;
	}
	else
	{
		node->next = NULL;
	}

	return (node);
}
