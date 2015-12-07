//
//  main.c
//  omp
//
//  Created by Jenny on 13.09.15.
//  Copyright (c) 2015 com.mipt. All rights reserved.
//

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#define N 1000000000
#define MAXN 10000

long long a[N];

int main (int argc, char *argv[]) {
    long i;
    double before, after;
    long long sum = 0LL;
    for (i = 0; i < N; i++) {
        a[i] = rand()%MAXN;
    }

    printf("iki\n");
    before = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < N; i++)
        sum += a[i];
    after = omp_get_wtime();
    
    printf("sum is %lld, time %lf\n", sum, after - before);

    return 0;
}
