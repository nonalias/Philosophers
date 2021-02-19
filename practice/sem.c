#include <stdio.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/errno.h>

sem_t *sem;

int share = 0;

typedef	struct	s_hi
{
	int		nbr;
	pthread_t	thread;
}				t_hi;

void	*go(void *data)
{
	pthread_t *thread;

	thread = (pthread_t *)data;
	sem_wait(sem);
	for (int i = 0; i < 1000000; i++)
		share++;
	//exit(1);
	sem_post(sem);
	return (void *)NULL;
}

int main(void)
{
	pthread_t thread1;
	pthread_t thread2;
	sem_unlink("my_semaphore");
	sem = sem_open("my_semaphore", O_CREAT, S_IRWXU, 2);
	if (!sem)
		return (1);
	pthread_create(&thread1, NULL, go, (void *)&thread1);
	pthread_create(&thread2, NULL, go, (void *)&thread2);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("share : %d\n", share);
	sem_close(sem);
}
