//
//  main.cpp
//  tbb
//
//  Created by Jenny on 14.09.15.
//  Copyright (c) 2015 com.mipt. All rights reserved.
//

#include <iostream>
#include "tbb/tick_count.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_reduce.h"
#include "tbb/task_scheduler_init.h"
#define N 1000000000
#define MAXN 10000
#define THREADS_NUM 1

using namespace tbb;

class CalculationTask
{
    long long *myArray;
public:
    mutable long long sum;
    void operator()(tbb::blocked_range<int> &r) const
    {
        for (int i = r.begin(); i != r.end(); i++)
            sum += myArray[i];
    }
    
    CalculationTask(CalculationTask &t, tbb::split) : myArray(t.myArray), sum(0){ }
    
    void join(CalculationTask &t)
    {
        sum += t.sum;
    }
    
    CalculationTask (long long *a) : myArray(a), sum(0) { }
};


int main()
{
    tbb::task_scheduler_init init(THREADS_NUM);
    long long *myArray = new long long[N];
    //long long real = 0;
    for (int i = 0; i < N; i++) {
        myArray[i] = rand()%MAXN;
        //real += myArray[i];
    }
    CalculationTask sum(myArray);
    tick_count t0 = tick_count::now();
    tbb::parallel_reduce(tbb::blocked_range<int>(0, N, 1000), sum);
    double time = (tick_count::now() - t0).seconds();
    printf("sum is %lld time %lf \n", sum.sum, time);
    
    delete[] myArray;
    
    return 0;
}
