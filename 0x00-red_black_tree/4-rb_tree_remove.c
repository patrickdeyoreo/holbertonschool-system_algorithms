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
 * rb_tree_in_order_successor - replace a node with its in-order successor
 *
 * @tree: pointer to the node to replace
 *
 * Return: Always 3
 */
static int rb_tree_in_order_successor(rb_tree_t **tree)
{
	rb_tree_t *successor = *tree;

	if (successor)
	{
		successor = successor->right;
		if (successor)
		{
			while (successor->left)
				successor = successor->left;
			successor->left = (*tree)->left;
			if (successor->left)
				successor->left->parent = successor;
			if (successor != (*tree)->right)
				successor->right = (*tree)->right;
			if (successor->right)
				successor->right->parent = successor;
			successor->parent = (*tree)->parent;
		}
	}
	free(*tree);
	(*tree) = successor;

	return (3);
}

/**
 * _rb_tree_remove - remove a value from a red-black tree
 *
 * @tree: double pointer to the root of a tree
 * @value: value to remove
 *
 * Return: -1 if removal fails,
 * 0 if right subtree requires adjustment,
 * 1 if left subtree requires adjustment,
 * 2 if subtree is balanced w/ black root,
 * 3 if subtree is balanced w/ red root
 */
static int _rb_tree_remove(rb_tree_t **tree, int value)
{
	if (*tree)
	{
		if (value == (*tree)->n)
		{
			return (rb_tree_in_order_successor(tree));
		}
		switch (value < (*tree)->n
			? _rb_tree_remove(&(*tree)->left, value)
			: _rb_tree_remove(&(*tree)->right, value))
		{
		case -1:
			return (-1);

		case 0:
			return (value < (*tree)->n
				? (rb_tree_rotate_right_complex(tree))
				: (rb_tree_rotate_left(tree)));

		case 1:
			return (value < (*tree)->n
				? (rb_tree_rotate_right(tree))
				: (rb_tree_rotate_left_complex(tree)));

		case 2:
			return ((*tree)->color == BLACK ? 2 : 3);

		case 3:
			return ((*tree)->color == BLACK ? 2 : value < (*tree)->n);
		}
	}
	return (-1);
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
	_rb_tree_remove(&root, n);

	return (root);
}
