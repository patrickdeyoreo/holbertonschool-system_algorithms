#include <stdlib.h>

#include "huffman.h"

/**
 * symbol_create - create a new symbol
 *
 * @data: character
 * @freq: frequency
 *
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer to the instantiaed symbol.
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol = malloc(sizeof(*symbol));

	if (symbol)
	{
		symbol->data = data;
		symbol->freq = freq;
	}
	return (symbol);
}
