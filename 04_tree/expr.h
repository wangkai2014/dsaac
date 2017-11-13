/* description of arithmetic expression */

#ifndef __EXPR_H__
#define __EXPR_H__

#define EXPR_LEN    200
#define SYMBOL_LEN  10

enum ORDER_CODE
{
    PRE_ORDER     = 0,
    IN_ORDER      = 1,
    POST_ORDER    = 2,
    INVALID_ORDER
};

void set_prio();
void get_line(char *str);
int read_symbol(char *symbol, char *str, int *pos);
int is_operator(char ch);
int cmp_priority(char first, char second);
int transform_expr_order(char *dest_expr, int dest_order, char *src_expr, int src_order);

#endif
