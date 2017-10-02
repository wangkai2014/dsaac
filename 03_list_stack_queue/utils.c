#include <stdio.h>
#include "list.h"

static inline void error(char *msg)
{
    printf("func %s, line %d, %s\n", __FUNCTION__, __LINE__, msg);
}
