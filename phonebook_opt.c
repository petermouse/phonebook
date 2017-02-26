#include <stdlib.h>

#include "phonebook_opt.h"

entry *findName(char lastName[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}

/* binary search tree implementation */
node *buildBST(entry **head, int n)
{
    if (n <= 0)
        return NULL;

    node *left = buildBST(head, n/2);
    node *root = (node *) malloc(sizeof(node));
    root->pbEntry = *head;
    root->left = left;
    *head = (*head)->pNext;
    root->right = buildBST(head, n - n/2 - 1);

    return root;
}

entry *findNameByBST(char lastName[], node *root)
{
    if (root == NULL)
        return NULL;
    int result;
    if ( (result = strcasecmp(lastName, root->pbEntry->lastName)) == 0 )
        return root->pbEntry;
    else if (result < 0)
        return findNameByBST(lastName, root->left);
    else
        return findNameByBST(lastName, root->right);
    return NULL;
}

/* hash function implementation */
unsigned long djb2_hash(char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash % HASH_TABLE_SIZE;
}

entry *insertFront(char lastName[],entry* e)
{
    entry *pHead = (entry *) malloc(sizeof(entry));
    strcpy(e->lastName, lastName);
    pHead->pNext = e;
    return pHead;
}

entry *findNameByHash(char lastName[], entry **table)
{
    int hashValue = djb2_hash(lastName);
    return findName(lastName, table[hashValue]);
}
