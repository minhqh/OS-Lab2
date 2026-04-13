1. Mục tiêu bài
-Sử dụng mmap để ánh xạ một file vào không gian địa chỉ cục bộ.
-Dùng vùng nhớ đã được ánh xạ này để chứng minh việc chia sẻ dữ liệu giữa tiến trình độc lập.

2. Danh sách file
Trong thư mục problem1 này bao gồm 4 file.
-1 file mmap_writer.c:code chính của tiến trình ghi, tạo file, ánh xạ bộ nhớ và ghi tin.
-1 file mmap_reader.c:code chính của tiến trình đọc, mở file đã có, ánh xạ bộ nhớ và đọc tin.
-1 file shared_data.dat: File dữ liệu được tạo tự động khi chạy tiến trình ghi dùng làm nơi lưu trữ trung gian cho mmap.

3. Cách build
Tiến hành biên dịch chương trình với lệnh:

gcc -Wall -o mmap_writer mmap_writer.c
gcc -Wall -o mmap_reader mmap_reader.c


4. Cách chạy
Thực hiện chạy chương trình:
Chạy chương trình ghi để tạo file và vùng nhớ:

./mmap_writer

Sau đó chạy chương trình đọc để đọc dữ liệu chia sẻ

./mmap_reader

5. Input / Output
- Chương trình không nhận input.
- Kết quả đầu ra:
    Bên mmap_writer hiện thị "Đã gửi tin nhắn vào mmap"
    Bên mmap_reader hiện thị nội dung đã đọc từ vùng nhớ chứng tỏ giao tiếp thành công
        "Tinh nang on."

6. Ý tưởng hiện thực
Mô tả ngắn cách giải:
-Sử dụng mô hình Client-Server đơn giản thông qua bộ nhớ chia sẻ. 
-Tiến trình ghi đóng vai trò người cấp phát và ghi dữ liệu.
-Tiến trình đọc đóng vai trò người tiêu thụ dữ liệu.

Dùng mmap:
-Cả 2 đều dùng system call open() để trỏ vào cùng một file vật lý.
-Tiến trình ghi vào bộ nhớ ảo với quyền PROT_READ | PROT_WRITE qua cờ MAP_SHARED dùng hàm sprinf để ghi thẳng vào.
-Tiến trình đọc mở file với quyển O_RDONLY sau đó gọi mmap() với cờ MAP_SHARED để đọc.
-Cả hai tiến trình đều gọi munmap() và close() để giải phóng tài nguyên sau khi chạy.

7. Ghi chú thêm (nếu có)
- Các lưu ý cần biết khi chạy.
Nếu file shared_data.dat chưa tồn tại, việc chạy ./mmap_reader trước sẽ báo lỗi open file. Luôn đảm bảo chạy ./mmap_writer trước.

