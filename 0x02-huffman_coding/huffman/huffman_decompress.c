#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../heap/heap.h"
#include "../huffman.h"

/**
 * huffman_decompress - decompress a file
 *
 * @istream: input file stream
 * @ostream: output file strea
 *
 * Return: Upon success, return EXIT_SUCCESS. Otherwise, return EXIT_FAILURE.
 */
int huffman_decompress(FILE *istream, FILE *ostream __attribute__((unused)))
{
	if (!freq_table_read(istream))
	{
		if (ferror(istream))
			error(EXIT_FAILURE, errno, NULL);
		if (feof(istream))
			error(EXIT_FAILURE, 0, "End of file reached prematurely");
	}
	return (EXIT_SUCCESS);
}
