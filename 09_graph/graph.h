#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "list.h"

typedef int Vertex;

struct edge
{
    Vertex x;
    Vertex y;
};

typedef struct edge Edge;

struct graph
{
    int vertex_num;
    List **list;
};

typedef struct graph Graph;

int graph_init(Graph **graph, int vertex_num);
int graph_create(Graph **graph, Edge *edge, int vertex_num, int edge_num);
int graph_topo_sort(Graph *graph, Vertex *vertices);
void graph_clear(Graph **graph);
void graph_print(Graph *graph);

#endif
