#include <stdbool.h>

#include "rb_trees.h"


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
 * rb_tree_recolor - color a node red and its children black
 *
 * @tree: double pointer to the root of a tree
 *
 * Return: Always 3
 */
static int rb_tree_recolor(rb_tree_t **tree)
{
	(*tree)->color = RED;
	(*tree)->left->color = BLACK;
	(*tree)->right->color = BLACK;

	return (3);
}

/**
 * _rb_tree_insert - insert a value into a red-black tree
 *
 * @tree: double pointer to the root of a tree
 * @value: value to insert
 * @parent: pointer to the parent of the node pointed to by tree
 * @dest: double pointer to the destination to point to the new node
 *
 * Return: -1 if insertion fails,
 * 0 if right subtree requires adjustment,
 * 1 if left subtree requires adjustment,
 * 2 if subtree is balanced w/ black root,
 * 3 if subtree is balanced w/ red root
 */
int _rb_tree_insert(
	rb_tree_t **tree, rb_tree_t *parent, int value, rb_tree_t **dest)
{
	if (*tree)
	{
		if (value != (*tree)->n)
		{
			switch (value < (*tree)->n
				? _rb_tree_insert(&(*tree)->left, *tree, value, dest)
				: _rb_tree_insert(&(*tree)->right, *tree, value, dest))
			{
			case 0:
				if ((*tree)->left && (*tree)->right
					&& (*tree)->left->color == RED && (*tree)->right->color == RED)
					return (rb_tree_recolor(tree));

				return (value < (*tree)->n
					? rb_tree_rotate_right_complex(tree)
					: rb_tree_rotate_left(tree));

			case 1:
				if ((*tree)->left && (*tree)->right
					&& (*tree)->left->color == RED && (*tree)->right->color == RED)
					return (rb_tree_recolor(tree));

				return (value < (*tree)->n
					? rb_tree_rotate_right(tree)
					: rb_tree_rotate_left_complex(tree));

			case 2:
				return ((*tree)->color == BLACK ? 2 : 3);

			case 3:
				return ((*tree)->color == BLACK ? 2 : value < (*tree)->n);
			}
		}
		return (-1);
	}
	(*tree) = rb_tree_node(parent, value, RED);
	if (dest)
		(*dest) = (*tree);
	return ((*tree) ? 3 : -1);
}


/**
 * rb_tree_insert - insert a value into a red-black tree
 *
 * @tree: double pointer to the root of a tree
 * @value: value to insert
 *
 * Return: If insertion fails, return NULL.
 * Otherwise, return a pointer to the inserted node.
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *node = NULL;

	if (tree && _rb_tree_insert(tree, NULL, value, &node) != -1 && *tree)
		(*tree)->color = BLACK;
	return (node);
}
