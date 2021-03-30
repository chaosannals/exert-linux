#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define P_COUNT 3

// 子进程主函数。
int submain()
{
    sleep(6);
    printf("submain (%d) do same thing.\n", getpid());
    execlp("ps", "ps", "au", NULL); // 会把整个环境切换到指定的进程。导致之后的代码无效。
    return 0;
}

// 父进程主函数。
int main()
{
    int mpid = getpid(); // 主进程 ID
    printf("main process. %d \n", mpid);

    int pids[P_COUNT];

    for (int i = 0; i < P_COUNT; ++i)
    {
        int pid = fork(); // 岔开后 子进程 pid = 0；父进程 pid = 子进程ID；

        switch (pid)
        {
        case -1:
            perror("fork failed\n");
            break;
        case 0:
            printf("subprocess (%d) %d %d\n", i, pid, getpid());
            // 这个时候子进程应该离开父进程的生成分岔循环，不然子进程也会fork出孙进程。
            return submain();
        default:
            printf("process (%d) %d %d\n", i, pid, getpid());
            pids[i] = pid;
            break;
        }
    }

    int fc = 0;
    int stat = 0;
    while (fc < P_COUNT)
    {
        for (int j = 0; j < P_COUNT; ++j)
        {
            int pid = pids[j];
            // waitpid 回收僵尸子进程。
            if (pid != 0 && waitpid(pid, &stat, WNOHANG)) {
                printf("final %d\n", pid);
                pids[j] = 0;
                ++fc;
            }
        }
    }

    printf("final all.\n");

    return 0;
}