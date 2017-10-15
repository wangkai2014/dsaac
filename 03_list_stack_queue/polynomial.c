#include "utils.h"
#include "list.h"
#include "polynomial.h"

#define MAX_COEFFICIENT  5

int generate_polynomial_arr(struct polynomial **poly_arr, int max_expo, int *term_num)
{
    struct polynomial *arr = NULL;
    int pos = 0;
    int coef;
    int expo;

    if (NULL == poly_arr)
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    arr = (struct polynomial *)malloc(sizeof(struct polynomial) * (max_expo+1));
    if (NULL == arr)
    {
        print_error("failed to malloc memory!");
        return MALLOC_FAIL;
    }

    for (expo = 0; expo <= max_expo; expo++)
    {
        coef = rand() % MAX_COEFFICIENT;
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
        print_error("failed to generate polynomial array!");
        return result;
    }

    result = list_create_from_poly_arr(poly, poly_arr, arr_size);
    if (SUCCESS != result)
    {
        print_error("failed to create list poly_first from polynomial array!");
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
        print_error("null pointer!");
        return NUL_PTR;
    }

    result = list_init(poly_add, sizeof(struct polynomial));
    if (SUCCESS != result)
    {
        print_error("failed to init list poly_add!");
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
            print_error("failed to insert list!");
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
            print_error("failed to insert list!");
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
        print_error("null pointer!");
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
        print_error("null pointer!");
        return NUL_PTR;
    }

    result = list_init(poly_multiply, sizeof(struct polynomial));
    if (SUCCESS != result)
    {
        print_error("failed to init list poly_multiply!");
        return result;
    }

    cur_first = poly_first->next;
    cur_multiply = *poly_multiply;

    while (NULL != cur_first)
    {
        result = list_copy(&cur_multiply, poly_second, sizeof(struct polynomial));
        if (SUCCESS != result)
        {
            print_error("failed to copy list from poly_second to cur_multiply!");
            return result;
        }
        
        result = multiply_polynomial_with_term(cur_multiply, (struct polynomial *)cur_first->data);
        if (SUCCESS != result)
        {
            print_error("failed to multiply polynomial with term!");
            list_clear(cur_multiply);
            return result;
        }

        result = add_polynomials(*poly_multiply, cur_multiply, &poly_add);
        if (SUCCESS != result)
        {
            print_error("failed to add polynomials!");
            list_clear(cur_multiply);
            return result;
        }

        *poly_multiply = poly_add;
        poly_add = NULL;
        list_clear(cur_multiply);

        cur_first = cur_first->next;
    }

    return SUCCESS;
}

int power_polynomial_with_multiply(struct list *poly, int expo, struct list **power_poly)
{
    int result = 0;
    int cur_expo = 0;
    struct list *first_poly = NULL;
    struct list *product_poly = NULL;

    if ((NULL == poly) || (NULL == power_poly))
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    result = list_copy(&first_poly, poly, sizeof(struct polynomial));
    if (SUCCESS != result)
    {
        print_error("failed to copy list!");
        return result;
    }

    for (cur_expo = 1; cur_expo < expo; cur_expo++)
    {
        result = multiply_polynomials(first_poly, poly, &product_poly);
        if (SUCCESS != result)
        {
            print_error("failed to multiply polynomial!");
            return result;
        }

        list_clear(first_poly);
        first_poly = product_poly;
        product_poly = NULL;
    }

    *power_poly = first_poly;

    return SUCCESS;
}

int power_polynomial_with_square(struct list *poly, int expo, struct list **power_poly)
{
    struct list *product_poly = NULL;
    int result = 0;

    if ((NULL == poly) || (NULL == power_poly))
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    if (expo == 1)
    {
        result = list_copy(power_poly, poly, sizeof(struct polynomial));
        if (SUCCESS != result)
        {
            print_error("failed to copy list!");
        }

        return result;
    }

    result = power_polynomial_with_square(poly, expo/2, &product_poly);
    if (SUCCESS != result)
    {
        print_error("failed to power polynomial with square!");
        return result;
    }

    result = multiply_polynomials(product_poly, product_poly, power_poly);
    if (SUCCESS != result)
    {
        print_error("failed to multiply polynomials!");
        list_clear(product_poly);
        return result;
    }

    list_clear(product_poly);

    if (expo % 2 == 1)
    {
        product_poly = *power_poly;
        *power_poly = NULL;

        result = multiply_polynomials(product_poly, poly, power_poly);
        if (SUCCESS != result)
        {
            print_error("failed to multiply polynomials!");
            list_clear(product_poly);
            return result;
        }

        list_clear(product_poly);
    }

    return SUCCESS;
}

