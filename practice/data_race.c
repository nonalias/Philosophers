#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int		count;
pthread_mutex_t mt;

void	*t_function(void *data)
{
	pthread_t	tid;
	pid_t		pid;

	/*
	pid = getpid();
	tid = pthread_self();
	printf("[%s] pid : %d, tid : %x\n", (char *)data, pid, tid);
	*/
	pthread_mutex_lock(&mt);
	int i = 0;
	while (i < 100000)
	{
		i++;
		count++;
	}
	pthread_mutex_unlock(&mt);
}

int		main(void)
{
	pthread_t	tid[2];
	pthread_t	t_main;

	pthread_mutex_init(&mt, NULL);

	count = 0;
	pthread_create(&tid[0], NULL, t_function, (void *)"thread1");
	pthread_create(&tid[1], NULL, t_function, (void *)"thread2");
	t_main = pthread_self();
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	printf("hello, main pid : %d, tid : %x\n", getpid(), t_main);
	printf("count : %d\n", count);
	pthread_mutex_destroy(&mt);
}
