#include "utils.h"
#include "list.h"
#include "polynomial.h"
#include "arithmetic.h"

static int str_to_poly(char *str, struct list **poly);
static int poly_to_str(char *str, struct list *poly);

int add(char *first_operand, char *second_operand, char *answer)
{
    struct list *first_poly = NULL;
    struct list *second_poly = NULL;
    struct list *add_poly = NULL;
    int result = SUCCESS;

    memset(answer, 0 ,MAX_DIGIT_NUM);

    str_to_poly(first_operand, &first_poly);
    str_to_poly(second_operand, &second_poly);

    result = add_polynomials(first_poly, second_poly, &add_poly);
    if (SUCCESS != result)
    {
        print_error("failed to add polynomials!");
        return result;
    }

    /* 进位处理 */
    result = carry_polynomials(add_poly);  
    if (SUCCESS != result)
    {
        print_error("failed to carry polynomials!");
    }

    poly_to_str(answer, add_poly);

    list_clear(first_poly);
    list_clear(second_poly);
    list_clear(add_poly);

    return SUCCESS;
}

int subtract(char *first_operand, char *second_operand, char *answer)
{
    memset(answer, 0 ,MAX_DIGIT_NUM);

    return SUCCESS;
}

int multiply(char *first_operand, char *second_operand, char *answer)
{
    struct list *first_poly = NULL;
    struct list *second_poly = NULL;
    struct list *product_poly = NULL;
    int result = SUCCESS;

    memset(answer, 0, MAX_DIGIT_NUM);

    str_to_poly(first_operand, &first_poly);
    str_to_poly(second_operand, &second_poly);

    result = multiply_polynomials_with_carry(first_poly, second_poly, &product_poly);
    if (SUCCESS != result)
    {
        print_error("failed to multiply polynomials with carry!");
        return result;
    }
    
    poly_to_str(answer, product_poly);

    list_clear(first_poly);
    list_clear(second_poly);
    list_clear(product_poly);

    return SUCCESS;
}

int divide(char *first_operand, char *second_operand, char *answer)
{
    memset(answer, 0 ,MAX_DIGIT_NUM);

    return SUCCESS;
}

int exponent(char *base, char *power, char *answer)
{
    struct list *base_poly = NULL;
    struct list *power_poly = NULL;
    int expo = 0;
    int result = SUCCESS;

    memset(answer, 0, MAX_DIGIT_NUM);

    str_to_poly(base, &base_poly);

    expo = atoi(power);

    result = power_polynomial_with_multiply_carry(base_poly, expo, &power_poly);
    if (SUCCESS != result)
    {
        print_error("failed to multiply polynomials with carry!");
        return result;
    }
    
    poly_to_str(answer, power_poly);

    list_clear(base_poly);
    list_clear(power_poly);

    return SUCCESS;
}

static int str_to_poly(char *str, struct list **poly)
{
    int len = 0;
    int pos = 0;
    int result = SUCCESS;
    struct polynomial *poly_arr;

    if ((NULL == str) || (NULL == poly))
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    len = strlen(str);

    poly_arr = (struct polynomial *)malloc(sizeof(struct polynomial) * len);
    if (NULL == poly_arr)
    {
        print_error("failed to malloc memory for poly_arr!");
        return MALLOC_FAIL;
    }

    for (pos = 0; pos < len; pos++)
    {
        poly_arr[pos].expo = pos;
        poly_arr[pos].coef = str[len - 1 - pos] - '0';
    }

    result = list_create_from_poly_arr(poly, poly_arr, len);
    if (SUCCESS != result)
    {
        print_error("failed to create list from polynomial array!");
        return result;
    }

    return SUCCESS;
}

static int poly_to_str(char *str, struct list *poly)
{
    int result = SUCCESS;
    int pos = 0;
    /* 由于链表存储整数时从低位到高位，与数组存储顺序相反，所以先用一个辅助数组来获取链表表示的整数 */
    char aux_str[MAX_DIGIT_NUM + 1]; 
    struct list *cur = NULL;
    
    if ((NULL == str) || (NULL == poly))
    {
        print_error("null pointer!");
        return NUL_PTR;
    }

    aux_str[MAX_DIGIT_NUM] = 0;
    cur = poly->next;

    for (pos = MAX_DIGIT_NUM - 1; pos >= 0; pos--)
    {
        if (NULL == cur)
        {
            break;
        }

        aux_str[pos] = '0' + ((struct polynomial *)cur->data)->coef;
        cur = cur->next;
    }

    memcpy(str, aux_str + pos + 1, MAX_DIGIT_NUM - pos);

    return SUCCESS;
}