/* 进位处理。
 * 注意约束条件：
 * 1. 满10进1
 * 2. 多项式的项从小到大排列，系数为0的项也保留。
 * 3. 多项式每一项的系数应该小于20。因为两个加数的当前位相加最多为18，加上进位最多为19 */
int carry_polynomials(struct list *poly)
{
    int carry = 0;
    int coef = 0;
    int expo = 0;
    int result = SUCCESS;
    struct list *cur = NULL;
    struct polynomial data;

    if (NULL == poly)
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    cur = poly->next;

    while (cur != NULL)
    {
        expo = ((struct polynomial *)cur->data)->expo; 
        coef = ((struct polynomial *)cur->data)->coef + carry; 

        ((struct polynomial *)cur->data)->coef = coef % 10;
        carry = coef / 10;

        cur = cur->next;
    }

    if (carry > 0)
    {
        data.expo = expo + 1;
        data.coef = carry;

        result = list_push_back(poly, &data);
        if (SUCCESS != result)
        {
            print_error("failed to push back list!");
            return result;
        }
    }

    return SUCCESS;
}

/* 增加进位处理的多项式乘法 */
int multiply_polynomials_with_carry(struct list *poly_first, struct list *poly_second, struct list **poly_multiply)
{
    int result = 0;
    struct list *cur_first = NULL;
    struct list *cur_multiply = NULL;
    struct list *poly_add = NULL;  

    if ((NULL == poly_first) || (NULL == poly_second) || (NULL == poly_multiply))
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    result = list_init(poly_multiply, sizeof(struct polynomial));
    if (SUCCESS != result)
    {
        print_error("failed to init list poly_multiply!");
        return result;
    }

    cur_first = poly_first->next;
    cur_multiply = *poly_multiply;

    while (NULL != cur_first)
    {
        result = list_copy(&cur_multiply, poly_second, sizeof(struct polynomial));
        if (SUCCESS != result)
        {
            print_error("failed to copy list from poly_second to cur_multiply!");
            return result;
        }
        
        result = multiply_polynomial_with_term(cur_multiply, (struct polynomial *)cur_first->data);
        if (SUCCESS != result)
        {
            print_error("failed to multiply polynomial with term!");
            list_clear(cur_multiply);
            return result;
        }

        carry_polynomials(cur_multiply); /* 进位处理 */

        result = add_polynomials(*poly_multiply, cur_multiply, &poly_add);
        if (SUCCESS != result)
        {
            print_error("failed to add polynomials!");
            list_clear(cur_multiply);
            return result;
        }

        carry_polynomials(poly_add);

        *poly_multiply = poly_add;
        poly_add = NULL;
        list_clear(cur_multiply);

        cur_first = cur_first->next;
    }

    return SUCCESS;
}

int power_polynomial_with_multiply_carry(struct list *poly, int expo, struct list **power_poly)
{
    int result = 0;
    int cur_expo = 0;
    struct list *first_poly = NULL;
    struct list *product_poly = NULL;

    if ((NULL == poly) || (NULL == power_poly))
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    result = list_copy(&first_poly, poly, sizeof(struct polynomial));
    if (SUCCESS != result)
    {
        print_error("failed to copy list!");
        return result;
    }

    for (cur_expo = 1; cur_expo < expo; cur_expo++)
    {
        result = multiply_polynomials_with_carry(first_poly, poly, &product_poly);
        if (SUCCESS != result)
        {
            print_error("failed to multiply polynomial!");
            return result;
        }

        list_clear(first_poly);
        first_poly = product_poly;
        product_poly = NULL;
    }

    *power_poly = first_poly;

    return SUCCESS;
}

int power_polynomial_with_square_carry(struct list *poly, int expo, struct list **power_poly)
{
    struct list *product_poly = NULL;
    int result = 0;

    if ((NULL == poly) || (NULL == power_poly))
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    if (expo == 1)
    {
        result = list_copy(power_poly, poly, sizeof(struct polynomial));
        if (SUCCESS != result)
        {
            print_error("failed to copy list!");
        }

        return result;
    }

    result = power_polynomial_with_square(poly, expo/2, &product_poly);
    if (SUCCESS != result)
    {
        print_error("failed to power polynomial with square!");
        return result;
    }

    result = multiply_polynomials_with_carry(product_poly, product_poly, power_poly);
    if (SUCCESS != result)
    {
        print_error("failed to multiply polynomials!");
        list_clear(product_poly);
        return result;
    }

    list_clear(product_poly);

    if (expo % 2 == 1)
    {
        product_poly = *power_poly;
        *power_poly = NULL;

        result = multiply_polynomials_with_carry(product_poly, poly, power_poly);
        if (SUCCESS != result)
        {
            print_error("failed to multiply polynomials!");
            list_clear(product_poly);
            return result;
        }

        list_clear(product_poly);
    }

    return SUCCESS;
}
