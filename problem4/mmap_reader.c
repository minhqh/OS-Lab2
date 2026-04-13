#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define FILE_SIZE 4096
#define FILE_NAME "shared_data.dat"

int main() {
    int fd = open(FILE_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Lỗi open file (Hãy chắc chắn bạn đã chạy mmap_writer trước)");
        return 1;
    }

    char *map = mmap(NULL, FILE_SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("Lỗi mmap");
        close(fd);
        return 1;
    }

    printf("Reader: Nội dung đọc được từ vùng mmap là:\n");
    printf(">> \"%s\"\n", map);

    if (munmap(map, FILE_SIZE) == -1) {
        perror("Lỗi munmap");
    }
    close(fd);
    
    return 0;
}