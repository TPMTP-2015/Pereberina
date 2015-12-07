//
//  main.c
//  pthreads
//
//  Created by Jenny on 07.09.15.
//  Copyright (c) 2015 com.mipt. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#define N 1000000000
#define MAXN 10000

long long a[N];

struct Data {
    long left;
    long right;
    long long sum;
};

void *thread_func(void *data) {
    long i;
    long right = ((struct Data *)data)->right;
    long long sum = 0LL;
    
    for (i = ((struct Data *)data)->left; i < right; i++) {
        sum += a[i];
    }
    
    ((struct Data *)data)->sum = sum;
    return NULL;
}

int main(int argc, const char * argv[]) {
    clock_t start, stop;
    long n;
    long j;
    long long sum = 0LL;
    pthread_t *thr;
    if (!argv[1]) {
        perror("Too few arguments");
        return EXIT_FAILURE;
    }
    
    n = atoi(argv[1]);
    thr = (pthread_t *)malloc(n*sizeof(pthread_t));
    struct Data *data;
    data = (struct Data *)malloc(n*sizeof(struct Data));
    for (j = 0; j < N; j++) {
        a[j] = rand()%MAXN;
        //sum += a[j];
    }
    long count = (double)N/n;
    //printf("sum is %lld %ld \n", sum, n);
    start = clock();
    for (j = 0; j < n; j++) {
        data[j].left = j*count;
        data[j].right = N;
        if (j != n - 1)
            data[j].right = data[j].left + count;
        
        if (pthread_create(&thr[j], NULL, thread_func, &data[j]) != 0) {
            perror("Creating failed");
            return EXIT_FAILURE;
        }
    }
    //sum = 0;
    for (j = 0; j < n; j++) {
        pthread_join(thr[j], NULL);
        sum += data[j].sum;
    }
    stop = clock();
    
    printf("sum is %lld, time is %f  \n", sum, ( double ) ( stop - start ) / CLOCKS_PER_SEC);
    free(thr);
    free(data);
    return 0;
}
