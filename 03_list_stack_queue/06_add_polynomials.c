#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"
#include "list.h"

int generate_polynomial_arr(struct polynomial *arr, int max_expo, int *term_num);
int init_polynomials(struct list **poly_first, struct list **poly_second, struct list **poly_add);
int add_polynomials(struct list *poly_first, struct list *poly_second, struct list *poly_add);
void clear_polynomials(struct list *poly_first, struct list *poly_second, struct list *poly_add);

int main()
{
    struct list *poly_first = NULL;
    struct list *poly_second = NULL;
    struct list *poly_add = NULL;
    int result = 0;

    result = init_polynomials(&poly_first, &poly_second, &poly_add);
    if (SUCCESS != result)
    {
        error("failed to init polynomials!");
        return 0;
    }

    printf("poly_1:\n");
    list_print_poly(poly_first);
    printf("poly_2:\n");
    list_print_poly(poly_second);

    result = add_polynomials(poly_first, poly_second, poly_add);
    if (SUCCESS != result)
    {
        error("failed to add polynomials!");
        return 0;
    }

    printf("poly_1 + poly_2:\n");
    list_print_poly(poly_add);

    clear_polynomials(poly_first, poly_second, poly_add);

    return 0;
}

int generate_polynomial_arr(struct polynomial *arr, int max_expo, int *term_num)
{
    int pos = 0;
    int coef;
    int expo;

    if (NULL == arr)
    {
        error("null pointer!");
        return NUL_PTR;
    }

    for (expo = 0; expo < max_expo; expo++)
    {
        coef = rand() % max_expo;
        if (coef > 0)
        {
            arr[pos].coef = coef;
            arr[pos].expo = expo;
            pos++;
        }
    }

    *term_num = pos;

    return SUCCESS;
}

int init_polynomials(struct list **poly_first, struct list **poly_second, struct list **poly_add)
{
    int arr_size = 0;
    int result = 0;
    struct polynomial poly_arr[10];

    srand((unsigned)time(NULL));

    /* init poly_first */
    result = generate_polynomial_arr(poly_arr, 10, &arr_size);
    if (SUCCESS != result)
    {
        error("failed to generate polynomial array!");
        return result;
    }

    result = list_create_from_poly_arr(poly_first, poly_arr, arr_size);
    if (SUCCESS != result)
    {
        error("failed to create list poly_first from polynomial array!");
        return result;
    }

    /* init poly_second */
    memset((void *)poly_arr, 0, sizeof(poly_arr));
    
    result = generate_polynomial_arr(poly_arr, 10, &arr_size);
    if (SUCCESS != result)
    {
        error("failed to generate polynomial array!");
        return result;
    }

    result = list_create_from_poly_arr(poly_second, poly_arr, arr_size);
    if (SUCCESS != result)
    {
        error("failed to create list poly_second from polynomial array!");
        return result;
    }

    /* init poly_add */
    result = list_init(poly_add, sizeof(struct polynomial));
    if (SUCCESS != result)
    {
        error("failed to init list poly_add!");
        return result;
    }

    return SUCCESS;
}

int add_polynomials(struct list *poly_first, struct list *poly_second, struct list *poly_add)
{
    struct list *cur_first = NULL;
    struct list *cur_second = NULL;
    struct list *cur_add = NULL;
    struct polynomial data;
    int result = 0;

    if ((poly_first == NULL) || (poly_second == NULL) || (poly_add == NULL))
    {
        error("null pointer!");
        return NUL_PTR;
    }

    cur_first = poly_first->next;
    cur_second = poly_second->next;
    cur_add = poly_add;

    while ((NULL != cur_first) && (NULL != cur_second))
    {
        if ((*(struct polynomial*)cur_first->data).expo < (*(struct polynomial*)cur_second->data).expo)
        {
            data.expo = ((struct polynomial *)cur_first->data)->expo;
            data.coef = ((struct polynomial *)cur_first->data)->coef;
            cur_first = cur_first->next;
        }
        else if ((*(struct polynomial*)cur_first->data).expo > (*(struct polynomial*)cur_second->data).expo)
        {
            data.expo = ((struct polynomial *)cur_second->data)->expo;
            data.coef = ((struct polynomial *)cur_second->data)->coef;
            cur_second = cur_second->next;
        }
        else
        {
            data.expo = ((struct polynomial *)cur_first->data)->expo;
            data.coef = ((struct polynomial *)cur_first->data)->coef + ((struct polynomial *)cur_second->data)->coef;
            cur_first = cur_first->next;
            cur_second = cur_second->next;
        }

        result = list_insert(poly_add, cur_add, (void *)&data);
        if (SUCCESS != result)
        {
            error("failed to insert list!");
            return result;
        }

        cur_add = cur_add->next;
    }

    if (NULL == cur_first)
    {
        cur_first = cur_second;
    }

    while (NULL != cur_first)
    {
        result = list_insert(poly_add, cur_add, cur_first->data);
        if (SUCCESS != result)
        {
            error("failed to insert list!");
            return result;
        }

        cur_first = cur_first->next;
        cur_add = cur_add->next;
    }

    return SUCCESS;
}

void clear_polynomials(struct list *poly_first, struct list *poly_second, struct list *poly_add)
{
    list_clear(poly_first);

    list_clear(poly_second);

    list_clear(poly_add);
}
