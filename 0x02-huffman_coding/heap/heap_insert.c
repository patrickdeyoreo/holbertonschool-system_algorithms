#include "heap.h"

/**
 * get_nth_node - get the nth node where next node should be inserted
 * @node: heap
 * @n: index of node to be inserted
 * Return: parent if n is +1 than size or nth
 * node which will store the next inserted node
 */
static binary_tree_node_t *get_nth_node(binary_tree_node_t *node, size_t n)
{
	int index = 0, mask;

	for (index = 0; 1 << (index + 1) <= (int)n; ++index)
		;
	for (--index; index >= 0; --index)
	{
		mask = 1 << index;
		if (n & mask)
		{
			if (node->right)
				node = node->right;
			else
				break;
		}
		else
		{
			if (node->left)
				node = node->left;
			else
				break;
		}
	}
	return (node);
}

/**
 * heapify - heapifies node
 * @heap: heap
 * @node: inserted node
 * Return: returns the current node
 */
static binary_tree_node_t *heapify(heap_t *heap, binary_tree_node_t *node)
{
	void *temp;

	if (!node || !node->parent)
		return (node);
	while (node->parent)
	{
		if (heap->data_cmp(node->parent->data, node->data) > 0)
		{
			temp = node->data;
			node->data = node->parent->data;
			node->parent->data = temp;
		}
		node = node->parent;
	}
	return (node);
}

/**
 * heap_insert - insert into min heap
 * @heap: heap data structure
 * @data: data for a new node
 * Return: pointer to the created node containing data, or NULL if it fails
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node, *parent;

	if (!heap)
		return (NULL);
	node = binary_tree_node(NULL, data);
	if (!node)
		return (NULL);
	if (!heap->root)
	{
		heap->root = node;
	}
	else
	{
		parent = get_nth_node(heap->root, heap->size + 1);
		if (!parent->left)
			parent->left = node;
		else
			parent->right = node;
		node->parent = parent;
	}
	heap->size += 1;
	return (heapify(heap, node));
}
