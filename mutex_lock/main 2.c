//
//  main.c
//  Lock
//
//  Created by Jenny on 12.10.15.
//  Copyright © 2015 com.mipt. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#define THREADS 16
#define WORK 1000000
// 4 23.566610
// 10 52.299386
pthread_rwlock_t rwlock;
double a = 0;

void *thread_func(void) {
    int i;
    
    for (i = 0; i < WORK; i++) {
        pthread_rwlock_wrlock(&rwlock);
        a++;
        
        pthread_rwlock_unlock(&rwlock);
    }
 
    return NULL;
}

int main(int argc, const char * argv[]) {
    long j;
    pthread_t thr[THREADS];
    
    struct timeval before, after;
    
    gettimeofday(&before, NULL);
    pthread_rwlock_init(&rwlock, NULL);
    for (j = 0; j < THREADS; j++) {
        if (pthread_create(&thr[j], NULL, (void *)thread_func, NULL) != 0) {
            perror("Creating failed");
            return EXIT_FAILURE;
        }
    }
    
    for (j = 0; j < THREADS; j++) {
        pthread_join(thr[j], NULL);
    }
    
    gettimeofday(&after, NULL);
    
    printf("%ld\n", ((1000000*after.tv_sec + after.tv_usec) - (1000000*before.tv_sec + before.tv_usec)));
    return 0;
}
