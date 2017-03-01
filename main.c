#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#if defined(BST)
#define OUT_FILE "bst.txt"
#elif defined(HASH)
#define OUT_FILE "hash.txt"
#elif defined(REDUCE)
#define OUT_FILE "reduce.txt"
#else
#define OUT_FILE "orig.txt"
#endif

#define INPUT_FILE "random.txt"
#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp,*input;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;
    int wordCount = 0;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    input = fopen(INPUT_FILE, "r");
    if (input == NULL) {
        printf("cannot open the input file\n");
        fclose(fp);
        return -1;
    }

#if defined(HASH)
    int hashValue;
    entry **hashTable = (entry **) malloc(sizeof(entry *) * HASH_TABLE_SIZE);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable[i] = (entry *) malloc(sizeof(entry));
        hashTable[i]->pNext = NULL;
    }
#endif

    /* build the entry */
    entry *pHead, *e;
    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        wordCount++;
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
#if defined(HASH)
        /* hash function implementation*/
        hashValue = djb2_hash(line);
        e = hashTable[hashValue];
        hashTable[hashValue] = insertFront(line, e);
#else
        e = append(line, e);
#endif
    }

#if defined(BST)
    /* binary search tree implementation */
    e = pHead;
    if(e)
        e = e->pNext;
    node *root = buildBST(&e, wordCount);
#endif

    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);

    /* the givn last name to find */
    char lastName[MAX_LAST_NAME_SIZE] = "zzzzzzzz";
    e = pHead;


#if defined(BST)
    assert(findNameByBST(lastName, root) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findNameByBST(lastName, root)->lastName, "zzzzzzzz"));
#elif defined(HASH)
    assert(findNameByHash(lastName, hashTable) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findNameByHash(lastName, hashTable)->lastName, "zzzzzzzz"));
#else
    assert(findName(lastName, e) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(lastName, e)->lastName, "zzzzzzzz"));
#endif

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);

    while (fscanf(input, " %s", lastName) != EOF) {

#if defined(BST)
        /* binary search tree implementation */
        findNameByBST(lastName, root);
#elif defined(HASH)
        /* hash function implementation */
        findNameByHash(lastName, hashTable);
#else
        /* orig and reduce version will fall into here */
        findName(lastName, e);
#endif

    }

    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    FILE *output = fopen(OUT_FILE, "a");
    fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
    fclose(input);
    fclose(output);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);

    if (pHead->pNext) free(pHead->pNext);
    free(pHead);

    return 0;
}
