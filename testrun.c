#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include "quicksort.h"
#include "mergesort.h"
#include "utility.h"
#include <math.h>
#include "bitonicsort.h"

double *testrun(int d, int r, int n) {

    double *rpoints = generateDoubleArray(r * d);
    double *qpoints = generateDoubleArray(n * d);
    double *dist = generateDoubleArray(n * r);
    double *copy = generateDoubleArray(n * r);
    double *times = malloc(sizeof(double) * 4);

    double start = omp_get_wtime();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < r; ++j) {
            double x = euclidDist(d, (rpoints + d * j), (qpoints + d * i));
            *(dist + i * r + j) = x;
            *(copy + i * r + j) = x;
        }
    }
    times[0] = omp_get_wtime() - start;


    start = omp_get_wtime();
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < r; ++j) {
            double x = euclidDist(d, (rpoints + d * j), (qpoints + d * i));
            *(dist + i * j) = x;
            *(copy + i * j) = x;
        }
    }
    times[1] = omp_get_wtime() - start;

    start = omp_get_wtime();

    for (int i = 0; i < n; ++i) {
//        mergeSort((dist + i * r),0,  r-1);
        sort(&dist[i * r], r, 0);
//        serialQuickSort(&dist[i*r],0,r-1);

    }
    times[2] = omp_get_wtime() - start;

    start = omp_get_wtime();


    for (int i = 0; i < n; ++i) {
//        parallelMergeSort((copy + i * r), 0, r-1);
        printDoubleArray(&copy[i * r], 10);

        sort(copy + i * r, r, 1);
//        parallelQuickSort(copy+i*r,0,r-1);
        printDoubleArray(&copy[i * r], 10);


    }
    times[3] = omp_get_wtime() - start;
    free(copy);
    free(dist);
    free(rpoints);
    free(qpoints);
    return times;
}