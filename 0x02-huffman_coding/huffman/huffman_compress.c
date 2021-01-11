#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * huffman_compress - compress a file
 *
 * @istream: input file stream
 * @ostream: output file strea
 *
 * Return: Upon success, return EXIT_SUCCESS. Otherwise, return EXIT_FAILURE.
 */
int huffman_compress(FILE *istream, FILE *ostream)
{
	unsigned char buffer[BUFSIZ] = {0};
	binary_tree_node_t *tree = NULL;
	size_t n_read = 0;
	size_t index = 0;

	while ((n_read = fread(buffer, sizeof(*buffer), BUFSIZ, istream)))
	{
		if (n_read != BUFSIZ && ferror(istream))
			error(EXIT_FAILURE, errno, NULL);
		for (index = 0; index < n_read; index += 1)
			(*freq_table())[buffer[index]] += 1;
		if (n_read != BUFSIZ && feof(istream))
			break;
	}
	if (!freq_table_write(ostream))
	{
		if (ferror(ostream))
			error(EXIT_FAILURE, errno, NULL);
		if (feof(ostream))
			error(EXIT_FAILURE, 0, "Unexpected end of file");
	}
	tree = huffman_tree(*char_table(), *freq_table(), CHAR_TABLE_SIZE);
	rewind(istream);
	while ((n_read = fread(buffer, sizeof(*buffer), BUFSIZ, istream)))
	{
		if (n_read != BUFSIZ && ferror(istream))
			error(EXIT_FAILURE, errno, NULL);
		if (n_read != BUFSIZ && feof(istream))
			break;
	}
	_huffman_tree_delete(tree);
	return (EXIT_SUCCESS);
}
