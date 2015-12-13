//
//  main.c
//  mutex_lock
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
// 4 28.240421
// 10 63.336990
pthread_mutex_t mutex;
double a;

void *thread_func(void) {
    int j;
    
    for (j = 0; j < WORK; j++) {
        pthread_mutex_lock(&mutex);
        a++;
     
        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}

int main(int argc, const char * argv[]) {
    long j;
    pthread_t thr[THREADS];
    
    struct timeval before, after;
    
    gettimeofday(&before, NULL);
    pthread_mutex_init(&mutex, NULL);
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
