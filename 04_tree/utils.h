#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE   1
#define FALSE  0

#define MAX_BIT_NUM  32  /* int型整数以二进制表示时的最大位数 */

enum err_code
{
    SUCCESS = 0,
    FAIL    = 1,
    UNDERFLOW = 2,
    OVERFLOW  = 3,
    MALLOC_FAIL  = 4,
    NUL_PTR = 5,
    OUT_OF_RANGE = 6,
    INVALID_INPUT = 7,
    NOT_FOUND = 8,
    DUPLI_DATA = 9,
};

struct polynomial
{
    int coef;  /* coefficient */
    int expo;  /* exponent */
};

struct student
{
    int id;
    int secu_num;  /* social security number */
};

void print_error(char *msg);

#endif
