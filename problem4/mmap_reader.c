#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define FILE_SIZE 4096
#define FILE_NAME "shared_data.dat"

int main() {
    // 1. Mở file đã được writer tạo ra (chỉ cần quyền Đọc)
    int fd = open(FILE_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Lỗi open file (Hãy chắc chắn bạn đã chạy mmap_writer trước)");
        return 1;
    }

    // 2. Ánh xạ file vào bộ nhớ
    // Lần này ta chỉ cần cờ PROT_READ vì chỉ đọc dữ liệu 
    char *map = mmap(NULL, FILE_SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("Lỗi mmap");
        close(fd);
        return 1;
    }

    // 3. Đọc dữ liệu từ vùng nhớ ánh xạ và in ra màn hình
    printf("Reader: Nội dung đọc được từ vùng mmap là:\n");
    printf(">> \"%s\"\n", map);

    // 4. Dọn dẹp
    if (munmap(map, FILE_SIZE) == -1) {
        perror("Lỗi munmap");
    }
    close(fd);
    
    return 0;
}