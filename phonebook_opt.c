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
