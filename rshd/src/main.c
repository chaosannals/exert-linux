#include <stdio.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>

int subrun(int fd)
{
    int pid = getpid();
    char buffer[1024];
    for (;;)
    {
        // 发送。
        bzero(buffer, 1024);
        sprintf(buffer, "\npid: %d\n", pid);
        int sc = send(fd, buffer, strlen(buffer), 0);
        if (sc <= 0)
        {
            printf("[%d]send end.\n", pid);
            break;
        }
        printf("[%d]s(%d)\n", pid, sc);

        // 接收。
        bzero(buffer, 1024);
        int rc = recv(fd, buffer, 1024, 0);
        if (rc <= 0)
        {
            printf("[%d]recv end.\n", pid);
            break;
        }
        printf("[%d]r(%d): %s\n", pid, rc, buffer);
    }
    close(fd);
    printf("[%d]close fd\n", pid);
    return 0;
}

int setup()
{
    // 初始化 socket
    int servfd = socket(AF_INET, SOCK_STREAM, 0);
    if (servfd == -1)
    {
        return 1;
    }

    // 绑定地址
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(22222);
    if (bind(servfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        perror("bind failed.");
        return 2;
    }

    // 监听
    if (listen(servfd, 10) == -1)
    {
        perror("listen failed.");
        return 3;
    }

    // 接受请求。
    int pidc = 0;
    int pids[100];
    bzero(pids, sizeof(pids));
    for (;;)
    {
        // 回收子进程。
        int final = 0;
        for (int i = 0; i < 100; ++i)
        {
            if (pids[i] != 0)
            {
                int stat = 0;
                if (waitpid(pids[i], &stat, WNOHANG))
                {
                    printf("[%d]wait: %d\n", getpid(), pids[i]);
                    pids[i] = 0;
                    --pidc;
                }
            }
        }

        // 只接受 100 条链接，超过后之后回收了老的才会接受新的连接。
        printf("[%d]pidc: %d\n", getpid(), pidc);
        if (pidc > 100)
        {
            printf("[%d]full\n", getpid());
            sleep(1);
            continue;
        }

        // 接受请求。
        int connfd = accept(servfd, 0, 0);
        if (connfd == -1)
        {
            printf("[%d]accept faild.", getpid());
            continue;
        }

        pid_t pid = fork();

        // 子进程进入处理。
        if (pid == 0)
        {
            int code = subrun(connfd);
            close(connfd);
            return code;
        }

        // 主进程注册 PID
        for (int i = 0; i < 100; ++i)
        {
            if (pids[i] == 0)
            {
                pids[i] = pid;
                ++pidc;
                printf("[%d]reg: %d count: %d\n", getpid(), pid, pidc);
                break;
            }
        }
    }
    close(servfd);
    return 0;
}

int main()
{
    printf("[%d]reverse shell\n", getpid());
    int code = setup();
    printf("[%d]end: %d\n", getpid(), code);
    return code;
}