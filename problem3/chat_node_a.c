#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 0x1234
#define MAX_TEXT 256

// Định nghĩa cấu trúc tin nhắn
struct msgbuf {
    long mtype;
    char mtext[MAX_TEXT];
};

int msgid; // ID của hàng đợi dùng chung

// Thread 1: Chuyên gửi tin nhắn
void* sender(void* arg) {
    struct msgbuf buf;
    buf.mtype = 1; // Node A luôn gửi tin nhắn với nhãn loại 1

    while (1) {
        fgets(buf.mtext, MAX_TEXT, stdin);
        
        // Xóa ký tự newline ('\n') ở cuối chuỗi do fgets sinh ra
        buf.mtext[strcspn(buf.mtext, "\n")] = 0; 
        
        // Gửi vào queue
        if (msgsnd(msgid, &buf, sizeof(buf.mtext), 0) == -1) {
            perror("msgsnd failed");
        }

        // Kịch bản thoát
        if (strcmp(buf.mtext, "end") == 0) {
            printf("[System]: Bạn đã rời khỏi đoạn chat.\n");
            exit(0);
        }
    }
    return NULL;
}

// Thread 2: Chuyên nhận tin nhắn
void* receiver(void* arg) {
    struct msgbuf buf;

    while (1) {
        // Node A chỉ đọc các tin nhắn có nhãn loại 2 (do Node B gửi)
        if (msgrcv(msgid, &buf, sizeof(buf.mtext), 2, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }

        // Kịch bản thoát khi người kia gõ "end"
        if (strcmp(buf.mtext, "end") == 0) {
            printf("[System]: Đối tác đã rời khỏi đoạn chat. Nhấn Enter để thoát.\n");
            exit(0); 
        }

        printf("\n[Node B]: %s\n", buf.mtext);
    }
    return NULL;
}

int main() {
    // Khởi tạo Message Queue chung (nếu chưa có thì tạo mới)
    msgid = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    printf("=== CHAT NODE A ĐÃ SẴN SÀNG ===\n");
    printf("Nhập tin nhắn và nhấn Enter để gửi. Gõ 'end' để kết thúc.\n");

    pthread_t send_tid, recv_tid;

    // Khởi tạo 2 luồng độc lập
    pthread_create(&send_tid, NULL, sender, NULL);
    pthread_create(&recv_tid, NULL, receiver, NULL);

    // Chờ các luồng hoàn tất (thực tế sẽ bị ngắt bởi exit() bên trong luồng)
    pthread_join(send_tid, NULL);
    pthread_join(recv_tid, NULL);

    // Xóa Queue khỏi bộ nhớ sau khi dùng xong
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}