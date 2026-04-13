#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct{
    int start_index;
    int end_index;
    long long sum;
} Thread_data;

void* compute_sum(void* arg) {
    Thread_data* data = (Thread_data*)arg;
    data->sum = 0;

    for (int i = data->start_index; i <= data->end_index; i++) {
        data->sum += i;
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Sử dụng: %s <numThreads> <n>\n", argv[0]);
        return 1;
    }
    int numThreads = atoi(argv[1]);
    int n = atoi(argv[2]);

    pthread_t threads[numThreads];
    Thread_data data[numThreads];

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < numThreads; i++){
        data[i].start_index = i *(n/numThreads) + 1;
        if (i == numThreads - 1)
            data[i].end_index = n; 
        else
            data[i].end_index = (i + 1)*(n/numThreads);
        
        pthread_create(&threads[i],NULL,compute_sum, &data[i]);
    }
    
    long long total = 0;
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
        total += data[i].sum;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    printf("%lld Time: %f giay \n", total,time_taken);

    return 0;
}