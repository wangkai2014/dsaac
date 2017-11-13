#include "utils.h"
#include "expr.h"

int main()
{
    int src_order = INVALID_ORDER;
    int dest_order = INVALID_ORDER;
    char src_expr[EXPR_LEN];
    char dest_expr[EXPR_LEN];

    while (1)
    {
        memset(src_expr, 0, EXPR_LEN);
        memset(dest_expr, 0, EXPR_LEN);

        printf("\n0.preorder 1.inorder 2.postorder");
        printf("\nEnter source and destination expression's order: ");
        scanf("%d %d", &src_order, &dest_order);

        if ((src_order >= INVALID_ORDER) || (dest_order >= INVALID_ORDER))
        {
            printf("bye~bye~\n");
            return 0;
        }

        printf("Enter source expression:\n");
        getchar();  /* skip the Enter key */
        get_line(src_expr);

        transform_expr_order(dest_expr, dest_order, src_expr, src_order);

        printf("destination expression: \n%s\n", dest_expr);
    }

    return 0;
}
