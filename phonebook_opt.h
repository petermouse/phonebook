#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LAST_NAME_SIZE 16
#define OPT 1

typedef struct __PHONE_BOOK_DATA {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} data;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_ENTRY *pNext;
    data *info;
} entry;

entry *findName(char lastName[], entry *pHead);
entry *append(char lastName[], entry *e);

/* binary search tree implementation */
typedef struct __TREE_NODE {
    entry *pbEntry;
    struct __TREE_NODE *left;
    struct __TREE_NODE *right;
} node;

node *buildBST (entry **head, int n);
entry *findNameByBST(char lastName[], node *root);

#endif
