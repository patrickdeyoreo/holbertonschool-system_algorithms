#include <stdbool.h>

#include "graphs.h"


/**
 * bft - perform breadth-first traversal over a graph
 *
 * @vertex: pointer to the starting vertex
 * @action: pointer to a function to apply to each vertex
 * @visited: pointer to a table of visited vertex indices
 * @queue: pointer to the front of a vertex queue
 * @depths: pointer to a table of vertex depths
 *
 * Return: Upon failure, return 0. Otherwise, return the greatest vertex depth.
 */
static size_t bft(
	const vertex_t *vertex, void (*action)(const vertex_t *, size_t),
	bool *visited, const vertex_t **queue, size_t *depths)
{
	const vertex_t **queue_rear = queue;
	const edge_t *edge = NULL;
	size_t depth = 0;

	*queue_rear++ = vertex;
	visited[vertex->index] = true;
	depths[vertex->index] = 0;
	while (queue != queue_rear)
	{
		vertex = *queue++;
		depth = depths[vertex->index];
		action(vertex, depth);
		for (edge = vertex->edges; edge; edge = edge->next)
		{
			if (visited[edge->dest->index])
			{
				continue;
			}
			*queue_rear++ = edge->dest;
			visited[edge->dest->index] = true;
			depths[edge->dest->index] = depth + 1;
		}
	}
	return (depth);
}


/**
 * breadth_first_traverse - perform breadth-first traversal over a graph
 *
 * @graph: pointer to the graph to traverse
 * @action: pointer to a function to apply to each vertex
 *
 * Return: Upon failure, return 0. Otherwise, return the greatest vertex depth.
 */
size_t breadth_first_traverse(
	const graph_t *graph, void (*action)(const vertex_t *, size_t))
{
	bool *visited = NULL;
	const vertex_t **queue = NULL;
	size_t *depths = NULL;
	size_t depth = 0;

	if (!graph)
	{
		return (0);
	}
	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (!visited)
	{
		return (0);
	}
	queue = calloc(graph->nb_vertices, sizeof(*queue));
	if (!queue)
	{
		free(visited);
		return (0);
	}
	depths = calloc(graph->nb_vertices, sizeof(*depths));
	if (!depths)
	{
		free(visited);
		free(queue);
		return (0);
	}
	depth = bft(graph->vertices, action, visited, queue, depths);
	free(visited);
	free(queue);
	free(depths);
	return (depth);
}
