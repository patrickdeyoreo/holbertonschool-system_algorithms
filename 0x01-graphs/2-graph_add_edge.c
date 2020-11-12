#include <string.h>

#include "graphs.h"


/**
 * graph_find_endpoints- find edge endpoints
 *
 * @vertices: pointer to a linked list of vertices
 * @src: pointer to a string matching the content of the source vertex
 * @dest: pointer to a string matching the content of the destination vertex
 * @v_src: address of a pointer to the source vertex
 * @v_dest: address of a pointer to the destination vertex
 *
 * Return: Upon failure, return 0. Otherwise, return 1.
 */
static int graph_find_endpoints(
	vertex_t *vertices, const char *src, const char *dest,
	vertex_t **v_src, vertex_t **v_dest)
{
	*v_src = NULL;
	*v_dest = NULL;

	while (vertices && !(*v_src && *v_dest))
	{
		if (!strcmp(vertices->content, src))
			*v_src = vertices;
		if (!strcmp(vertices->content, dest))
			*v_dest = vertices;
		vertices = vertices->next;
	}
	return (*v_src && *v_dest);
}

/**
 * graph_add_edge_unidirectional - add a new edge to a graph
 *
 * @v_src: pointer to the source vertex
 * @v_dest: pointer to the destination vertex
 *
 * Return: Upon failure, return 0. Otherwise, return 1.
 */
static int graph_add_edge_unidirectional(vertex_t *v_src, vertex_t *v_dest)
{
	edge_t **e_src = NULL;

	e_src = &v_src->edges;
	while (e_src && *e_src)
		e_src = (*e_src)->dest == v_dest ? NULL : &(*e_src)->next;
	if (e_src)
	{
		*e_src = malloc(sizeof(**e_src));
		if (!*e_src)
			return (0);
		(*e_src)->dest = v_dest;
		(*e_src)->next = NULL;
	}
	return (1);
}

/**
 * graph_add_edge_bidirectional - add a new edge to a graph
 *
 * @v_src: pointer to the source vertex
 * @v_dest: pointer to the destination vertex
 *
 * Return: Upon failure, return 0. Otherwise, return 1.
 */
static int graph_add_edge_bidirectional(vertex_t *v_src, vertex_t *v_dest)
{
	edge_t **e_src = NULL;
	edge_t **e_dest = NULL;

	e_src = &v_src->edges;
	while (e_src && *e_src)
		e_src = (*e_src)->dest == v_dest ? NULL : &(*e_src)->next;
	if (e_src)
	{
		*e_src = malloc(sizeof(**e_src));
		if (!*e_src)
			return (0);
		(*e_src)->dest = v_dest;
		(*e_src)->next = NULL;
	}
	e_dest = &v_dest->edges;
	while (e_dest && *e_dest)
		e_dest = (*e_dest)->dest == v_src ? NULL : &(*e_dest)->next;
	if (e_dest)
	{
		*e_dest = malloc(sizeof(**e_dest));
		if (!*e_dest)
		{
			if (e_src)
			{
				free(*e_src);
				*e_src = NULL;
			}
			return (0);
		}
		(*e_dest)->dest = v_src;
		(*e_dest)->next = NULL;
	}
	return (1);
}

/**
 * graph_add_edge - add a new edge to a graph
 *
 * @graph: pointer to the graph to which to add an edge
 * @src: pointer to a string matching the content of the source vertex
 * @dest: pointer to a string matching the content of the destination vertex
 * @type: edge type (unidirectional or bidirectional)
 *
 * Return: Upon failure, return 0. Otherwise, return 1.
 */
int graph_add_edge(
	graph_t *graph, const char *src, const char *dest, edge_type_t type)
{
	vertex_t *v_src = NULL;
	vertex_t *v_dest = NULL;

	if (graph && src && dest && graph_find_endpoints(
			graph->vertices, src, dest, &v_src, &v_dest))
	{
		switch (type)
		{
		case BIDIRECTIONAL:
			return (graph_add_edge_bidirectional(v_src, v_dest));
		case UNIDIRECTIONAL:
			return (graph_add_edge_unidirectional(v_src, v_dest));
		}
	}
	return (0);
}
