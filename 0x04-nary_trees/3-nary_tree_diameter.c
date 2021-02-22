#include "nary_trees.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * _nary_tree_diameter - compute the diameter of an N-ary tree
 *
 * @root: pointer to the root of the tree of which to compute the diameter
 * @diameter: address at which to store the diameter
 *
 * Return: height of subtree
 */
size_t _nary_tree_diameter(nary_tree_t const *root, size_t *diameter)
{
	nary_tree_t *child = NULL;
	size_t max_height[2] = {0};
	size_t new_height = 0;

	if (!root)
		return (0);

	for (child = root->children; child; child = child->next)
	{
		new_height = _nary_tree_diameter(child, diameter);
		if (new_height > max_height[1])
		{
			max_height[1] = new_height;
		}
		if (new_height > max_height[0])
		{
			max_height[1] = max_height[0];
			max_height[0] = new_height;
		}
	}
	if (*diameter < max_height[0] + max_height[1] + 1)
		*diameter = max_height[0] + max_height[1] + 1;

	if (max_height[0] > max_height[1])
		return (1 + max_height[0]);
	else
		return (1 + max_height[1]);
}

/**
 * nary_tree_diameter - compute the diameter of an N-ary tree
 *
 * @root: pointer to the root of the tree of which to compute the diameter
 *
 * Return: diameter of the tree pointed to by root
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t diameter = 0;

	if (!root)
		return (0);

	_nary_tree_diameter(root, &diameter);
	return (diameter);
}
