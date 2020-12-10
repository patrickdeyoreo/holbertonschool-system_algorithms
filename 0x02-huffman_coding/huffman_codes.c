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
 * _print_symbol - print a symbol and its huffman code to standard output
 *
 * @data: symbol to print
 * @path: path from root node to leaf node as a binary number
 */
static void _print_symbol(void *data, unsigned long int path)
{
	symbol_t *symbol = data;
	char c = symbol ? symbol->data : -1;
	unsigned long int msb = 0;

	if (c == -1)
		return;
	printf("%c: ", c);
	while ((path >> msb) > 1)
		msb += 1;
	while (msb--)
		putchar(((path >> msb) & 1) + '0');
	putchar('\n');
}

/**
 * _huffman_codes_print - traverse huffman tree and print huffman codes
 *
 * @tree: pointer to the root of a huffman tree
 * @path: path from root node to leaf node as a binary number
 */
static void _huffman_codes_print(binary_tree_node_t *tree, unsigned int path)
{
	symbol_t *symbol = NULL;

	if (tree)
	{
		symbol = tree->data;
		if (symbol && symbol->data == -1)
		{
			_huffman_codes_print(tree->left, path << 1);
			_huffman_codes_print(tree->right, path << 1 | 1);
		}
		else if (symbol)
		{
			_print_symbol(symbol, path);
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
	_huffman_codes_print(tree, 1);
	_huffman_tree_delete(tree);
	return (1);
}
