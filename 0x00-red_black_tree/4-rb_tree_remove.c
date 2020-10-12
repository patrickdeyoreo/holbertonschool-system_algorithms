#include "rb_trees.h"


#define HAS_RED_CHILDREN(node) (	\
	(node)				\
	&& (node)->left			\
	&& (node)->right		\
	&& (node)->left->color == RED	\
	&& (node)->right->color == RED	\
)


#define COLOR_CHILDREN_BLACK(node) (	\
	(node)				\
	? (node)->color = RED		\
	, (node)->left->color = BLACK	\
	, (node)->right->color = BLACK	\
	, 3				\
	: 0				\
)


/**
 * rb_tree_rotate_left - perform a left rotation
 *
 * @tree: double pointer to the root of a tree
 *
 * Return: Always 2
 */
static int rb_tree_rotate_left(rb_tree_t **tree)
{
	(*tree) = (*tree)->right;
	(*tree)->parent->right = (*tree)->left;
	if ((*tree)->left)
		(*tree)->left->parent = (*tree)->parent;
	(*tree)->left = (*tree)->parent;
	(*tree)->parent = (*tree)->left->parent;
	(*tree)->left->parent = (*tree);

	(*tree)->color = BLACK;
	(*tree)->left->color = RED;

	return (2);
}


/**
 * rb_tree_rotate_left_complex - perform a complex left rotation
 *
 * @tree: double pointer to the root of a tree
 *
 * Return: Always 2
 */
static int rb_tree_rotate_left_complex(rb_tree_t **tree)
{
	(*tree) = (*tree)->right->left;
	(*tree)->parent->left = (*tree)->right;
	if ((*tree)->right)
		(*tree)->right->parent = (*tree)->parent;
	(*tree)->right = (*tree)->parent;
	(*tree)->right->parent->right = (*tree)->left;
	if ((*tree)->left)
		(*tree)->left->parent = (*tree)->right->parent;
	(*tree)->left = (*tree)->right->parent;
	(*tree)->right->parent = (*tree);
	(*tree)->parent = (*tree)->left->parent;
	(*tree)->left->parent = (*tree);

	(*tree)->color = BLACK;
	(*tree)->left->color = RED;

	return (2);
}


/**
 * rb_tree_rotate_right - perform a right rotation
 *
 * @tree: double pointer to the root of a tree
 *
 * Return: Always 2
 */
static int rb_tree_rotate_right(rb_tree_t **tree)
{
	(*tree) = (*tree)->left;
	(*tree)->parent->left = (*tree)->right;
	if ((*tree)->right)
		(*tree)->right->parent = (*tree)->parent;
	(*tree)->right = (*tree)->parent;
	(*tree)->parent = (*tree)->right->parent;
	(*tree)->right->parent = (*tree);

	(*tree)->color = BLACK;
	(*tree)->right->color = RED;

	return (2);
}


/**
 * rb_tree_rotate_right_complex - perform a complex right rotation
 *
 * @tree: double pointer to the root of a tree
 *
 * Return: Always 2
 */
static int rb_tree_rotate_right_complex(rb_tree_t **tree)
{
	(*tree) = (*tree)->left->right;
	(*tree)->parent->right = (*tree)->left;
	if ((*tree)->left)
		(*tree)->left->parent = (*tree)->parent;
	(*tree)->left = (*tree)->parent;
	(*tree)->left->parent->left = (*tree)->right;
	if ((*tree)->right)
		(*tree)->right->parent = (*tree)->left->parent;
	(*tree)->right = (*tree)->left->parent;
	(*tree)->left->parent = (*tree);
	(*tree)->parent = (*tree)->right->parent;
	(*tree)->right->parent = (*tree);

	(*tree)->color = BLACK;
	(*tree)->right->color = RED;

	return (2);
}


/**
 * _rb_tree_remove - remove a value from a red-black tree
 *
 * @tree: double pointer to the root of a tree
 * @n: value to remove
 *
 * Return: -1 if removal fails,
 * 0 if right subtree requires adjustment,
 * 1 if left subtree requires adjustment,
 * 2 if subtree is balanced w/ black root,
 * 3 if subtree is balanced w/ red root
 */
