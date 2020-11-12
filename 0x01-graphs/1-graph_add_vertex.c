#include <string.h>

#include "graphs.h"


/**
 * graph_add_vertex - add a new vertex to a graph
 *
 * @graph: pointer to the graph to which to add a vertex
 * @str: pointer to a string to copy into the new vertex
 *
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer to the new vertex.
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t **vertex = NULL;
	char *dup = NULL;

	if (!graph || !str)
		return (NULL);

	for (vertex = &graph->vertices; *vertex; vertex = &(*vertex)->next)
	{
		if (!strcmp(str, (*vertex)->content))
			return (NULL);
	}

	dup = strdup(str);
	if (!dup)
		return (NULL);

	*vertex = malloc(sizeof(**vertex));
	if (!*vertex)
		return (NULL);

	(*vertex)->next = NULL;
	(*vertex)->edges = NULL;
	(*vertex)->nb_edges = 0;
	(*vertex)->content = dup;
	(*vertex)->index = graph->nb_vertices++;

	return (*vertex);
}
