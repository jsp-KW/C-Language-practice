/*
	싱글 스레드
	참고한 블로그 출처: https://doorbw.tistory.com/27
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN

DWORD WINAPI ThreadFunc(LPVOID);

// DWORD =long
// WINAPI: Windows 의 api
// LPVOID: ms 에서 사용하는 void*


int global = 1;

int main() {

	HANDLE thread;
	DWORD thread_id;
	
	for (int i = 0; i < 3; i++) {
		ThreadFunc((LPVOID)i);
	}

	Sleep(3000);

	return EXIT_SUCCESS;

}


DWORD WINAPI ThreadFunc(LPVOID n) {
	for (int i = 0; i < 100; i++) {
		printf("%d%d%d%d%d%d%d global = %d\n", n, n, n, n, n, n, n, global++);
	}
}
