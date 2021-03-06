#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphs.h"
#include "pathfinding.h"
#include "queues.h"

/**
 * _dijkstra_graph_queue_path - queue the path found from start to target
 *
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 * @previous: pointer to vertex parents
 * @queue: pointer to a queue to populate
 *
 * Return: If memory allocation fails or no path from start to target
 * is found, return 0. Otherwise, return 1.
 */
static int _dijkstra_graph_queue_path(
	vertex_t const *start, vertex_t const *target,
	vertex_t const **previous, queue_t *queue)
{
	char *data = NULL;

	while (target)
	{
		data = strdup(target->content);
		if (!data)
			return (0);
		if (!queue_push_front(queue, data))
		{
			free(data);
			return (0);
		}
		if (target->index == start->index)
			return (1);
		target = previous[target->index];
	}
	return (0);
}

/**
 * _dijkstra_graph_extract_min - extact a vertex with the minimum distance
 *
 * @graph: pointer to the graph
 * @vertices: pointer to vertex set
 * @distances: pointer to vertex distances
 *
 * Return: If vertex set is empty or no distances are defined, return NULL.
 * Otherwise, return a pointer to a vertex with the minimum distance.
 */
static vertex_t const *_dijkstra_graph_extract_min(
	graph_t *graph, vertex_t const **vertices, size_t *distances)
{
	vertex_t const *vertex = NULL;
	size_t index = 0;
	size_t min = -1;

	while (index < graph->nb_vertices)
	{
		if (vertices[index] && distances[index] < min)
		{
			vertex = vertices[index];
			min = distances[index];
		}
		index += 1;
	}
	if (vertex)
		vertices[vertex->index] = NULL;
	return (vertex);
}

/**
 * _dijkstra_graph - search for a path between two vertices in a graph
 *
 * @graph: pointer to the graph in which to search
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 * @vertices: pointer to vertex set
 * @previous: pointer to vertex parents
 * @distances: pointer to vertex distances
 * @queue: pointer to a queue to populate
 *
 * Return: If memory allocation fails or no path from start to target
 * is found, return 0. Otherwise, return 1.
 */
static int _dijkstra_graph(
	graph_t *graph, vertex_t const *start, vertex_t const *target,
	vertex_t const **vertices, vertex_t const **previous,
	size_t *distances, queue_t *queue)
{
	vertex_t const *v = NULL;
	edge_t const *e = NULL;
	size_t d = 0;

	while ((v = _dijkstra_graph_extract_min(
				graph, vertices, distances)))
	{
		printf("Checking %s, distance from %s is %lu\n",
			v->content, start->content, distances[v->index]);
		if (v->index == target->index)
			break;
		for (e = v->edges; e; e = e->next)
		{
			if (vertices[e->dest->index])
			{
				d = distances[v->index] + e->weight;
				if (d < distances[e->dest->index])
				{
					previous[e->dest->index] = v;
					distances[e->dest->index] = d;
				}
			}
		}
	}
	if (previous[target->index])
		return (_dijkstra_graph_queue_path(
				start, target, previous, queue));
	return (0);
}

/**
 * dijkstra_graph - search for a path between two vertices in a graph
 *
 * @graph: pointer to the graph in which to search
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 *
 * Return: If memory allocation fails or no path from start to target
 * is found, return NULL. Otherwise, return a pointer to a queue in
 * which each item is a copy of the content of a vertex in the shortest
 * path from start to target.
 */
queue_t *dijkstra_graph(
	graph_t *graph, vertex_t const *start, vertex_t const *target)
{
	queue_t *queue = NULL;
	vertex_t const *vertex = NULL;
	vertex_t const **vertices = NULL;
	vertex_t const **previous = NULL;
	size_t *distances = NULL;

	if (!graph || !start || !target)
		return (NULL);
	queue = queue_create();
	if (!queue)
		return (NULL);
	vertices = calloc(graph->nb_vertices, sizeof(*vertices));
	previous = calloc(graph->nb_vertices, sizeof(*previous));
	distances = calloc(graph->nb_vertices, sizeof(*distances));
	if (!vertices || !previous || !distances)
	{
		queue_delete(queue);
		free(vertices);
		free(previous);
		free(distances);
		return (NULL);
	}
	for (vertex = graph->vertices; vertex; vertex = vertex->next)
	{
		vertices[vertex->index] = vertex;
		distances[vertex->index] = -1;
	}
	distances[start->index] = 0;
	if (!_dijkstra_graph(
			graph, start, target,
			vertices, previous, distances, queue))
	{
		queue_delete(queue);
		queue = NULL;
	}
	free(vertices);
	free(previous);
	free(distances);
	return (queue);
}
