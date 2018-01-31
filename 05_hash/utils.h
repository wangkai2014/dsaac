#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE   1
#define FALSE  0

#define ERR_MSG(format, ...)  printf("%s(%d): ", __FUNCTION__, __LINE__); printf(format, ##__VA_ARGS__)

#define MAX(a, b)    (((a) > (b)) ? (a) : (b))
#define ABS(a, b)    (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))

#define MAX_BIT_NUM  32  /* int型整数以二进制表示时的最大位数 */

typedef unsigned char uchar;
typedef unsigned int uint;

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
    DUPLICATED = 9,
};

struct polynomial
{
    int coef;  /* coefficient */
    int expo;  /* exponent */
};

#endif
