#include <stdbool.h>

#include "graphs.h"


/**
 * dft - perform depth-first traversal over a graph
 *
 * @vertex: pointer to the starting vertex
 * @action: pointer to a function to apply to each vertex
 * @visited: pointer to a table of visited vertex indices
 * @depth: depth of the starting vertex
 *
 * Return: Upon failure, return 0.
 * Otherwise, return the greatest vertex depth.
 */
static size_t dft(
	const vertex_t *vertex, void (*action)(const vertex_t *, size_t),
	bool *visited, size_t depth)
{
	const edge_t *edge = NULL;
	size_t max_depth = depth;
	size_t new_depth = 0;

	if (!vertex || visited[vertex->index])
	{
		return (0);
	}
	visited[vertex->index] = true;
	action(vertex, depth);
	for (edge = vertex->edges; edge; edge = edge->next)
	{
		new_depth = dft(edge->dest, action, visited, depth + 1);
		if (max_depth < new_depth)
		{
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
 * Return: Upon failure, return 0.
 * Otherwise, return the greatest vertex depth.
 */
size_t depth_first_traverse(
	const graph_t *graph, void (*action)(const vertex_t *, size_t))
{
	bool *visited = NULL;
	size_t depth = 0;

	if (!graph || !graph->vertices)
	{
		return (0);
	}
	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (!visited)
	{
		return (0);
	}
	depth = dft(graph->vertices, action, visited, 0);
	free(visited);
	return (depth);
}
