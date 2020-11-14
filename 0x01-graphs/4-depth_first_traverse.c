#include "graphs.h"


/**
 * dft - perform depth-first traversal over a graph
 *
 * @vertex: pointer to the starting vertex
 * @depth: depth of the starting vertex
 * @action: pointer to a function to apply to each vertex
 * @table: pointer to a table of visited vertices
 *
 * Return: Upon failure, return 0. Otherwise, return the greatest vertex depth.
 */
static size_t dft(
	const vertex_t *vertex, size_t depth,
	void (*action)(const vertex_t *, size_t), unsigned char *table)
{
	edge_t *edge = NULL;
	size_t max_depth = 0;
	size_t new_depth = 0;

	if (vertex && !(table[vertex->index / 8] & (1 << (vertex->index % 8))))
	{
		table[vertex->index / 8] |= (1U << (vertex->index % 8));
		action(vertex, depth);
		max_depth = depth;
		for (edge = vertex->edges; edge; edge = edge->next)
		{
			new_depth = dft(edge->dest, depth + 1, action, table);
			if (max_depth < new_depth)
				max_depth = new_depth;
		}
	}
	return (max_depth);
}


/**
 * depth_first_traverse - perform depth-first traversal over a graph
 *
 * @graph: pointer to the graph to traverse
 * @action: pointer to a function to apply to each vertex
 *
 * Return: Upon failure, return 0. Otherwise, return the greatest vertex depth.
 */
size_t depth_first_traverse(
	const graph_t *graph, void (*action)(const vertex_t *, size_t))
{
	unsigned char *table = NULL;
	size_t depth = 0;

	if (graph && graph->vertices)
	{
		table = calloc((graph->nb_vertices - 1) / 8 + 1, 1);
		if (table)
		{
			depth = dft(graph->vertices, depth, action, table);
			free(table);
		}
	}
	return (depth);
}
