#ifndef _HEAP_H_
#define _HEAP_H_

#include <stddef.h>

/**
 * struct binary_tree_node_s - binary tree node data structure
 *
 * @left: pointer to the left child
 * @right: pointer to the right child
 * @parent: pointer to the parent
 * @data: pointer to the data
 */
typedef struct binary_tree_node_s
{
	struct binary_tree_node_s *left;
	struct binary_tree_node_s *right;
	struct binary_tree_node_s *parent;
	void *data;
} binary_tree_node_t;

/**
 * struct heap_s - binary heap data structure
 *
 * @size: number of nodes in the heap
 * @root: pointer to the heap root
 * @data_cmp: pointer to a function to compare two nodes' data
 */
typedef struct heap_s
{
	size_t size;
	binary_tree_node_t *root;
	int (*data_cmp)(void *, void*);
} heap_t;

binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data);
heap_t *heap_create(int (*data_cmp)(void *, void *));
void heap_delete(heap_t *heap, void (*data_free)(void *));
binary_tree_node_t *heap_insert(heap_t *heap, void *data);
void *heap_extract(heap_t *heap);

#endif /* _HEAP_H_ */
