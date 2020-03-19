
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

double* a;
const int ASCENDING = 1;
const int DESCENDING = 0;
int THRESHOLD;
void compare(int i, int j, int dir)
{
    if (dir==(a[i]>a[j]))
    {
        double h=a[i];
        a[i]=a[j];
        a[j]=h;
    }
}

void bitonicMerge(int lo, int cnt, int dir)
{
    if (cnt>1)
    {
        int k=cnt/2;
        int i;
        for (i=lo; i<lo+k; i++)
            compare(i, i+k, dir);
        bitonicMerge(lo, k, dir);
        bitonicMerge(lo+k, k, dir);
    }
}


void bitonicSort(int lo, int cnt, int dir, int p)
{
    if (cnt>1)
    {
        int k=cnt/2;
        if(!p || k < THRESHOLD) {
            p=0;
            bitonicSort(lo, k, ASCENDING,p);
            bitonicSort(lo + k, k, DESCENDING,p);
            bitonicMerge(lo, cnt, dir);
        }
        else{

#pragma omp parallel
#pragma omp single
            {
#pragma omp task
                {
                    bitonicSort(lo, k, ASCENDING,p);

                }
#pragma omp task
                {
                    bitonicSort(lo + k, k, DESCENDING,p);

                }
            }
        }
        bitonicMerge(lo, cnt, dir);

    }
}


void sort(double *arr, int N, int p)
{
    omp_set_nested(1);
    a = arr;
    THRESHOLD = N/16;
    bitonicSort(0, N, ASCENDING,p);
}