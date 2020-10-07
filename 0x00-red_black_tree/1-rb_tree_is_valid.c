#include "rb_trees.h"

#define MAX(m, n) ((m) > (n) ? (m) : (n))
#define MIN(m, n) ((m) < (n) ? (m) : (n))


/**
 * rb_tree_black_height_max - find the maximum number of black nodes in a path
 *
 * @tree: pointer to the root of a tree
 *
 * Return: the maximum number of black nodes in any path from tree to a leaf
 */
static size_t rb_tree_black_height_max(const rb_tree_t *tree)
{
	size_t black_height_max_l = 0;
	size_t black_height_max_r = 0;

	if (!tree)
		return (1);

	black_height_max_l = rb_tree_black_height_max(tree->left);
	black_height_max_r = rb_tree_black_height_max(tree->right);

	return ((tree->color == BLACK) + MAX(black_height_max_l, black_height_max_r));
}


/**
 * rb_tree_black_height_min - find the minimum number of black nodes in a path
 *
 * @tree: pointer to the root of a tree
 *
 * Return: the minimum number of black nodes in any path from tree to a leaf
 */
static size_t rb_tree_black_height_min(const rb_tree_t *tree)
{
	size_t black_height_min_l = 0;
	size_t black_height_min_r = 0;

	if (!tree)
		return (1);

	black_height_min_l = rb_tree_black_height_min(tree->left);
	black_height_min_r = rb_tree_black_height_min(tree->right);

	return ((tree->color == BLACK) + MIN(black_height_min_l, black_height_min_r));
}


/**
 * rb_tree_red_is_valid - check if tree has any adjacent red nodes
 *
 * @tree: pointer to the root of a tree
 *
 * Return: If tree has no adjacent red nodes, return 1. Otherwise, return 0.
 */
static int rb_tree_red_is_valid(const rb_tree_t *tree)
{
	if (!tree)
		return (1);

	if (tree->color == RED && tree->parent && tree->parent->color == RED)
		return (0);

	return (rb_tree_red_is_valid(tree->left) && rb_tree_red_is_valid(tree->right));
}


/**
 * rb_tree_is_bst - check if tree is a binary search tree
 *
 * @tree: pointer to the root of a tree
 *
 * Return: If tree is a binary search tree, return 1. Otherwise, return 0.
 */
static int rb_tree_is_bst(const rb_tree_t *tree)
{
	if (!tree)
		return (1);

	if (tree->left && tree->left->n >= tree->n)
		return (0);

	if (tree->right && tree->right->n <= tree->n)
		return (0);

	return (rb_tree_is_bst(tree->left) && rb_tree_is_bst(tree->right));
}


/**
 * rb_tree_is_valid - check if a tree is a valid red-black tree
 *
 * @tree: pointer to the root of a tree
 *
 * Return: If tree is NULL or is not a valid red-black tree return 0.
 * Otherwise, return 1.
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	return (tree &&
		tree->color == BLACK &&
		rb_tree_is_bst(tree) &&
		rb_tree_red_is_valid(tree->left) &&
		rb_tree_red_is_valid(tree->right) &&
		rb_tree_black_height_max(tree) == rb_tree_black_height_min(tree));
}
