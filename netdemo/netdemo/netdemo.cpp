// netdemo.cpp: 定义应用程序的入口点。
//

#include "netdemo.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{
	cout << "pipe" << endl;
	
	int fd[2];
	int result = pipe(fd);
	if (-1 == result) {
		cout << "pipe make failed." << endl;
		return -1;
	}

	pid_t pid = fork();
	int write_fd = fd[1];
	int read_fd = fd[0];
	if (-1 == pid) {
		cout << "fork failed." << endl;
		return -1;
	}

	int counter = 0;
	char readbuffer[80];
	if (0 == pid) {
		cout << "cw: " << write_fd << " cr: " << read_fd << endl;

		close(read_fd);
		char child_content[] = "child content";
		int r = write(write_fd, child_content, sizeof(child_content));
		cout << "child write: " << r << endl;
	}
	else {
		cout << "pw: " << write_fd << " pr: " << read_fd << endl;

		close(write_fd);
		int n = read(read_fd, readbuffer, sizeof(readbuffer));
		cout << "parent read: " << n << " " << readbuffer << endl;
	}

	return 0;
}
