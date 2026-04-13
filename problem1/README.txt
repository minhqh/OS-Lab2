1. Mục tiêu bài 
Đề bài yêu cầu đọc vào 2 file bằng 2 tiến trình con được tạo ra. 
Với mục tiêu là mỗi tiến trình con tiến hành tính trung bình trong mỗi file đó.

2. Danh sách file
Trong thư mục problem1 này bao gồm 1 folder, 2 file.
-Folder movie_100k-split chứa 2 file movie_100k_1.txt và movie_100k_2.txt lần lượt chứa đánh giá của người xem về phim
-1 file main.c để hiện thực chương trình và đây là source code chính
-1 file là README.txt để mô tả về bài tập.

3. Cách build
Tiến hành biên dịch chương trình với lệnh:

gcc -Wall -o main main.c

4. Cách chạy
Thực hiện chạy chương trình 

./main

5. Input / Output
- Chương trình nhận input là 2 file movie_100k_1.txt và movie_100k_2.txt nằm trong folder movie_100k-split
- Kết quả đầu ra mong đợi là 1 output được in ra bao gồm 
<id_phim> <điểm đánh giá tb> <Só lượng đánh giá>
VD:
1  3.8783  452
2  3.2061  131 
...
1682 3.0000 1


6. Ý tưởng hiện thực
Mô tả ngắn cách giải:
-Tiên hành tạo ra một vùng nhớ chia sẻ để tính và lưu tổng điểm rating từng phim.
-Tạo 2 tiến trình con, mỗi tiến trình con chịu trách nhiệm đọc và tính sau đó cộng dồn kết quả vào vùng nhớ chung.
-Cuối cùng tiến trình cha chờ 2 tiến trình con, tổng hợp và tính trung bình.

Dùng process:
Sử dụng lệnh fork() để tạo 2 tiến trình con xử lý đồng thời 2 file nhằm tăng tốc độ.
Tiến trình cha dùng waitpid() để đồng bộ với các tiến trình con.

Thiết kế:
Để tránh race condition, chương trình tách ra rằng mỗi tiến trình chỉ ghi vào mảng riêng của tiến trình đó 
Tiến trình cha chỉ gộp ở bước cuối

7. Ghi chú thêm (nếu có)
Không