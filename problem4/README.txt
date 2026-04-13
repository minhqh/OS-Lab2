gcc -Wall -o mmap_writer mmap_writer.c
gcc -Wall -o mmap_reader mmap_reader.c

# Bước 1: Chạy tiến trình Writer trước để tạo file và ghi dữ liệu
./mmap_writer

# Bước 2: Chạy tiến trình Reader để đọc vùng nhớ được chia sẻ
./mmap_reader