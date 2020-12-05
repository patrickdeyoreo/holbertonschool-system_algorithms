#include <stdio.h>

#include "../huffman.h"

/**
 * freq_table - get the global character frequency table
 *
 * Return: pointer to the global character frequency table
 */
freq_table_t *freq_table(void)
{
	static freq_table_t table = {0};

	return (&table);
}

/**
 * freq_table_read - read into the global frequency table
 *
 * @istream: pointer to the input stream
 *
 * Return: Upon success, return 1. Otherwise, return 0.
 */
int freq_table_read(FILE *istream)
{
	freq_table_t *table = freq_table();

	return (fread(table, sizeof(*table), 1, istream));
}

/**
 * freq_table_write - write from the global frequency table
 *
 * @ostream: pointer to the output stream
 *
 * Return: Upon success, return 1. Otherwise, return 0.
 */
int freq_table_write(FILE *ostream)
{
	freq_table_t *table = freq_table();

	return (fwrite(table, sizeof(*table), 1, ostream));
}
