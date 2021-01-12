#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphs.h"
#include "pathfinding.h"
#include "queues.h"

/**
 * queue_push_vertex - push a copy of the content of a vertex into a queue
 *
 * @queue: pointer to the queue
 * @vertex: pointer to the vertex
 *
 * Return: If memory allocation fails, return 0. Otherwise, return 1.
 */
static int queue_push_vertex(queue_t *queue, vertex_t const *vertex)
{
	char *content = strdup(vertex->content);

	if (!content)
		return (0);
	if (!queue_push_front(queue, content))
	{
		free(content);
		return (0);
	}
	return (1);
}

/**
 * _backtracking_graph - search for a path between two vertices in a graph
 *
 * @graph: pointer to the graph in which to search
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 * @visited: 2D map of visited cells
 * @queue: pointer to an empty queue
 *
 * Description:
 * For each visited cell, neighbours are explored in the following order:
 *   RIGHT, BOTTOM, LEFT, TOP
 *
 * Return: If memory allocation fails or no path from is found, return 0.
 * Otherwise, return 1.
 */
static int _backtracking_graph(
	graph_t *graph, vertex_t const *start, vertex_t const *target,
	unsigned char *visited, queue_t *queue)
{
	edge_t *edge = start->edges;

	if (visited[start->index])
		return (0);
	visited[start->index] = 1;
	printf("Checking %s\n", start->content);
	if (!strcmp(start->content, target->content))
		return (queue_push_vertex(queue, start));
	while (edge)
	{
		if (_backtracking_graph(
				graph, edge->dest, target, visited, queue))
			return (queue_push_vertex(queue, start));
		edge = edge->next;
	}
	return (0);
}

/**
 * backtracking_graph - search for a path between two vertices in a graph
 *
 * @graph: pointer to the graph in which to search
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 *
 * Return: If memory allocation fails or no path from start to target is found,
 * return NULL. Otherwise, return a pointer to a queue in which each item is a
 * vertex in a path from start to target.
 */
queue_t *backtracking_graph(
	graph_t *graph, vertex_t const *start, vertex_t const *target)
{
	unsigned char *visited = NULL;
	queue_t *queue = NULL;

	if (!graph || !start || !target)
		return (NULL);
	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (!visited)
		return (NULL);
	queue = queue_create();
	if (!queue)
	{
		free(visited);
		return (NULL);
	}
	if (!_backtracking_graph(graph, start, target, visited, queue))
	{
		free(visited);
		queue_delete(queue);
		return (NULL);
	}
	free(visited);
	return (queue);
}
