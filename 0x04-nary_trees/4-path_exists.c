#include <string.h>

#include "nary_trees.h"

/**
 * path_exists - check if a path exists in an N-ary tree
 *
 * @root: pointer to the root of the tree
 * @path: NULL-terminated array of strings representing a path
 *
 * Return: If the path exists, return 1. Otherwise, return 0.
 */
int path_exists(nary_tree_t const *root, char const * const *path)
{
	nary_tree_t *child = NULL;

	if (!path[0])
		return (1);
	if (!root)
		return (0);
	if (strcmp(root->content, path[0]))
		return (0);
	for (path += 1; root && path[0]; root = child, path += 1)
	{
		for (child = root->children; child; child = child->next)
		{
			if (!strcmp(child->content, path[0]))
				break;
		}
		if (!child)
			return (0);
	}
	return (!path[0]);
}
