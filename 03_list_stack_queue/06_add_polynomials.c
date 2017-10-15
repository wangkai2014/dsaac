#include "utils.h"
#include "list.h"
#include "polynomial.h"

int main()
{
    struct list *poly_first = NULL;
    struct list *poly_second = NULL;
    struct list *poly_add = NULL;
    int result = 0;

    result = init_polynomial(&poly_first, 6);
    if (SUCCESS != result)
    {
        print_error("failed to init poly_first!");
        return 0;
    }

    result = init_polynomial(&poly_second, 8);
    if (SUCCESS != result)
    {
        print_error("failed to init poly_second!");
        return 0;
    }

    printf("poly_1:\n");
    list_print_poly(poly_first);
    printf("poly_2:\n");
    list_print_poly(poly_second);

    result = add_polynomials(poly_first, poly_second, &poly_add);
    if (SUCCESS != result)
    {
        print_error("failed to add polynomials!");
        return 0;
    }

    printf("poly_1 + poly_2:\n");
    list_print_poly(poly_add);


    list_clear(poly_first);
    list_clear(poly_second);
    list_clear(poly_add);

    return 0;
}

