#include <stdlib.h>

#include "nary_trees.h"

/**
 * nary_tree_delete - delete an entire N-ary tree
 *
 * @tree: pointer to the root of the tree to delete
 */
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *child = NULL;
	nary_tree_t *subtree = NULL;

	if (!tree)
		return;

	child = tree->children;
	while ((subtree = child))
	{
		child = child->next;
		nary_tree_delete(subtree);
	}

	free(tree->content);
	free(tree);
}
