1. Mục tiêu bài 
Đề bài yêu cầu tính tổng các số tự nhiên từ 1 cho tới n. 
Bài toán yêu cầu tình bằng 2 cách:
-Cách 1: tính tuần tự lặp từ 1 tới n rồi cộng lại
-Cách 2: Tiến hành chia thành các luồng riêng tính từng khoảng rồi tính tổng trong khoảng cuối cùng tính tổng cuối lại.

2. Danh sách file
Trong thư mục problem2 này bao gồm 4 file.
-1 file sum_serial.c chứa chương trình tính tổng bằng cách tuần tự.
-1 file sum_multi-thread.c chứ chương trình tính tổng bằng cách tính dựa trên chia ra số luộng rồi cộng lại.
-1 file Makefile có 2 phương thức make all để build và make clean để dọn dẹp
-1 file README.txt mô tả về bài tập.

3. Cách build
Tiến hành biên dịch chương trình với lệnh:

make all

4. Cách chạy
Thực hiện chạy chương trình 
#Chương trình tính tuần tự

./sum_serial <n>

Trong đó n là số muốn tính tổng tới:
Ví dụ: 
    ./sum_serial 1000000

#Chương trình tính đa luồng

./sum_multi-thread <số luồng> <n>

Trong đó, số luồng là số luồng muốn chia ra để tình, n là số muốn tình tổng tới.
Ví dụ:
    ./sum_multi-thread 10 1000000


5. Input / Output
-Chương trình nhận đầu vào input là số tự nhiên n, và số luồng num_thread đối với chương trình sum_multi-thread.c
-Chương trình trả về kết quả tổng tính được và thời gian để thực hiện chạy chương trình đó.
Output đầu ra là <kết quả tổng> Time: <thời gian (s)>


6. Ý tưởng hiện thực
Mô tả ngắn cách giải:
-Bài toán tính tổng từ 1 đến n được thực hiện bằng hai phiên bản để so sánh hiệu năng. 
-Phiên bản thứ nhất (Serial) dùng vòng lặp đơn luồng tính tuần tự.
-Phiên bản thứ hai (Multi-thread) chia đều khoảng giá trị từ 1 đến n cho numThreads luồng khác nhau. Mỗi luồng tính tổng một phân đoạn nhỏ, sau đó luồng chính (main thread) sẽ gộp các tổng phụ lại thành kết quả cuối cùng. 
-Cả hai phiên bản đều được đo thời gian thực thi bằng clock_gettime().

Dùng thread:
-Sử dụng thư viện POSIX Pthread (pthread_create, pthread_join) để tạo và đồng bộ các luồng.
-Cấu trúc Thread_data (struct) được tạo ra để truyền các tham số đầu vào (start_index, end_index) và nhận kết quả đầu ra (sum) cho từng thread độc lập.

Thiết kế:
-Biến lưu trữ sử dụng kiểu long long để tránh tràn số.
-Biến sum được cấp phát trong struct để tránh truy xuất đồng thời biến toàn cục.

7. Ghi chú thêm (nếu có)
Không