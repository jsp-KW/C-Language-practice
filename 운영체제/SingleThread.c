/*
	 멀티 스레드 예제 
	 참고한 블로그 출처 : https://doorbw.tistory.com/27
*/

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


DWORD WINAPI ThreadFunc(LPVOID);


int global = 1;


int main() {
	HANDLE thread;
	DWORD thread_id;

	for (int i = 0; i < 5; i++) {
		thread = CreateThread(NULL, 0, ThreadFunc, (LPVOID)i, 0, &thread_id);

		if (thread) {
			printf("Thread started %d \n", i);
			CloseHandle(thread);
		}
	}

	Sleep(1000);
	return EXIT_SUCCESS;
}


DWORD WINAPI ThreadFunc(LPVOID n) {
	for (int i = 0; i < 100; i++) {
		printf("%d%d%d%d%d%d%d%d global = %d\n", n, n, n, n, n, n, n, n, global++);

	}

	return 0;
}
