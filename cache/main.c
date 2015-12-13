//
//  main.c
//  cache
//
//  Created by Jenny on 13.12.15.
//  Copyright © 2015 com.mipt. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#define OFFSET (16777216/sizeof(int))
#define N 32
#define ELEMENTS (SIZE/N)
#define SIZE (OFFSET*N)

volatile int a[SIZE];

int main(int argc, const char * argv[]) {
    clock_t start, stop;
    int i, j;
    int n;
    
    for (j = 0; j < N - 1; j++) {
        for (i = j*OFFSET; (i < (j + 1)*OFFSET && i < SIZE); i++) {
            a[i] = (j + 1)*OFFSET + i%OFFSET;
            n = a[i];
        }
    }
    
    start = clock();
    for (j = 0; j < ELEMENTS; j++) {
        i = j;
        while(a[i] != 0) {
            i = a[i];
        }
    }
    stop = clock();
    printf("time is %ld  \n", ( stop - start ));
    return 0;
}
