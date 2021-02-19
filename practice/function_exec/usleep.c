#include <unistd.h>
#include <stdio.h>

int main(void)
{
	printf("안녕하세요 카운트다운을 시작합니다.\n");
	printf("3초\n");
	usleep(1000000);
	printf("2초\n");
	usleep(1000000);
	printf("1초\n");
	usleep(1000000);
	printf("펑\n");
}

