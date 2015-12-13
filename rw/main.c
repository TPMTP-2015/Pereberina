#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define READERS 16
#define WRITERS 64
#define ITERATIONS 5
int a;
int semid;
pthread_mutex_t mutex;
pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;


void *reader(void *prm) {
    int i, r;
    struct sembuf done = { 0, -1, 0};
    
    for(i = 0; i < ITERATIONS; i++) {
        pthread_rwlock_rdlock(&lock);
        
        r = a;
        printf("Read a: %d\n", a);
                    // semop(semid, &done, 1);
        pthread_rwlock_unlock(&lock);
    }
    
    return NULL;
}

void *writer(void *prm) {
    int i;
    struct sembuf wait = { 0, -READERS, 0};
    struct sembuf set_queue = { 0, READERS, 0 };
    
    for (i = 0; i < ITERATIONS; i++) {
        pthread_rwlock_wrlock(&lock);
        
                        //semop(semid, &wait, 1);
        
        a++;
        printf("Write a: %d\n", a);
       
                       // semop(semid, &set_queue, 1);
        
        pthread_rwlock_unlock(&lock);
    }
    
    return NULL;
}

int main(int argc, const char * argv[]) {
    pthread_t rd[READERS];
    pthread_t wr[WRITERS];
    int i;
    key_t key;
    union semun arg;
    struct timeval before, after;
    
    key = ftok(".", 1);
    
    semid = semget(key, 1, 0666 | IPC_CREAT);
    arg.val = READERS;
    semctl(semid, 0, SETVAL, arg.val);
   
    pthread_mutex_init(&mutex, NULL);
    
    gettimeofday(&before, NULL);
    for(i = 0; i < READERS; i++) {
        pthread_create(&(rd[i]), NULL, reader, NULL);
    }
  
    printf("Readers created\n");
    
    for(i = 0; i < WRITERS; i++) {
        pthread_create(&(wr[i]), NULL, writer, NULL);
    }
    printf("Writers created\n");
    for(i = 0; i < READERS; i++) {
        pthread_join(rd[i], NULL);
    }
    for(i = 0; i < WRITERS; i++) {
        pthread_join(wr[i], NULL);
    }
    gettimeofday(&after, NULL);
    
    pthread_mutex_destroy(&mutex);
    pthread_rwlock_destroy(&lock);
    printf("%ld\n", ((1000000*after.tv_sec + after.tv_usec) - (1000000*before.tv_sec + before.tv_usec)));
    
    return 0;
}