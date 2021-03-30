#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int BUFFER_SIZE = 1024;
char host_ip[100] = "127.0.0.1";
char host_port[5] = "22222";

int main(int argc, char *argv[])
{
    printf("reverse shell client %s\n", argv[0]);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket init failed.");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(host_port));
    server_addr.sin_addr.s_addr = inet_addr(host_ip);
    bzero(&server_addr.sin_zero, sizeof(server_addr.sin_zero));
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) == -1)
    {
        perror("connect failed.");
        return 2;
    }

    char buffer[BUFFER_SIZE];
    for (;;)
    {
        bzero(buffer, BUFFER_SIZE);
        printf("\nbegin receive\n");
        int rn = recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (rn == -1)
        {
            perror("rece failed.");
            return 3;
        }
        else if (rn > 0)
        {
            buffer[rn] = '\0';
            printf("received: %s\n", buffer);
            printf("send:");
            char msg[100];
            scanf("%s", msg);
            int len = strlen(msg);
            int sn = send(sockfd, msg, len, 0);
            if (sn == -1)
            {
                perror("send error");
            }
        }
        else
        {
            printf("socket end.\n");
            break;
        }
    }
    close(sockfd);
    return 0;
}