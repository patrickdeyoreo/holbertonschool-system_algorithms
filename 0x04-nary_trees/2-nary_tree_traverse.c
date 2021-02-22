#include "nary_trees.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * _nary_tree_traverse - perform a depth-first traversal on an N-ary tree
 *
 * @root: pointer to the root of the tree to traverse
 * @action: action to perform on each node in the tree
 * @depth: depth of the node pointed to by root
 *
 * Return: depth of the deepest node in the tree
 */
static size_t _nary_tree_traverse(
	nary_tree_t const *root,
	void (*action)(nary_tree_t const *node, size_t depth),
	size_t depth)
{
	nary_tree_t const *child = NULL;
	size_t max_depth = depth;
	size_t new_depth = 0;

	if (!root)
		return (0);

	action(root, depth);

	for (child = root->children; child; child = child->next)
	{
		new_depth = _nary_tree_traverse(child, action, depth + 1);
		max_depth = MAX(max_depth, new_depth);
	}
	return (max_depth);
}

/**
 * nary_tree_traverse - perform a depth-first traversal on an N-ary tree
 *
 * @root: pointer to the root of the tree to traverse
 * @action: action to perform on each node in the tree
 *
 * Return: depth of the deepest node in the tree
 */
size_t nary_tree_traverse(
	nary_tree_t const *root,
	void (*action)(nary_tree_t const *node, size_t depth))
{
	return (_nary_tree_traverse(root, action, 0));
}
