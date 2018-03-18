#include "utils.h"
#include "graph.h"

#define VERTEX_NUM  11

int generate_graph(Graph **graph);

int main()
{
    int result;
    Graph *graph = NULL;
    Vertex vertex_id;
    Vertex *vertices;
    
    result = generate_graph(&graph);
    if (SUCCESS != result)
    {
        ERR_MSG("ERR[%d]: failed to generate graph!\r\n", result);
        return result;
    }

    graph_print(graph);

    vertices = (Vertex*)malloc(sizeof(Vertex) * graph->vertex_num);
    if (NULL == vertices)
    {
        ERR_MSG("failed to malloc memory for vertices!\r\n");
        return result;
    }

    result = graph_topo_sort(graph, vertices);
    if (SUCCESS != result)
    {
        ERR_MSG("ERR[%d]: failed to topologically sort graph!\r\n", result);
        return result;
    }

    printf("\r\nThe typological order of the vertices are: \r\n");

    for (vertex_id = 0; vertex_id < graph->vertex_num; vertex_id++)
    {
        printf("%d ", vertices[vertex_id]);
    }

    printf("\r\n");

    return 0;
}

int generate_graph(Graph **graph)
{
    Edge edges[] = {{1,2}, {2,3}, {10,1}, {4,1}, {1,5},
                   {5,3}, {6,3}, {3,11}, {10,4}, {4,5},
                   {5,6}, {6,11}, {10,7}, {7,4}, {7,5},
                   {8,5}, {5,9}, {9,6}, {9, 11}, {7,8},
                   {8,9}
                  };
    int result;

    result = graph_create(graph, edges, VERTEX_NUM, sizeof(edges) / sizeof(Edge));
    if (SUCCESS != result)
    {
        ERR_MSG("ERR[%d]: failed to create graph!\r\n", result);
        return result;
    }

    return SUCCESS;
}
