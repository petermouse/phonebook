#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = fopen("orig.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (!fp) {
        printf("ERROR opening input file orig.txt\n");
        exit(0);
    }
    int i = 0;
    char append[50], find[50];
    double orig_sum_a = 0.0, orig_sum_f = 0.0, orig_a, orig_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find, &orig_a, &orig_f);
        orig_sum_a += orig_a;
        orig_sum_f += orig_f;
    }
    fclose(fp);

    double reduce_sum_a = 0.0, reduce_sum_f = 0.0, reduce_a, reduce_f;
    fp = fopen("reduce.txt", "r");
    if (!fp) {
        reduce_sum_a = reduce_sum_f = -100;
    } else {
        for (i = 0; i < 100; i++) {
            if (feof(fp)) {
                printf("ERROR: You need 100 datum instead of %d\n", i);
                printf("run 'make run' longer to get enough information\n\n");
                exit(0);
            }
            fscanf(fp, "%s %s %lf %lf\n", append, find, &reduce_a, &reduce_f);
            reduce_sum_a += reduce_a;
            reduce_sum_f += reduce_f;
        }
    }
    fclose(fp);

    double bst_sum_a = 0.0, bst_sum_f = 0.0, bst_a, bst_f;
    fp = fopen("bst.txt", "r");
    if (!fp) {
        bst_sum_a = bst_sum_f = -100;
    } else {
        for (i = 0; i < 100; i++) {
            if (feof(fp)) {
                printf("ERROR: You need 100 datum instead of %d\n", i);
                printf("run 'make run' longer to get enough information\n\n");
                exit(0);
            }
            fscanf(fp, "%s %s %lf %lf\n", append, find, &bst_a, &bst_f);
            bst_sum_a += bst_a;
            bst_sum_f += bst_f;
        }
    }
    fclose(fp);

    double hash_sum_a = 0.0, hash_sum_f = 0.0, hash_a, hash_f;
    fp = fopen("hash.txt", "r");
    if (!fp) {
        hash_sum_a = hash_sum_f = -100;
    } else {
        for (i = 0; i < 100; i++) {
            if (feof(fp)) {
                printf("ERROR: You need 100 datum instead of %d\n", i);
                printf("run 'make run' longer to get enough information\n\n");
                exit(0);
            }
            fscanf(fp, "%s %s %lf %lf\n", append, find, &hash_a, &hash_f);
            hash_sum_a += hash_a;
            hash_sum_f += hash_f;
        }
    }
    fclose(fp);

    fprintf(output, "append() %lf %lf %lf %lf\n",orig_sum_a / 100.0, reduce_sum_a / 100.0,
            bst_sum_a / 100.0, hash_sum_a / 100.0);
    fprintf(output, "findName() %lf %lf %lf %lf", orig_sum_f / 100.0, reduce_sum_f / 100.0,
            bst_sum_f / 100.0, hash_sum_f / 100.0);
    fclose(output);
    return 0;
}