static rb_tree_t *_rb_tree_remove(rb_tree_t **tree, int n)
{
	rb_tree_t *temporary = NULL;
	rb_tree_t *successor = NULL;

	if (!tree)
		return (NULL);
	temporary = *tree;
	if (!temporary)
		return (NULL);
	while (*tree && (*tree)->n != n)
		tree = ((*tree)->n >= n) ? &(*tree)->left : &(*tree)->right;
	successor = *tree;
	if (!successor)
		return (temporary);
	if (successor->right)
	{
		successor = successor->right;
		if (successor->left)
		{
			while (successor->left)
				successor = successor->left;
			successor->parent->left = successor->right;
			if (successor->right)
				successor->right->parent = successor->parent;
			(*tree)->n = successor->n;
			if (successor->color == RED)
			{
				free(successor);
				while ((*tree)->parent)
					tree = &(*tree)->parent;
				return (*tree);
			}
			if (successor->right)
			{
				successor->right->color = BLACK;
				free(successor);
				while ((*tree)->parent)
					tree = &(*tree)->parent;
				return (*tree);
			}
			temporary = successor->parent;
			if (temporary == temporary->parent->left)
				tree = &temporary->parent->left;
			else
				tree = &temporary->parent->right;
			if (temporary->right)
			{
				if (temporary->right->right)
					rb_tree_rotate_left(tree);
				else if (temporary->right->left)
					rb_tree_rotate_left_complex(tree);
				else
					temporary->right->color = RED;
			}
			temporary->color = BLACK;
			free(successor);
			while ((*tree)->parent)
				tree = &(*tree)->parent;
			return (*tree);
		}
		(*tree)->right = successor->right;
		if (successor->right)
			successor->right->parent = *tree;
		(*tree)->n = successor->n;
		if (successor->color == RED)
		{
			free(successor);
			while ((*tree)->parent)
				tree = &(*tree)->parent;
			return (*tree);
		}
		if (successor->right)
		{
			successor->right->color = BLACK;
			free(successor);
			while ((*tree)->parent)
				tree = &(*tree)->parent;
			return (*tree);
		}
		temporary = *tree;
		if (temporary->left)
		{
			if (temporary->left->left)
				rb_tree_rotate_right(tree);
			else if (temporary->left->right)
				rb_tree_rotate_right_complex(tree);
			else
				temporary->left->color = RED;
		}
		temporary->color = BLACK;
		free(successor);
		while ((*tree)->parent)
			tree = &(*tree)->parent;
		return (*tree);
	}
	*tree = temporary = successor->left;
	if (temporary)
		temporary->parent = successor->parent;
	else
		temporary = successor->parent;
	if (successor->color == RED)
	{
		free(successor);
		if (temporary)
		{
			while (temporary->parent)
				temporary = temporary->parent;
		}
		return (temporary);
	}
	if (successor->left)
	{
		successor->left->color = BLACK;
		free(successor);
		if (temporary)
		{
			while (temporary->parent)
				temporary = temporary->parent;
		}
		return (temporary);
	}
	if (temporary)
	{
		if (temporary->parent)
		{
			if (temporary == temporary->parent->left)
			{
				tree = &temporary->parent->left;
			}
			else
			{
				tree = &temporary->parent->right;
			}
			if (temporary->left)
			{
				if (temporary->left->left)
					rb_tree_rotate_right(tree);
				else if (temporary->left->right)
					rb_tree_rotate_right_complex(tree);
				else
					temporary->left->color = RED;
			}
		}
		temporary->color = BLACK;
	}
	free(successor);
	if (temporary)
	{
		while (temporary->parent)
			temporary = temporary->parent;
	}
	return (temporary);
}


/**
 * rb_tree_remove - remove a node from a red-black tree
 *
 * @root: pointer to the root of a tree
 * @n: value to remove
 *
 * Return: pointer to the root of the resulting tree
 */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	return _rb_tree_remove(&root, n);
}
