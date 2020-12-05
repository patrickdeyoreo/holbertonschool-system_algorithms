#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../huffman.h"

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
	size_t nread = 0;
	size_t index = 0;

	while ((nread = fread(buffer, sizeof(*buffer), BUFSIZ, istream)))
	{
		if (nread != BUFSIZ && ferror(istream))
			error(EXIT_FAILURE, errno, NULL);
		for (index = 0; index < nread; index += 1)
			(*freq_table())[buffer[index]] += 1;
		if (nread != BUFSIZ && feof(istream))
			break;
	}
	if (!fwrite(freq_table(), sizeof(*freq_table()), 1, ostream))
	{
		if (ferror(ostream))
			error(EXIT_FAILURE, errno, NULL);
		if (feof(ostream))
			error(EXIT_FAILURE, 0, "End of file reached prematurely");
	}
	rewind(istream);
	while ((nread = fread(buffer, sizeof(*buffer), BUFSIZ, istream)))
	{
		if (nread != BUFSIZ && ferror(istream))
			error(EXIT_FAILURE, errno, NULL);
		if (nread != BUFSIZ && feof(istream))
			break;
	}
	return (EXIT_SUCCESS);
}
