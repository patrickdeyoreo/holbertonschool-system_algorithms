#include "rb_trees.h"


/**
 * array_to_rb_tree - create a red-black tree from an array
 *
 * @array: pointer to the first element of the array
 * @size: number of elements in the array
 *
 * Return: If creation fails, return NULL.
 * Otherwise, return a pointer to the root of the newly created red-black tree.
 */
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	rb_tree_t *tree = NULL;

	if (array)
	{
		while (size--)
			rb_tree_insert(&tree, *array++);
	}
	return (tree);
}
