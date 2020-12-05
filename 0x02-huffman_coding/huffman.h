#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stddef.h>

#include "heap/heap.h"
#include "huffman/_huffman.h"

/**
 * struct symbol_s - store a character and its associated frequency
 *
 * @data: character
 * @freq: associated frequency
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

symbol_t *symbol_create(char data, size_t freq);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
int huffman_extract_and_insert(heap_t *priority_queue);
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);
int huffman_codes(char *data, size_t *freq, size_t size);

#endif /* _HUFFMAN_H_ */
