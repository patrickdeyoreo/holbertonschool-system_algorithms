#include "heap/heap.h"
#include "huffman.h"

/**
 * huffman_tree - builds a Huffman tree
 * @data: array of character
 * @freq: frequencies of each character of @data
 * @size: size of @freq and @data
 * Return: Huffman tree if success, NULL on failure
*/
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	binary_tree_node_t *tree;

	if (!data || !freq || size == 0)
		return (NULL);
	heap = huffman_priority_queue(data, freq, size);
	if (!heap)
		return (NULL);
	while (heap->size > 1)
	{
		if (!huffman_extract_and_insert(heap))
		{
			/* heap_delete(heap, free_node); */
			/* return (NULL); */
			break;
		}
	}
	tree = heap->root->data;
	free(heap->root);
	free(heap);
	return (tree);
}
