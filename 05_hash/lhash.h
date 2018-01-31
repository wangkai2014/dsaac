#ifndef __LHASH_H__
#define __LHASH_H__

enum STATUS
{
    UNUSED   = 0,
    USED     = 1,
    DELETED  = 2
};

struct hash_entry
{
    STAUTS status;
    int data;
};

typedef struct hash_entry HashEntry;

struct hash_table
{
    int size;
    HashEntry *data;
};

typedef struct hash_table HashTable;

#endif
