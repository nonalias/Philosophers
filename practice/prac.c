#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int i;
void	*t_function(void *data)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	char	*thread_name = (char *)data;
	int i = 0;
	while (i < 3)
	{
		printf("[%s] pid : %d, tid: %x --- %d\n",
				thread_name, (unsigned int)pid, (unsigned int)tid, i);
		i++;
		//sleep(1);
	}
	printf("\n");
}

int		main(void)
{
	pthread_t p_thread[3];
	int thr_id;
	int status;
	char *p1 = "thread_1";
	char *p2 = "thread_2";
	char *p3 = "thread_3";
	char *pM = "thread_m";

	sleep(1);
	thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)p1);
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}
	thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)p2);
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}
	thr_id = pthread_create(&p_thread[2], NULL, t_function, (void *)p3);
	t_function((void *)pM);
	pthread_join(p_thread[0], (void **)&status);
	pthread_join(p_thread[1], (void **)&status);
	pthread_join(p_thread[2], (void **)&status);
	return 0;
}
