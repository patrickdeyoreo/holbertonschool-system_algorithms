#ifndef _GRAPHS_H_
#define _GRAPHS_H_

#include <stdlib.h>


/**
 * enum edge_type_e - different types of connections between vertices
 *
 * @UNIDIRECTIONAL: the connection is made only in one way
 * @BIDIRECTIONAL: the connection is made in two ways
 */
typedef enum edge_type_e
{
	UNIDIRECTIONAL = 0,
	BIDIRECTIONAL
} edge_type_t;


/**
 * struct edge_s - node in a linked list of edges for a given vertex
 *
 * @dest: pointer to the connected vertex
 * @next: pointer to the next edge
 */
typedef struct edge_s
{
	struct vertex_s	*dest;
	struct edge_s	*next;
} edge_t;


/**
 * struct vertex_s - node in a linked list of vertices in the adjency list
 *
 * @index: index of the vertex in the adjency list.
 * @content: custom data stored in the vertex (here, a string)
 * @nb_edges: number of conenctions with other vertices in the graph
 * @edges: pointer to the head node of the linked list of edges
 * @next: pointer to the next vertex in the adgency linked list
 */
typedef struct vertex_s
{
	size_t		index;
	char		*content;
	size_t		nb_edges;
	struct edge_s	*edges;
	struct vertex_s	*next;
} vertex_t;


/**
 * struct graph_s - representation of a graph using an adjacency linked list
 *
 * @nb_vertices: number of vertices in our graph
 * @vertices: pointer to the head node of our adjency linked list
 */
typedef struct graph_s
{
	size_t		nb_vertices;
	struct vertex_s	*vertices;
} graph_t;


graph_t *graph_create(void);

vertex_t *graph_add_vertex(
	graph_t *graph, const char *str);
int graph_add_edge(
	graph_t *graph, const char *src, const char *dest, edge_type_t type);

void graph_delete(graph_t *graph);

size_t depth_first_traverse(
	const graph_t *graph, void (*action)(const vertex_t *, size_t));
size_t breadth_first_traverse(
	const graph_t *graph, void (*action)(const vertex_t *, size_t));

void graph_display(const graph_t *);


#endif /* _GRAPHS_H_ */
