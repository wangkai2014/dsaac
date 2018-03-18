#include "utils.h"
#include "graph.h"

#define VERTEX_NUM 11

int main()
{
    Graph *graph = NULL;
    Edge edges[] = {{1,2}, {2,3}, {10,1}, {4,1}, {1,5},
                   {5,3}, {6,3}, {3,11}, {10,4}, {4,5},
                   {5,6}, {6,11}, {10,7}, {7,4}, {7,5},
                   {8,5}, {5,9}, {9,6}, {9, 11}, {7,8},
                   {8,9}
                  };
    int result;

    result = graph_create(&graph, edges, VERTEX_NUM, sizeof(edges)/sizeof(Edge));
    if (SUCCESS != result)
    {
        ERR_MSG("Err[%d]: failed to create graph!\r\n", result);
        return result;
    }

    graph_print(graph);
    
    graph_clear(&graph);

    return SUCCESS;
}
