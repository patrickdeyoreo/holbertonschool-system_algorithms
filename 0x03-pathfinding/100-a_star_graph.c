#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphs.h"
#include "pathfinding.h"
#include "queues.h"

#define EUCLIDEAN_DISTANCE(start_x, start_y, end_x, end_y) \
	(sqrt(pow((end_x) - (start_x), 2) + pow((end_y) - (start_y), 2)))

/**
 * _init - allocate and initialize memory
 *
 * @graph: pointer to the graph to search
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 * @vertices: addresss of a pointer to vertex set
 * @previous: addresss of a pointer to vertex parents
 * @distances: addresss of a pointer to vertex distances
 * @euclidean: addresss of a pointer to euclidean distances
 * @queue: address of a pointer to a queue to populate
 *
 * Return: If memory allocation fails, return 0. Otherwise, return 1.
 */
static int _init(
	graph_t *graph, vertex_t const *start, vertex_t const *target,
	vertex_t const ***vertices, vertex_t const ***previous,
	size_t **distances, double **euclidean, queue_t **queue)
{
	vertex_t const *vertex = NULL;

	*queue = queue_create();
	if (!*queue)
		return (0);
	*vertices = calloc(graph->nb_vertices, sizeof(**vertices));
	*previous = calloc(graph->nb_vertices, sizeof(**previous));
	*distances = calloc(graph->nb_vertices, sizeof(**distances));
	*euclidean = calloc(graph->nb_vertices, sizeof(**euclidean));
	if (!*vertices || !*previous || !*distances || !*euclidean)
	{
		queue_delete(*queue);
		free(*vertices);
		free(*previous);
		free(*distances);
		free(*euclidean);
		return (0);
	}
	for (vertex = graph->vertices; vertex; vertex = vertex->next)
	{
		(*vertices)[vertex->index] = vertex;
		(*distances)[vertex->index] = -1;
		(*euclidean)[vertex->index] = EUCLIDEAN_DISTANCE(
			target->x, target->y, vertex->x, vertex->y);
	}
	(*distances)[start->index] = 0;
	return (1);
}

/**
 * _a_star_graph_queue_path - queue the path found from start to target
 *
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 * @previous: pointer to vertex parents
 * @queue: pointer to a queue to populate
 *
 * Return: If memory allocation fails or no path from start to target
 * is found, return 0. Otherwise, return 1.
 */
static int _a_star_graph_queue_path(
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
 * _a_star_graph_extract_min - extact a vertex with the minimum distance
 *
 * @graph: pointer to the graph
 * @vertices: pointer to vertex set
 * @distances: pointer to vertex distances
 * @euclidean: pointer to euclidean distances
 *
 * Return: If vertex set is empty or no distances are defined, return NULL.
 * Otherwise, return a pointer to a vertex with the minimum distance.
 */
static vertex_t const *_a_star_graph_extract_min(
	graph_t *graph, vertex_t const **vertices,
	size_t *distances, double *euclidean)
{
	vertex_t const *vertex = NULL;
	size_t index = 0;
	size_t min = -1;

	while (index < graph->nb_vertices)
	{
		if (vertices[index] &&
			distances[index] + euclidean[index] < min)
		{
			vertex = vertices[index];
			min = distances[index] + euclidean[index];
		}
		index += 1;
	}
	if (vertex)
		vertices[vertex->index] = NULL;
	return (vertex);
}

/**
 * _a_star_graph - search for a path between two vertices in a graph
 *
 * @graph: pointer to the graph in which to search
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 * @vertices: pointer to vertex set
 * @previous: pointer to vertex parents
 * @distances: pointer to vertex distances
 * @euclidean: pointer to euclidean distances
 * @queue: pointer to a queue to populate
 *
 * Return: If memory allocation fails or no path from start to target
 * is found, return 0. Otherwise, return 1.
 */
static int _a_star_graph(
	graph_t *graph, vertex_t const *start, vertex_t const *target,
	vertex_t const **vertices, vertex_t const **previous,
	size_t *distances, double *euclidean, queue_t *queue)
{
	vertex_t const *v = NULL;
	edge_t const *e = NULL;
	size_t d = 0;

	while ((v = _a_star_graph_extract_min(
				graph, vertices, distances, euclidean)))
	{
		printf("Checking %s, distance to %s is %lu\n",
			v->content, target->content,
			(size_t) euclidean[v->index]);
		if (v->index == target->index)
			break;
		euclidean[v->index] = EUCLIDEAN_DISTANCE(
			target->x, target->y, v->x, v->y);
		for (e = v->edges; e; e = e->next)
		{
			if (vertices[e->dest->index])
			{
				d = distances[v->index] + e->weight;
				if (d + euclidean[v->index] <
					distances[e->dest->index] +
					euclidean[e->dest->index])
				{
					previous[e->dest->index] = v;
					distances[e->dest->index] = d;
				}
			}
		}
	}
	return (_a_star_graph_queue_path(
			start, target, previous, queue));
}

/**
 * a_star_graph - search for a path between two vertices in a graph
 *
 * @graph: pointer to the graph to search
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 *
 * Return: If memory allocation fails or no path from start to target
 * is found, return NULL. Otherwise, return a pointer to a queue in
 * which each item is a copy of the content of a vertex in the shortest
 * path from start to target.
 */
queue_t *a_star_graph(
	graph_t *graph, vertex_t const *start, vertex_t const *target)
{
	queue_t *queue = NULL;
	vertex_t const **vertices = NULL;
	vertex_t const **previous = NULL;
	size_t *distances = NULL;
	double *euclidean = NULL;

	if (!graph || !start || !target || !_init(
			graph, start, target, &vertices, &previous,
			&distances, &euclidean, &queue))
		return (NULL);
	if (!_a_star_graph(
			graph, start, target,
			vertices, previous, distances, euclidean, queue))
	{
		queue_delete(queue);
		queue = NULL;
	}
	free(vertices);
	free(previous);
	free(distances);
	free(euclidean);
	return (queue);
}
