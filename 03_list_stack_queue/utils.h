#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE   1
#define FALSE  0

enum err_code
{
    SUCCESS = 0,
    FAIL    = 1,
    UNDERFLOW = 2,
    OVERFLOW  = 3,
    MALLOC_FAIL  = 4,
    NUL_PTR = 5,
};

struct polynomial
{
    int coef;  /* coefficient */
    int expo;  /* exponent */
};

void error(char *msg);

#endif
