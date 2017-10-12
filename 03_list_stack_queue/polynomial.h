#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

int init_polynomial(struct list **poly, int max_expo);
int add_polynomials(struct list *poly_first, struct list *poly_second, struct list **poly_add);
int multiply_polynomials(struct list *poly_first, struct list *poly_second, struct list **poly_multiply);

#endif
