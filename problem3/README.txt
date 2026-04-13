1. Mục tiêu bài 
Đề bài yêu cầu hiện thực chương trình đoạn tin nhắn giữa 2 người nhưng sử dụng trong 2 luồng của chương trình.
Mỗi người dùng đều có thể gửi và nhận tin của đối phương.

2. Danh sách file
Trong thư mục problem1 này bao gồm 3 file.
-1 file chat_node_a.c chứa chương trình bao gồm hàm gửi hàm nhận và luồng,
-1 file chat_node_b.c chứa chương trình bao gồm hàm gửi hàm nhận và luồng,
-1 file README.txt mô tả về bài tập

3. Cách build
Tiến hành biên dịch chương trình với lệnh:

gcc -Wall -pthread -o chat_node_a chat_node_a.c
gcc -Wall -pthread -o chat_node_b chat_node_b.c

4. Cách chạy
Thực hiện chạy chương trình:
-Đầu tiên mở thêm một Terminal nữa.
Terminal 1 tiến hành chạy:

./chat_node_a

Để nguyên Terminal 1 qua Terminal 2 chạy :

./chat_node_b

5. Input / Output
- Chương trình nhận input là các câu văn bản được gửi từ cả 2 phía.
- Kết quả đầu ra mong đợi là các câu văn bản mà đối phương đã gửi.


6. Ý tưởng hiện thực
Mô tả ngắn cách giải:
-Hai chương trình Node A và Node B chạy tin nhắn trực tiếp bằng cách tận dụng Message Queue.
-Khác với 1 chiều chỉ có một người gửi thì đây có cả gửi lẫn nhận vì mỗi node đều có hàm sender và reciver nên đều nhận và gửi.

Dùng IPC(Message Queue):
Sử dụng msgget, msgsnd, msgrcv, msgctl để tạo hàng đợi tin nhắn chung dựa trên một MSG_KEY quy ước trước.
Sử dụng pthread_create để tách biệt khi nhắn và nhận chạy song song.

Thiết kế:
Để tránh tình trạng không xác định được tin của mình, tức nhắn gì gửi nấy cho chính mình.
Tiến hành gán cờ mtype. Node A luôn gửi mtype = 1 và chỉ nhận mtype = 2. Ngược lại cho B.

7. Ghi chú thêm (nếu có)
Không

