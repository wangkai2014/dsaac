#ifndef __UTILS_H__
#define __UTILS_H__

#define TRUE   1
#define FALSE  0

enum err_code
{
    SUCCESS = 0,
    FAIL    = 1,
    UNDERFLOW = 2,
    OVERFLOW  = 3,
    MALLOC_FAIL  = 4,
};

void error(char *msg);

#endif
