#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "utility.h"
#include <omp.h>

int *generateArray(int n) {
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        *(arr + i) = ((double) rand() / RAND_MAX) * 10;
    }
    return arr;
}

double *generateDoubleArray(int n) {
    double *arr = malloc(n * sizeof(double));
    for (int i = 0; i < n; ++i) {
        *(arr + i) = ((double) rand() / RAND_MAX) * 10;
    }
    return arr;
}

double colStd(double *arr, double avg, int index, int rowlen, int collen) {
    double var = 0;
    for (int i = index; i < rowlen*collen; i+=rowlen) {
        var += pow(*(arr+i) - avg, 2);
    }
    return sqrt(var);
}

double avgCol(double*arr, int col, int size){
    double avg = 0;
    for(int i = 0; i< size*size; i+=size) avg += arr[i];
    avg /= (double)size;
    return avg;
}


void writeToFile() {
    FILE *fptr = fopen("referencepoints.csv", "w");
    for (int d = 32; d <= 512; d *= 2) {
        for (int r = 32; r <= 512; r *= 2) {
            for (int i = 0; i < r * d; ++i) {
                if (i == r * d - 1) {
                    fprintf(fptr, "%d\n", rand());
                } else {
                    fprintf(fptr, "%d,", rand());
                }
            }
        }
    }
    fclose(fptr);
    fptr = fopen("querypoints.csv", "w");
    for (int d = 32; d <= 512; d *= 2) {
        for (int n = 400; n <= 1600; n += 400) {
            for (int i = 0; i < n * d; ++i) {
                if (i == n * d - 1) {
                    fprintf(fptr, "%d\n", rand());
                } else {
                    fprintf(fptr, "%d,", rand());
                }
            }
        }
    }

    fclose(fptr);

}

double euclidDist(int d, double *p1, double *p2) {
    double dist = 0;

    for (int i = 0; i < d; ++i) {
        dist += pow(*(p1 + i) - *(p2 + i), 2);
    }
    return sqrt(dist);
}

void printArray(int A[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d, ", A[i]);
    printf("\n");
}

void printDoubleArray(double *A, int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%f, ", *(A + i));
    printf("\n");
}

int *copyIntArr(int *arr, int size) {
    int *copy = malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        *(copy + i) = *(arr + i);
    }
    return copy;
}

double *copyDoubleArr(double *arr, int size) {
    double *copy = malloc(size * sizeof(double));
    for (int i = 0; i < size; ++i) {
        *(copy + i) = *(arr + i);
    }
    return copy;
}