#include "utils.h"
#include "list.h"

int init_graph(struct list ***graph, int vertex_num);
int read_graph(struct list **graph, int vertex_num, int edge_num);
int print_graph(struct list **graph, int vertex_num);
int clear_graph(struct list **graph, int vertex_num);

int main()
{
    int vertex_num = 0;
    int edge_num = 0;
    int result = SUCCESS;
    struct list **graph = NULL;

    printf("Enter the number of vertexs and edges in the graph: ");
    scanf("%d %d", &vertex_num, &edge_num);

    result = init_graph(&graph, vertex_num);
    if (SUCCESS != result)
    {
        print_error("failed to initialize the graph!");
        return 0;
    }

    result = read_graph(graph, vertex_num, edge_num);
    if (SUCCESS != result)
    {
        print_error("failed to read the graph!");
        clear_graph(graph, vertex_num);
        return 0;
    }
    
    result = print_graph(graph, vertex_num);
    if (SUCCESS != result)
    {
        print_error("failed to print the graph!");
        clear_graph(graph, vertex_num);
        return 0;
    }

    clear_graph(graph, vertex_num);

    return 0;
}

int init_graph(struct list ***in_graph, int vertex_num)
{
    int result = SUCCESS;
    int vertex_id = 0;
    struct list **graph = NULL;

    if ((NULL == graph) && (vertex_num < 0))
    {
        printf("invalid input! vertex_num = %d.\n", vertex_num);
        return INVALID_INPUT;
    }

    graph = (struct list **)malloc(sizeof(struct list *) * vertex_num);
    if (NULL == graph)
    {
        printf("failed to malloc memory for graph!\n");
        return MALLOC_FAIL;
    }

    memset(graph, 0, sizeof(struct list *) * vertex_num);

    for (vertex_id = 0; vertex_id < vertex_num; vertex_id++)
    {
        result = list_init(graph + vertex_id, sizeof(int));
        if (SUCCESS != result)
        {
            printf("failed to init list! vertex_id = %d.\n", vertex_id);
            free(graph);
            return result;
        }
    }

    *in_graph = graph;

    return SUCCESS;
}

int read_graph(struct list **graph, int vertex_num, int edge_num)
{
    int result = SUCCESS;
    int edge_id = 0;
    int vertex_a = 0;
    int vertex_b = 0;

    if ((NULL == graph) || (vertex_num < 0 ) || (edge_num < 0))
    {
        printf("invalid input! vertex_num = %d, edge_num = %d\n", vertex_num, edge_num);
    }

    printf("Enter the vertexs for each edge:\n");

    for (edge_id = 0; edge_id < edge_num; edge_id++)
    {
        scanf("%d %d", &vertex_a, &vertex_b);
        
        if ((vertex_a >= vertex_num) || (vertex_b >= vertex_num))
        {
            printf("invalid vertex! a=%d, b=%d.\n", vertex_a, vertex_b);
            return INVALID_INPUT;
        }

        result = list_push_back(graph[vertex_a], &vertex_b);
        if (SUCCESS != result)
        {
            printf("failed to add b to the list of a! a = %d, b = %d.\n", vertex_a, vertex_b);
            return result;
        }

        result = list_push_back(graph[vertex_b], &vertex_a);
        if (SUCCESS != result)
        {
            printf("failed to add a to the list of b! a = %d, b = %d.\n", vertex_a, vertex_b);
            return result;
        }
    }

    return SUCCESS;
}

int print_graph(struct list **graph, int vertex_num)
{
    int vertex_id = 0;

    if ((NULL == graph) || (vertex_num < 0))
    {
        printf("invalid input! vertex_num = %d.\n", vertex_num);
        return INVALID_INPUT;
    }

    for (vertex_id = 0; vertex_id < vertex_num; vertex_id++)
    {
        printf("%d : ", vertex_id);

        list_print_int(graph[vertex_id]);
    }

    return SUCCESS;
}

int clear_graph(struct list **graph, int vertex_num)
{
    int vertex_id;

    if ((NULL == graph) || (vertex_num < 0))
    {
        printf("invalid input! vertex_num = %d.\n", vertex_num);
        return INVALID_INPUT;
    }

    for (vertex_id = 0; vertex_id < vertex_num; vertex_id++)
    {
        list_clear(graph[vertex_id]);
    }

    return SUCCESS;
}
