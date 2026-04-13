#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h> // Thư viện bắt buộc cho mmap [cite: 423]
#include <string.h>

#define FILE_SIZE 4096 // Kích thước mapping (thường là bội số của 1 page - 4KB)
#define FILE_NAME "shared_data.dat"

int main() {
    // 1. Mở hoặc tạo file với quyền Đọc/Ghi
    int fd = open(FILE_NAME, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Lỗi open file");
        return 1;
    }

    // 2. Cắt/mở rộng file đạt đúng kích thước mong muốn
    if (ftruncate(fd, FILE_SIZE) == -1) {
        perror("Lỗi ftruncate");
        close(fd);
        return 1;
    }

    // 3. Ánh xạ file vào không gian bộ nhớ ảo [cite: 426]
    // Dùng PROT_READ | PROT_WRITE để cho phép cả đọc và ghi 
    // Dùng MAP_SHARED để tiến trình khác có thể nhìn thấy sự thay đổi 
    char *map = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("Lỗi mmap");
        close(fd);
        return 1;
    }

    // 4. Ghi dữ liệu trực tiếp vào con trỏ bộ nhớ (thay vì dùng write() lên file)
    const char *message = "Hello from Writer! Tinh nang Memory Mapping hoat dong tot.";
    sprintf(map, "%s", message);
    printf("Writer: Đã ghi tin nhắn vào vùng mmap thành công!\n");

    // 5. Dọn dẹp
    if (munmap(map, FILE_SIZE) == -1) {
        perror("Lỗi munmap");
    }
    close(fd);
    
    return 0;
}