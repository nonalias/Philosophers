#include "philo_two.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*mover;
	char	*output;

	size = ft_strlen(s1) + ft_strlen(s2);
	output = (char *)malloc(sizeof(char) * (size + 1));
	if (!output)
		return (0);
	mover = (char *)s1;
	while (*mover)
	{
		*output = *mover;
		output++;
		mover++;
	}
	mover = (char *)s2;
	while (*mover)
	{
		*output = *mover;
		output++;
		mover++;
	}
	*output = '\0';
	return (output - size);
}

char	*dec_to_a(long n, int size, int is_minus)
{
	char	*output;

	output = malloc(sizeof(char) * (size + is_minus + 1));
	if (!output)
		return (NULL);
	if (is_minus)
		output[0] = '-';
	output[size + is_minus] = '\0';
	while (--size + is_minus >= is_minus)
	{
		output[size + is_minus] = (n % 10) + '0';
		n = n / 10;
	}
	return (output);
}

char	*ft_itoa(int n)
{
	int		is_minus;
	int		size;
	long	temp;
	long	arg;

	temp = n;
	arg = n;
	is_minus = 0;
	if (temp < 0)
	{
		arg = -arg;
		temp = -temp;
		is_minus = 1;
	}
	size = 0;
	while (temp)
	{
		size++;
		temp = temp / 10;
	}
	if (!size)
		size++;
	return (dec_to_a(arg, size, is_minus));
}
