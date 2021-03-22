#include <stdio.h>
#include <unistd.h>

// 子进程主函数。
int submain()
{
    printf("submain (%d) do same thing.\n", getpid());
    return 0;
}

// 父进程主函数。
int main()
{
    int mpid = getpid(); // 主进程 ID
    printf("main process. %d \n", mpid);

    for (int i = 0; i < 3; ++i)
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
            break;
        }
    }

    return 0;
}