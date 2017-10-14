#include "utils.h"
#include "list.h"
#include "polynomial.h"

int generate_polynomial_arr(struct polynomial **poly_arr, int max_expo, int *term_num)
{
    struct polynomial *arr = NULL;
    int pos = 0;
    int coef;
    int expo;

    if (NULL == poly_arr)
    {
        error("null pointer!");
        return NUL_PTR;
    }

    arr = (struct polynomial *)malloc(sizeof(struct polynomial) * (max_expo+1));
    if (NULL == arr)
    {
        error("failed to malloc memory!");
        return MALLOC_FAIL;
    }

    for (expo = 0; expo <= max_expo; expo++)
    {
        coef = rand() % max_expo;
        if (coef > 0)
        {
            arr[pos].coef = coef;
            arr[pos].expo = expo;
            pos++;
        }
    }

    *poly_arr = arr;
    *term_num = pos;

    return SUCCESS;
}

int init_polynomial(struct list **poly, int max_expo)
{
    int arr_size = 0;
    int result = 0;
    struct polynomial *poly_arr = NULL;

    srand((unsigned)time(NULL));

    result = generate_polynomial_arr(&poly_arr, max_expo, &arr_size);
    if (SUCCESS != result)
    {
        error("failed to generate polynomial array!");
        return result;
    }

    result = list_create_from_poly_arr(poly, poly_arr, arr_size);
    if (SUCCESS != result)
    {
        error("failed to create list poly_first from polynomial array!");
        return result;
    }

    return SUCCESS;
}

int add_polynomials(struct list *poly_first, struct list *poly_second, struct list **poly_add)
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

    result = list_init(poly_add, sizeof(struct polynomial));
    if (SUCCESS != result)
    {
        error("failed to init list poly_add!");
        return result;
    }

    cur_first = poly_first->next;
    cur_second = poly_second->next;
    cur_add = *poly_add;

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

        result = list_insert(*poly_add, cur_add, (void *)&data);
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
        result = list_insert(*poly_add, cur_add, cur_first->data);
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

int multiply_polynomial_with_term(struct list *poly, struct polynomial *term)
{
    int result = 0;
    struct list *cur_poly = NULL;
    struct polynomial *data = NULL;

    if ((NULL == poly) || (NULL == term))
    {
        error("null pointer!");
        return NUL_PTR;
    }

    cur_poly = poly->next;

    while (NULL != cur_poly)
    {
        data = (struct polynomial *)cur_poly->data;
        data->coef *= term->coef;
        data->expo += term->expo;

        cur_poly = cur_poly->next;
    }

    return SUCCESS;
}

int multiply_polynomials(struct list *poly_first, struct list *poly_second, struct list **poly_multiply)
{
    int result = 0;
    struct list *cur_first = NULL;
    struct list *cur_multiply = NULL;
    struct list *poly_add = NULL;  

    if ((NULL == poly_first) || (NULL == poly_second) || (NULL == poly_multiply))
    {
        error("null pointer!");
        return NUL_PTR;
    }

    result = list_init(poly_multiply, sizeof(struct polynomial));
    if (SUCCESS != result)
    {
        error("failed to init list poly_multiply!");
        return result;
    }

    cur_first = poly_first->next;
    cur_multiply = *poly_multiply;

    while (NULL != cur_first)
    {
        result = list_copy(&cur_multiply, poly_second, sizeof(struct polynomial));
        if (SUCCESS != result)
        {
            error("failed to copy list from poly_second to cur_multiply!");
            return result;
        }
        
        result = multiply_polynomial_with_term(cur_multiply, (struct polynomial *)cur_first->data);
        if (SUCCESS != result)
        {
            error("failed to multiply polynomial with term!");
            list_clear(cur_multiply);
            return result;
        }

        result = add_polynomials(*poly_multiply, cur_multiply, &poly_add);
        if (SUCCESS != result)
        {
            error("failed to add polynomials!");
            list_clear(cur_multiply);
            return result;
        }

        *poly_multiply = poly_add;
        list_clear(cur_multiply);

        cur_first = cur_first->next;
    }

    return SUCCESS;
}
