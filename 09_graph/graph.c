#include "utils.h"
#include "graph.h"
#include "queue.h"

int graph_init(Graph **in_graph, int vertex_num)
{
    int vertex_id;
    int result;
    Graph *graph;

    if ((in_graph == NULL) || (vertex_num < 1))
    {
        ERR_MSG("Invalid input! vertex_num=%d.\r\n", vertex_num);
        return INVALID_INPUT;
    }

    graph = (Graph *)malloc(sizeof(Graph));
    if (NULL == graph)
    {
        ERR_MSG("failed to malloc memory for graph!\r\n");
        return MALLOC_FAIL;
    }

    graph->vertex_num = vertex_num;

    /* vertex's id begins from 1, so graph->list[0] is not use */
    graph->list = (List **)malloc(sizeof(List *) * (vertex_num + 1));
    if (NULL == graph->list)
    {
        ERR_MSG("failed to malloc memory for graph->list!\r\n");
        free(graph);
        return MALLOC_FAIL;
    }

    for (vertex_id = 1; vertex_id <= vertex_num; vertex_id++)
    {
        result = list_init(graph->list + vertex_id, sizeof(Vertex));
        if (SUCCESS != result)
        {
            ERR_MSG("ERR[%d]: failed to init graph->list[%d]!\r\n", result, vertex_id);
            free(graph->list);
            free(graph);
            return result;
        }
    }

    *in_graph = graph;

    return SUCCESS;
}

int graph_create(Graph **graph, Edge *edge, int vertex_num, int edge_num)
{
    int result;
    int edge_id;

    if ((NULL == graph) || (NULL == edge) || (vertex_num < 1) || (edge_num < 1) )
    {
        ERR_MSG("Invalid input! vertex_num=%d, edge_num=%d.", vertex_num, edge_num);
        return INVALID_INPUT;
    }

    result = graph_init(graph, vertex_num);
    if (SUCCESS != result)
    {
        ERR_MSG("ERR[%d]: failed to init graph!", result);
        return result;
    }

    for (edge_id = 0; edge_id < edge_num; edge_id++)
    {
        result = list_push_back((*graph)->list[edge[edge_id].x], &(edge[edge_id].y), sizeof(Vertex));
        if (SUCCESS != result)
        {
            ERR_MSG("ERR[%d]: failed to add edge[%d] to the graph!\r\n", result, edge_id);
            return result;
        }
    }

    return SUCCESS;
}

int init_degree(Graph *graph, int **indegrees)
{
    int vertex_id;
    int adjc_vertex;
    int *degrees;
    List *cur;

    degrees = (int *)malloc(sizeof(int) * (graph->vertex_num + 1));
    if (NULL == degrees)
    {
        ERR_MSG("failed to malloc memory fro degrees!\r\n");
        return MALLOC_FAIL;
    }

    memset(degrees, 0, sizeof(int) * (graph->vertex_num + 1));

    for (vertex_id = 1; vertex_id <= graph->vertex_num; vertex_id++)
    {
        cur = graph->list[vertex_id]->next;

        while (!list_is_end(graph->list[vertex_id], cur))
        {
            adjc_vertex = *(int *)cur->data;
            degrees[adjc_vertex]++;

            cur = cur->next;
        }
    }

    *indegrees = degrees;

    return SUCCESS;
}

int graph_topo_sort(Graph *graph, Vertex *vertices)
{
    int vertex_id;
    int adjc_vertex;
    int *degrees = NULL;
    int result;
    int sort_num = 0;
    List *node = NULL;
    Queue *queue = NULL;

    if ((NULL == graph) || (NULL == vertices))
    {
        ERR_MSG("null pointer!\r\n");
        return NUL_PTR;
    }

    init_degree(graph, &degrees);

    result = queue_init(&queue, sizeof(Vertex));
    if (SUCCESS != result)
    {
        ERR_MSG("ERR[%d]: failed to init queue!\r\n", result);
        return result;
    }

    for (vertex_id = 1; vertex_id <= graph->vertex_num; vertex_id++)
    {
        if (degrees[vertex_id] == 0)
        {
            result = queue_enqueue(queue, &vertex_id, sizeof(Vertex));
            if (SUCCESS != result)
            {
                ERR_MSG("ERR[%d]: failed to enqueue vertex[%d]!\r\n", result, vertex_id);
                free(degrees);
                return result;
            }
        }
    }

    while (!queue_is_empty(queue))
    {
        result = queue_dequeue(queue, &vertex_id, sizeof(Vertex));
        if (SUCCESS != result)
        {
            ERR_MSG("ERR[%d]: failed to dequeue!\r\n", result);
        }

        vertices[sort_num++] = vertex_id;

        node = graph->list[vertex_id]->next;
        while (!list_is_end(graph->list[vertex_id], node))
        {
            adjc_vertex = *(int *)node->data;
            degrees[adjc_vertex]--;
            if (degrees[adjc_vertex] == 0)
            {
                result = queue_enqueue(queue, &adjc_vertex, sizeof(Vertex));
                if (SUCCESS != result)
                {
                    ERR_MSG("ERR[%d]: failed to enqueue!\r\n", result);
                    free(degrees);
                    return result;
                }
            }

            node = node->next;
        }
    }

    queue_clear(&queue);

    free(degrees);

    return SUCCESS;
}

void graph_clear(Graph **graph)
{
    int vertex_id;

    if ((NULL == graph) || (NULL == *graph))
    {
        return;
    }

    for (vertex_id = 1; vertex_id <= (*graph)->vertex_num; vertex_id++)
    {
        free((*graph)->list[vertex_id]);
    }

    free(*graph);
    *graph = NULL;
}

void graph_print(Graph *graph)
{
    int vertex_id;

    if (NULL == graph)
    {
        ERR_MSG("null Pointer!\r\n");
        return;
    }

    printf("\r\nVertex's num: %d.", graph->vertex_num);
    printf("\r\nVertex's adjacent vertices: \r\n");

    for (vertex_id = 1; vertex_id <= graph->vertex_num; vertex_id++)
    {
        printf("%d: ", vertex_id);
        list_print_int(graph->list[vertex_id]);
    }

    printf("\r\n");
}
