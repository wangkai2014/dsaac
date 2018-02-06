#include "utils.h"
#include "qhash.h"

#define HASH1(data, size) ((data) % (size))
#define HASH2(data) (7 - (data) % 7)

int hash_init(HashTable **in_htbl, int size)
{
    HashTable *htbl;

    if ((NULL == in_htbl) || (size < 1))
    {
        ERR_MSG("invalid input! size=%d.\n", size);
        return INVALID_INPUT;
    }

    htbl = (HashTable *)malloc(sizeof(HashTable));
    if (NULL == htbl)
    {
        ERR_MSG("failed to malloc memory for hash table!\n");
        return MALLOC_FAIL;
    }

    htbl->size = size;

    htbl->arr = (HashEntry *)malloc(sizeof(HashEntry) * size);
    if (NULL == htbl->arr)
    {
        ERR_MSG("failed to malloc memory for htbl's array!\n");
        return MALLOC_FAIL;
    }

    memset(htbl->arr, 0, sizeof(HashEntry) * size);

    *in_htbl = htbl;

    return SUCCESS;
}

void hash_clear(HashTable **htbl)
{
    if ((NULL == htbl) || (NULL == *htbl))
    {
        return;
    }

    free((*htbl)->arr);
    (*htbl)->arr = NULL;
    free(*htbl);
    *htbl = NULL;
}

int hash_insert(HashTable *htbl, int data)
{
    int collid;
    int pos;
    int factor;

    if ((NULL == htbl) || (data < 0))
    {
        ERR_MSG("invalid input! data=%d.\n", data);
        return INVALID_INPUT;
    }

    pos = HASH1(data, htbl->size);
    factor = HASH2(data);

    for (collid = 0; collid < htbl->size; collid++)
    {
        if (htbl->arr[pos].status != USED)
        {
            htbl->arr[pos].data = data;
            htbl->arr[pos].status = USED;

            return pos;
        }

        pos = (pos + factor * collid) % htbl->size;
    }

    return INVALID_POS;
}

int hash_insert_and_check_collide(HashTable *htbl, int data, int *in_collid)
{
    int collid;
    int pos;
    int factor;

    if ((NULL == htbl) || (NULL == in_collid) || (data < 0))
    {
        ERR_MSG("invalid input! data=%d.\n", data);
        return INVALID_INPUT;
    }

    pos = HASH1(data, htbl->size);
    factor = HASH2(data);

    for (collid = 0; collid < htbl->size; collid++)
    {
        if (htbl->arr[pos].status != USED)
        {
            htbl->arr[pos].data = data;
            htbl->arr[pos].status = USED;
            *in_collid = collid;

            return pos;
        }

        pos = (pos + factor * collid) % htbl->size;
    }

    *in_collid = collid;

    return INVALID_POS;
}

int hash_delete(HashTable *htbl, int data)
{
    int pos;

    if ((NULL == htbl) || (data < 0))
    {
        ERR_MSG("invalid input! data=%d.\n", data);
        return INVALID_INPUT;
    }

    pos = hash_find(htbl, data);
    if (INVALID_POS != pos)
    {
        htbl->arr[pos].status = DELETED;
    }

    return SUCCESS;
}

int hash_find(HashTable *htbl, int data)
{
    int collid;
    int pos;
    int factor;

    if ((NULL == htbl) || (data < 0))
    {
        ERR_MSG("invalid input! data=%d.\n", data);
        return INVALID_INPUT;
    }

    pos = HASH1(data, htbl->size);
    factor = HASH2(data);

    for (collid = 0; collid < htbl->size; collid++)
    {
        if (htbl->arr[pos].status == UNUSED)
        {
            return INVALID_POS;
        }
        else if (htbl->arr[pos].data == data)
        {
            return ((htbl->arr[pos].status == USED)? pos : INVALID_POS);
        }

        pos = (pos + factor * collid) % htbl->size;
    }

    return INVALID_POS;
}

void hash_print(HashTable *htbl)
{
    int pos;

    if (NULL == htbl)
    {
        return;
    }

    for (pos = 0; pos < htbl->size; pos++)
    {
        if (USED == htbl->arr[pos].status)
        {
            printf("%d ", htbl->arr[pos].data);
        }
        else
        {
            printf("* ");
        }

        if (pos % 10 == 9)
        {
            printf("\n");
        }
    }

    printf("\n");
}
