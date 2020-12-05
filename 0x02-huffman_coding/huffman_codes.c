#include <stdio.h>
#include <stdlib.h>

#include "heap/heap.h"
#include "huffman.h"

/**
 * _huffman_tree_delete - delete a huffman tree
 *
 * @tree: pointer to the root of a huffman tree
 */
static void _huffman_tree_delete(binary_tree_node_t *tree)
{
	if (tree)
	{
		_huffman_tree_delete(tree->left);
		_huffman_tree_delete(tree->right);
		free(tree->data);
		free(tree);
	}
}

/**
 * _print_code - print a huffman code to standard output
 *
 * @code: code to print
 */
static void _print_code(unsigned int code)
{
	if (code >> 1)
		_print_code(code >> 1);
	putchar(code & 1 ? '1' : '0');
}

/**
 * _huffman_codes_print - print huffman codes
 *
 * @tree: pointer to the root of a huffman tree
 * @code: huffman code (initialized to zero)
 */
static void _huffman_codes_print(binary_tree_node_t *tree, unsigned int code)
{
	symbol_t *symbol = NULL;

	if (tree)
	{
		symbol = tree->data;
		if (symbol->data == -1)
		{
			_huffman_codes_print(tree->left, code << 1);
			_huffman_codes_print(tree->right, code << 1 | 1);
		}
		else
		{
			printf("%c: ", symbol->data);
			_print_code(code);
			printf("\n");
		}
	}
}

/**
 * huffman_codes - build a huffman tree and print resulting huffman codes
 *
 * @data: array of characters
 * @freq: array of corresponding frequencies
 * @size: size of the arrays
 *
 * Return: Upon success, return 1. Otherwise, return 0.
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *tree = huffman_tree(data, freq, size);

	if (!tree)
		return (0);
	_huffman_codes_print(tree, 0);
	_huffman_tree_delete(tree);
	return (1);
}
