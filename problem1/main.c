#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h> 

#define NUM_MOVIES 1682

typedef struct{
    long long sum;
    int count;
} MovieRate;

typedef struct{
    MovieRate child1_data[NUM_MOVIES+1];
    MovieRate child2_data[NUM_MOVIES+1];   
} SharedMemory;

void process_file(const char* filename, MovieRate* data){
    FILE *file = fopen(filename,"r"); 
    if(!file){
        printf("Lỗi: Không mở được file %s\n" , filename);
        exit(1);
    }

    int user_id, movie_id, rate, time;

    while(fscanf(file , "%d\t%d\t%d\t%d" , &user_id, &movie_id, &rate, &time) == 4){
        if (movie_id >= 1 && movie_id <= NUM_MOVIES) {
            data[movie_id].sum += rate;
            data[movie_id].count++;
        }
    }

    fclose(file);
}

int main(int argc, char * argv[])
{
    int shmid = shmget(IPC_PRIVATE, sizeof(SharedMemory), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("Lỗi khi shmget");
        return 1;
    }

    SharedMemory *shared = (SharedMemory *)shmat(shmid, NULL, 0);
    if (shared == (SharedMemory *)-1) {
        perror("Lỗi khi shmat");
        return 1;
    }

    for (int i = 1; i <= NUM_MOVIES; i++) {
        shared->child1_data[i].sum = 0;
        shared->child1_data[i].count = 0;
        shared->child2_data[i].sum = 0;
        shared->child2_data[i].count = 0;
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("Lỗi fork Child 1");
        exit(1);
    } else if (pid1 == 0) {
        // Child 1
        process_file("movie-100k-split/movie-100k_1.txt", shared->child1_data);
        shmdt(shared);
        exit(0); 
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("Lỗi fork Child 2");
        exit(1);
    } else if (pid2 == 0) {
        // Child 2
        process_file("movie-100k-split/movie-100k_2.txt", shared->child2_data);
        shmdt(shared); 
        exit(0); 
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("MovieID\tAverage Rating\tTotal Votes\n");
    printf("-------------------------------------------\n");
    for (int i = 1; i <= NUM_MOVIES; i++) {
        long long total_sum = shared->child1_data[i].sum + shared->child2_data[i].sum;
        int total_count = shared->child1_data[i].count + shared->child2_data[i].count;
        
        if (total_count > 0) {
            double avg = (double)total_sum / total_count;
            printf("%d\t%.4f\t\t%d\n", i, avg, total_count);
        }
    }

    shmdt(shared);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}