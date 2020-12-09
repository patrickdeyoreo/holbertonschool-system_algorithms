#include "heap/heap.h"
#include "huffman.h"

/**
 * get_msb - get set MSB bit of @n
 * @n: number
 * Return: number with only MSB set
*/
ulong get_msb(ulong n)
{
	/* while ((n & mask) == 0) */
	/*	mask >>= 1; */
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n |= n >> 32;
	++n;
	return (n >> 1);
}

/**
 * sym_p - print symbol along with it's Huffman code
 * @data: symbol struct
 * @n: path from root node to leaf node represented in binary number
 */
void sym_p(void *data, ulong n)
{
	symbol_t *symbol;
	char c;
	ulong mask;

	symbol = (symbol_t *)data;
	c = symbol->data;
	if (c == -1)
		return;
	printf("%c: ", c);
	mask = get_msb(n);
	for (mask >>= 1; mask; mask >>= 1)
		putchar((n & mask) ? '1' : '0');
	putchar('\n');
}

/**
 * traverse - traverses binary tree, iterative way, no stack used
 * @tree: binary tree
*/
void traverse(binary_tree_node_t *tree)
{
	int left_done = 0;
	ulong path = 1UL;

	if (!tree)
		return;
	while (tree)
	{
		if (!left_done)
			while (tree->left)
			{
				tree = tree->left;
				path = path << 1;
			}
		sym_p(tree->data, path);
		left_done = 1;
		if (tree->right)
		{
			left_done = 0;
			tree = tree->right;
			path = (path << 1) | 1;
		}
		else if (tree->parent)
		{
			while (tree->parent && tree == tree->parent->right)
			{
				tree = tree->parent;
				path = path >> 1;
			}
			if (!tree->parent)
				break;
			tree = tree->parent;
			path = path >> 1;
		}
		else
		{
			break;
		}
	}
}

/**
 * huffman_codes - prints huffman codes for every character
 * @data: array of characters
 * @freq: frequencies of every character
 * @size: size of @data and @freq
 * Return: 1 if it succeed, 0 if it fails
*/
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *tree;

	if (!data || !freq || !size)
		return (0);
	tree = huffman_tree(data, freq, size);
	if (!tree)
		return (0);
	traverse(tree);
	free_tree(tree, free_node);
	return (1);
}
