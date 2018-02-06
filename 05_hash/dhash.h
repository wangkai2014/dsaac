#ifndef __DHASH_H__
#define __DHASH_H__

#define INVALID_POS    -1
#define MAX_HASH_ELEM  10000

enum status_code
{
    UNUSED   = 0,
    USED     = 1,
    DELETED  = 2
};

typedef enum status_code STATUS;

struct hash_entry
{
    STATUS status;
    int data;
};

typedef struct hash_entry HashEntry;

struct hash_table
{
    int size;
    HashEntry *arr;
};

typedef struct hash_table HashTable;

int hash_init(HashTable **htbl, int size);
void hash_clear(HashTable **htbl);
int hash_insert(HashTable *htbl, int data);
int hash_delete(HashTable *htbl, int data);
int hash_find(HashTable *htbl, int data);
void hash_print(HashTable *htbl);
int hash_insert_and_check_collide(HashTable *htbl, int data, int *collid);
#endif
