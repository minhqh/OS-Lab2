#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h> 
#include <string.h>

#define FILE_SIZE 4096 
#define FILE_NAME "shared_data.dat"

int main() {
    int fd = open(FILE_NAME, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Lỗi open file");
        return 1;
    }

    if (ftruncate(fd, FILE_SIZE) == -1) {
        perror("Lỗi ftruncate");
        close(fd);
        return 1;
    }

    char *map = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("Lỗi mmap");
        close(fd);
        return 1;
    }

    const char *message = "Tinh nang on.";
    sprintf(map, "%s", message);
    printf("Writer: Đã ghi tin nhắn vào vùng mmap thành công!\n");

    if (munmap(map, FILE_SIZE) == -1) {
        perror("Lỗi munmap");
    }
    close(fd);
    
    return 0;
}