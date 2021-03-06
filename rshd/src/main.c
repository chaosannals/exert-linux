#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int setup() {
    // 初始化 socket
    int servfd = socket(AF_INET, SOCK_STREAM, 0);
    if (servfd == -1) {
        return 1;
    }

    // 绑定地址
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(30000);
    if (bind(servfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        return 2;
    }

    // 监听
    if (listen(servfd, 10) == -1) {
        return 3;
    }

    // 接受请求。
    for (;;) {
        int connfd = accept(servfd, 0, 0);
        if (connfd == -1) {
            continue;
        }

    }
    close(servfd);
}

int main() {
    printf("reverse shell\n");
}