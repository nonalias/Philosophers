#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int		main(void)
{
	struct timeval startTime, endTime;
	double diffTime;

	gettimeofday(&startTime, NULL);
	usleep(523234);
	gettimeofday(&endTime, NULL);
	diffTime = (endTime.tv_sec - startTime.tv_sec) + ((endTime.tv_usec - startTime.tv_usec) / 1000000.0);
	printf("%fs\n", diffTime);
}
