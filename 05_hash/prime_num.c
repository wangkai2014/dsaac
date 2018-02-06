#include "utils.h"
#include "math.h"

int main()
{
    int begin;
    int num;
    int factor;
    int sqrt_num;

    printf("Enter the beginning num: ");
    scanf("%d", &begin);

    for (num = begin; ; num++)
    {
        sqrt_num = sqrt(num);
        for (factor = 2; factor <= sqrt_num; factor++)
        {
            if (num % factor == 0)
            {
                break;
            }
        }

        if (factor > sqrt_num)
        {
            printf("\nThe first prime number after %d is %d \n", begin, num);
            break;
        }
    }

    return 0;
}
