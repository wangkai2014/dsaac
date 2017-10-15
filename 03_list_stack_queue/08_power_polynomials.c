#include "utils.h"
#include "list.h"
#include "polynomial.h"

static void test_power_polynomial_with_multiply(struct list *poly, int expo);
static void test_power_polynomial_with_square(struct list *poly, int expo);

int main()
{
    struct list *poly = NULL;
    int result = 0;
    int poly_expo = 5;
    int power_expo = 10;

    result = init_polynomial(&poly, poly_expo);
    if (SUCCESS != result)
    {
        print_error("failed to init polynomial!");
        return 0;
    }

    test_power_polynomial_with_multiply(poly, power_expo);

    test_power_polynomial_with_square(poly, power_expo);

    return 0;
}

static void test_power_polynomial_with_multiply(struct list *poly, int expo)
{
    struct list *power_poly = NULL;
    time_t start_time;
    time_t end_time;
    int result = 0;

    printf("\n1. count the power of polynomial with multiplication:\n\n");

    printf("f(x) = ");
    list_print_poly(poly);

    time(&start_time);

    result = power_polynomial_with_multiply(poly, expo, &power_poly);
    if (SUCCESS != result)
    {
        print_error("failed to power polynomial with multiply!");
        return;
    }

    time(&end_time);

    printf("[f(x)]^%d = ", expo);
    list_print_poly(power_poly);

    printf("\ncost time: %d s\n", (int)(end_time - start_time));
    
    list_clear(power_poly);
    power_poly = NULL;
}

static void test_power_polynomial_with_square(struct list *poly, int expo)
{
    struct list *power_poly = NULL;
    time_t start_time;
    time_t end_time;
    int result = 0;

    printf("\n2. count the power of polynomial with squre:\n\n");

    printf("f(x) = ");
    list_print_poly(poly);

    time(&start_time);

    result = power_polynomial_with_square(poly, expo, &power_poly);
    if (SUCCESS != result)
    {
        print_error("failed to power polynomial with square!");
        return;
    }

    time(&end_time);

    printf("\n[f(x)]^%d = ", expo);
    list_print_poly(power_poly);

    printf("\ncost time: %d s\n", (int)(end_time - start_time));
    
    list_clear(power_poly);
    power_poly = NULL;
}
