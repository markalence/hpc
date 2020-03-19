#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include "quicksort.h"
#include "mergesort.h"
#include "utility.h"
#include <math.h>
#include "bitonicsort.h"
#include "testrun.h"

#define D_INIT 8
#define D_FIN 8
#define N_INIT 4
#define N_FIN 4
#define R_INIT 5000
#define R_FIN 100000
#define N_ITER 1

int main() {
    srand(time(NULL));
    FILE* ptr = fopen("bitonic.csv","w");

//    int n = pow(2,23);
//    double *e = generateDoubleArray(n);
//    double *c = copyDoubleArr(e, n);
//    double start;
//    start = omp_get_wtime();
//    parallelQuickSort(e, 0, n-1);
//    printf("%f\n", omp_get_wtime() - start);
//
//    start = omp_get_wtime();
//    serialQuickSort(c, 0, n-1);
//    printf("%f\n", omp_get_wtime() - start);


    for (int d = D_INIT; d <= D_FIN; d *= 2) {
        for (int n = N_INIT; n <= N_FIN; n *= 2) {
            for (int r = R_INIT; r <= R_FIN; r += 5000) {
                printf("%d\n",r);

                double times[N_ITER][4];
                double avgs[4] = {0};
                for(int i = 0; i < N_ITER; ++i){
                    double *e = testrun(d,r,n);
                    for(int j = 0; j < 4; ++j){
                        times[i][j] = e[j];
                        avgs[j] += e[j]/N_ITER;
                    }
                }
                double var[4];
                for(int k = 0; k < 4; ++k){
                    var[k] = colStd(&times[0][0], avgs[k], k, 4, N_ITER);
                }
                fprintf(ptr, "%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f\n",
                        d,r,n,avgs[0],var[0],avgs[1],var[1],avgs[2],var[2],avgs[3],var[3]);
            }
        }
    }

    return 0;
}
