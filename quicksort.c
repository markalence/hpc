#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include <jmorecfg.h>
int THRESHOLD;


void swap(double *a, double *b) {
    double t = *a;
    *a = *b;
    *b = t;
}

int partition(double arr[], int low, int high) {
    double pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void serialQuickSort(double* arr, int low, int high) {
//    printf("%s\n","SERIAL");
    if (low < high) {
        int pi = partition(arr, low, high);
        serialQuickSort(arr, low, pi - 1);
        serialQuickSort(arr, pi + 1, high);
    }
}

void pparallelQuickSort(double* arr, int low, int high) {
    if (low < high) {
        const int pi = partition(arr, low, high);
        int upper = pi - 1 - low < THRESHOLD;
        int lower = high - pi - 1 < THRESHOLD;
        omp_set_nested(1);
        omp_set_num_threads(8);

#pragma omp parallel
#pragma omp single
        {
#pragma omp task
            if (upper) {
//                printf("%d\n",omp_get_thread_num());
                serialQuickSort(arr, low, pi-1);
            } else {
                pparallelQuickSort(arr, low, pi-1);
            }

#pragma omp task
            if (lower) {
//                printf("%d\n",omp_get_thread_num());
                serialQuickSort(arr, pi + 1, high);
            } else {
                pparallelQuickSort(arr, pi + 1, high);
            }

        };
    }


}

void parallelQuickSort(double* arr, int low, int high){
    THRESHOLD = (high-low)/8;
    pparallelQuickSort(arr,low,high);
}
