#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char* argv[]){
    if (argc != 2) {
        printf("Sử dụng: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        printf("n phai > 0\n");
        return 1;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    printf("%lld Time: %f giay \n", sum,time_taken);
    return 0;
}