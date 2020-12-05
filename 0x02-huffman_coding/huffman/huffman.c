#include <ctype.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../huffman.h"

#define USAGE_FORMAT "%s <mode> <in_filename> <out_filename>"

/**
 * huffman - compress and decompress text files
 *
 * @mode: 'c' or 'd' ("compress" or "decompress")
 * @ifilename: input filename
 * @ofilename: output filename
 *
 * Return: Upon success, return 0. Otherwise, return a non-zero value.
 */
int huffman(char mode, char *ifilename, char *ofilename)
{
	FILE *istream = NULL;
	FILE *ostream = NULL;
	int ifileno = -1;
	int ofileno = -1;

	ifileno = open(ifilename, O_RDONLY);
	if (ifileno == -1)
		error(EXIT_FAILURE, errno, "%s", ifilename);
	istream = fdopen(ifileno, "r");
	if (!istream)
		error(EXIT_FAILURE, errno, "%s", ifilename);
	ofileno = open(ofilename, O_WRONLY | O_CREAT | O_EXCL, 0666);
	if (ofileno == -1)
		error(EXIT_FAILURE, errno, "%s", ofilename);
	ostream = fdopen(ofileno, "w");
	if (!ostream)
		error(EXIT_FAILURE, errno, "%s", ofilename);
	if (mode == 'c')
		return (huffman_compress(istream, ostream));
	if (mode == 'd')
		return (huffman_decompress(istream, ostream));
	return (EXIT_FAILURE);
}

/**
 * main - entry point
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: Upon success, return 0. Otherwise, return a non-zero value.
 */
int main(int argc, char **argv)
{
	if (argc != 4)
		error(EXIT_FAILURE, 0, "usage: " USAGE_FORMAT,
			program_invocation_short_name);
	if (strlen(argv[1]) != 1)
		error(EXIT_FAILURE, 0, "mode must be either 'c' or 'd'");
	if (tolower(argv[1][0]) != 'c' && tolower(argv[1][0]) != 'd')
		error(EXIT_FAILURE, 0, "mode must be either 'c' or 'd'");
	return (huffman(tolower(argv[1][0]), argv[2], argv[3]));
}
