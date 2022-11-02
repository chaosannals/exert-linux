#include <pthread.h>
#include <unistd.h>
#include <iostream>

void* start_routine(void* arg) {
	int* running = reinterpret_cast<int*>(arg);

	std::cout << u8"子线程开始" << std::endl;

	while (*running) {
		std::cout << u8"子线程运行" << std::endl;
		usleep(1);
	}
	std::cout << u8"子线程退出" << std::endl;
	static int retvalue = 8;
	pthread_exit(&retvalue);
}

int main() {
	pthread_t pt;
	static int running = 1;
	int ret = pthread_create(&pt, nullptr, start_routine, &running);

	if (ret != 0) {
		std::cerr << u8"建立线程失败" << std::endl;
		return -1;
	}

	usleep(1);
	for (int i = 0; i < 10; ++i) {
		std::cout << u8"主线程输出：" << i << std::endl;
		usleep(1);
	}

	int *retvalue;
	running = 0;
	pthread_join(pt, reinterpret_cast<void**>(&retvalue));

	std::cout << u8"子线程返回： " << *retvalue << std::endl;

	return 0;
}