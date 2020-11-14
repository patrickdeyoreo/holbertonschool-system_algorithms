#include "graphs.h"

/**
 * graph_delete - delete a graph
 *
 * @graph: pointer to the graph to delete
 */
void graph_delete(graph_t *graph)
{
	edge_t *edge = NULL;
	vertex_t *vertex = NULL;

	if (graph)
	{
		while ((vertex = graph->vertices))
		{
			graph->vertices = vertex->next;
			while ((edge = vertex->edges))
			{
				vertex->edges = edge->next;
				free(edge);
			}
			free(vertex->content);
			free(vertex);
		}
		free(graph);
	}
}
