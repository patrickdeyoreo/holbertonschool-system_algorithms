#include <stdio.h>
#include <stdlib.h>

#include "pathfinding.h"
#include "queues.h"

/**
 * queue_push_point - create a point and push it to the front of a queue
 *
 * @queue: pointer to the queue
 * @coordinates: coordinates of the point to create
 *
 * Return: If memory allocation fails, return 0. Otherwise, return 1.
 */
static int queue_push_point(queue_t *queue, point_t const *coordinates)
{
	point_t *point = malloc(sizeof(*point));

	if (!point)
		return (0);
	*point = *coordinates;
	if (!queue_push_front(queue, point))
	{
		free(point);
		return (0);
	}
	return (1);
}

/**
 * map_delete - delete a 2D map
 *
 * @map: pointer to the map to free
 * @rows: number of rows
 */
static void map_delete(char **map, unsigned int rows)
{
	if (map)
	{
		while (rows--)
			free(map[rows]);
		free(map);
	}
}

/**
 * map_create - create a 2D map
 *
 * @rows: number of rows
 * @cols: number of columns
 *
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer to a new zero-initialized 2D map.
 */
static char **map_create(unsigned int rows, unsigned int cols)
{
	char **map = calloc(rows, sizeof(*map));
	unsigned int row = 0;

	if (!map)
		return (NULL);

	while (row < rows)
	{
		map[row] = calloc(cols, sizeof(*map[row]));
		if (!map[row++])
		{
			map_delete(map, row);
			return (NULL);
		}
	}
	return (map);
}

/**
 * _backtracking_array - search for a path between two points in a 2D array
 *
 * @map: 2D map of walkable and unwalkable cells (0s and 1s, respectively)
 * @rows: number of rows of map
 * @cols: number of columns of map
 * @start: coordinates of the starting point
 * @target: coordinates of the target point
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
static int _backtracking_array(
	char **map, int rows, int cols,
	point_t const *start, point_t const *target,
	char **visited, queue_t *queue)
{
	static int const shifts[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	point_t next = *start;
	int x = next.x;
	int y = next.y;
	unsigned int shift_index = 0;

	if (x < 0 || x >= cols || y < 0 || y >= rows ||
		map[y][x] == '1' || visited[y][x])
	{
		return (0);
	}
	visited[y][x] = 1;
	printf("Checking coordinates [%d, %d]\n", x, y);
	if (x == target->x && y == target->y)
		return (queue_push_point(queue, start));
	while (shift_index < 4)
	{
		next.x = x + shifts[shift_index][0];
		next.y = y + shifts[shift_index][1];
		if (_backtracking_array(
				map, rows, cols,
				&next, target, visited, queue))
			return (queue_push_point(queue, start));
		shift_index += 1;
	}
	return (0);
}

/**
 * backtracking_array - search for a path between two points in a 2D array
 *
 * @map: 2D map of walkable and unwalkable cells (0s and 1s, respectively)
 * @rows: number of rows of map
 * @cols: number of columns of map
 * @start: coordinates of the starting point
 * @target: coordinates of the target point
 *
 * Description:
 * For each visited cell, neighbours are explored in the following order:
 *   RIGHT, BOTTOM, LEFT, TOP
 *
 * Return: If memory allocation fails or no path from start to target is
 * found, return NULL. Otherwise, return a pointer to a queue in which each
 * item is a point in a path from start to target.
 */
queue_t *backtracking_array(
	char **map, int rows, int cols,
	point_t const *start, point_t const *target)
{
	queue_t *queue = NULL;
	char **visited = NULL;
	int row = 0;

	if (!map || !start || !target || rows < 1 || cols < 1 ||
		start->x < 0 || start->x >= cols ||
		start->y < 0 || start->y >= rows ||
		target->x < 0 || target->x >= cols ||
		target->y < 0 || target->y >= rows)
	{
		return (NULL);
	}
	while (row < rows)
	{
		if (!map[row++])
			return (NULL);
	}
	queue = queue_create();
	if (!queue)
		return (NULL);
	visited = map_create(rows, cols);
	if (!visited)
	{
		queue_delete(queue);
		return (NULL);
	}
	if (!_backtracking_array(
			map, rows, cols, start, target, visited, queue))
	{
		queue_delete(queue);
		queue = NULL;
	}
	map_delete(visited, rows);
	return (queue);
}
