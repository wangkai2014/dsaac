#include "utils.h"
#include "lhash.h"

enum OPER_CODE
{
    INIT      = 0;
    CLEAR     = 1;
    INSERT    = 2;
    DELETE    = 3;
    FIND      = 4;
    PRINT     = 5;
    COLLIDE   = 6;
    QUIT
};

typedef void (*FUNC_PTR)(HashTable **);

void test_hash_init(HashTable **htbl);
void test_hash_clear(HashTable **htbl);
void test_hash_insert(HashTable **htbl);
void test_hash_delete(HashTable **htbl);
void test_hash_find(HashTable **htbl);
void test_hash_print(HashTable **htbl);
void test_hash_collide(HashTable **htbl);

void generate_data(int **data, int num);

int g_ttl_num = 0;
int g_ttl_collid = 0;

int main()
{
    int oper = 0;
    HashTable *htbl = NULL;
    FUNC_PTR test_func[] = { test_hash_init,
                             test_hash_clear,
                             test_hash_insert,
                             test_hash_delete,
                             test_hash_find,
                             test_hash_print,
                             test_hash_collide
    };

    while (1)
    {
        printf("\n0.init 1.clear 2.insert 3.delete 4.find 5.print 6.quit 7.collide");
        printf("\nEnter operation: ");
        scanf("%d", &oper);

        if (oper >= QUIT)
        {
            break;
        }

        (test_func[oper])(&htbl);

        printf("\n");
    }

    hash_clear(&htbl);

    return 0;
}

void test_hash_init(HashTable **htbl)
{
    int result;

    result = hash_init(htbl);
    if (SUCCESS != result)
    {
        ERR_MSG("err(%d): failed to init hash table!\n", result);
    }
    else
    {
        printf("\ninit hash table successfully.");
    }
}

void test_hash_clear(HashTable **htbl)
{
    hash_clear(htbl);

    printf("\nclear hash table successfully.");
}

void test_hash_insert(HashTable **htbl)
{
    printf("\ninsert hash table successfully.");
}

void test_hash_delete(HashTable **htbl)
{
    printf("\ndelete hash table successfully.");
}

void test_hash_find(HashTable **htbl)
{
    int target = 0;
    int pos = 0;
    int result;

    printf("\nEnter the data you want to find: ");
    scanf("%d", &target);

    result = hash_find(htbl, target, &pos);
    if (SUCCESS != result)
    {
        printf("\nfailed to find %d in the hash table!", target);
    }
    else
    {
        printf("\ndata %d is at position %d.", target, pos);
    }

    return;
}

void test_hash_print(HashTable **htbl)
{
    hash_print(htbl);
}

void test_hash_collide(HashTable **htbl)
{
    int *data = NULL;
    int pos;
    int result;
    int num = 0;
    int collid = 0;

    printf("\nEnter the number of elements you want to insert: ");
    scanf("%d", &num);

    result = generate_data(&data, num);
    if (SUCCESS != result)
    {
        ERR_MSG("\nerr(%d): failed to generate data! num=%d.", result, num);
        return;
    }

    for (pos = 0; pos < num; pos++)
    {
        result = hash_insert_and_check_collide(htbl, data[pos], &collid);
        if (SUCCESS != result)
        {
            ERR_MSG("\nerr(%d): failed to insert %d to hash table!", result, data[pos]);
            return;
        }

        if (collid > 0)
        {
            printf("\ninsert %d to hash table with %d collisions.", data[pos], collid);
            g_ttl_collid += collid;
            collid = 0;
        }
    }

    g_ttl_num += num;

    printf("\ntotal insert: %d, total collision: %d, collision ratio: %f.", g_ttl_num, g_ttl_collid, (double)g_ttl_collid / (double)g_ttl_num);

    free(data);
}

int generate_data(int **in_data, int num)
{
    int *data;
    int pos;

    if ((NULL == in_data) || (num < 1))
    {
        ERR_MSG("invalid input! num=%d.", num);
        return INVALID_INPUT;
    }

    data = (int *)malloc(sizeof(int) * num);
    if (NULL == data)
    {
        ERR_MSG("failed to malloc memory for data!\n");
        return MALLOC_FAIL;
    }

    srand((unsigned)time(0));

    for (pos = 0; pos < num; pos++)
    {
        data[pos] = rand() % MAX_HASH_ELEM;

        printf("%d ", data[pos]);
    }

    printf("\n");

    *in_data = data;

    return SUCCESS;
}
