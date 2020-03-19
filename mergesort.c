#include<stdlib.h>
#include<stdio.h>
#include "mergesort.h"
int THRESHOLD;

void merge(double* arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    double* L = malloc(n1* sizeof(double));
    double* R = malloc(n2* sizeof(double));

        for (i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(double* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void pparallelMergeSort(double* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        if (r - l <= THRESHOLD) {
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
        } else {

#pragma omp parallel num_threads(2)
            {
#pragma omp single
                {
#pragma omp task
                    {
                        pparallelMergeSort(arr, l, m);

                    }
#pragma omp task
                    {
                        pparallelMergeSort(arr, m + 1, r);

                    }
                }

            }
            merge(arr, l, m, r);

        }
    }
}
void parallelMergeSort(double* arr, int l, int r) {
    omp_set_nested(1);
    omp_set_num_threads(8);
    THRESHOLD = (r-l+1)/8;
    pparallelMergeSort(arr,l,r);
}
