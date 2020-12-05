#include "../huffman.h"

/**
 * char_table - get the global character table
 *
 * Return: pointer to the global character table
 */
char_table_t *char_table(void)
{
	static char_table_t table = {0};
	static size_t index;

	if (!index)
	{
		while (index < sizeof(table) / sizeof(*table))
		{
			table[index] = index;
			index += 1;
		}
	}
	return (&table);
}
