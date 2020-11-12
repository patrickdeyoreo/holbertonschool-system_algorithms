#include "graphs.h"


/**
 * graph_create - allocate and initialize a new graph
 *
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer to the new graph.
 */
graph_t *graph_create(void)
{
	graph_t *graph = malloc(sizeof(*graph));

	if (graph)
	{
		graph->nb_vertices = 0;
		graph->vertices = NULL;
	}
	return (graph);
}
