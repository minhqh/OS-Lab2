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

struct msgbuf {
    long mtype;
    char mtext[MAX_TEXT];
};

int msgid; // ID chung

void* sender(void* arg) {
    struct msgbuf buf;
    buf.mtype = 1; 
    while (1) {
        fgets(buf.mtext, MAX_TEXT, stdin);
        
        // Xóa ký tự newline ('\n') ở cuối chuỗi do fgets sinh ra
        buf.mtext[strcspn(buf.mtext, "\n")] = 0; 
        
        if (msgsnd(msgid, &buf, sizeof(buf.mtext), 0) == -1) {
            perror("msgsnd failed");
        }

        if (strcmp(buf.mtext, "end") == 0) {
            printf("Bạn đã thoát khỏi đoạn chat.\n");
            exit(0);
        }
    }
    return NULL;
}

void* receiver(void* arg) {
    struct msgbuf buf;

    while (1) {
        if (msgrcv(msgid, &buf, sizeof(buf.mtext), 2, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }

        if (strcmp(buf.mtext, "end") == 0) {
            printf("Sys: Đối phương đã thoát khỏi đoạn chat.\n");
            printf("Nhấn Enter để thoát.\n");
            exit(0); 
        }

        printf("\n[Node B]: %s\n", buf.mtext);
    }
    return NULL;
}

int main() {
    msgid = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    printf("===> CHAT NODE A \n");
    printf("Nhập tin nhắn và nhấn Enter để gửi. Gõ 'end' để kết thúc.\n");

    pthread_t send_tid, recv_tid;

    pthread_create(&send_tid, NULL, sender, NULL);
    pthread_create(&recv_tid, NULL, receiver, NULL);

    pthread_join(send_tid, NULL);
    pthread_join(recv_tid, NULL);

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}