#include"philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	a;

	s = 1;
	a = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + str[i] - 48;
		i++;
	}
	return (s * a);
}

int	ft_strlen(char *c)
{
	int i;

	if(c == NULL)
		return(0);
	i = 0;
	while(c[i])
	{
		i++;
	}
	return(i);
}

long long	tv(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	printf_m(t_data *data, char *c)
{
	pthread_mutex_lock(&data->phi->gen_m);
	printf("%lld P%d %s\n", tv(), data->id, c);
	pthread_mutex_unlock(&data->phi->gen_m);
	return(0);
}
