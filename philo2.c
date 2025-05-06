#include"philo.h"

int	p_sleep (t_data *data)
{
	t_philo	*phi;
	int		id;

	phi = data->phi;
	id = data->id;
//	pthread_mutex_lock(&phi->gen_m);
	printf("%lld P%d is sleeping\n", tv(), id);
//	pthread_mutex_unlock(&phi->gen_m);
	usleep(phi->t_s * 1000);
	return (0);
}

int	p_think (t_data *data)
{
	t_philo	*phi;
	int		id;

	phi = data->phi;
	id = data->id;
//	pthread_mutex_lock(&phi->gen_m);
	printf("%lld P%d is thinking\n", tv(), id);
//	pthread_mutex_unlock(&phi->gen_m);
	return (0);
}

int	f_lock(t_data *data, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	pthread_mutex_lock(f1);
//	printf("lock f1\n");
	if(data->dead == 1)
	{
//		printf("relache f1\n");
		pthread_mutex_unlock(f1);
		return(-1);
	}
	printf("%lld P%d has taken a fork f1\n", tv(), data->id);

	pthread_mutex_lock(f2);
//	printf("lock f2\n");
//	printf("lock f2\n");
	if(data->dead == 1)
	{
//		printf("relache f2 et f1\n");
		pthread_mutex_unlock(f1);
		pthread_mutex_unlock(f2);
		return(-1);
	}
	printf("%lld P%d has taken a fork f2\n", tv(), data->id);
	return (0);
}

int	p_eat (t_data *data)
{
	t_philo	*phi;
	int		id;

	phi = data->phi;
	id = data->id;
	if(id == phi->nb_p)
	{
		if (f_lock(data, &data->fork_m, &data->next->fork_m) == -1)
			return (-1);
	}
	else
	{
		if (f_lock(data, &data->next->fork_m, &data->fork_m) == -1)
			return (-1);
	}
	data->s_e = tv();
	printf("%lld P%d is eating\n", tv(), id);
	usleep(phi->t_e * 1000);
	pthread_mutex_unlock(&data->fork_m);
//	printf("f3 relachee\n");
	pthread_mutex_unlock(&data->next->fork_m);
//	printf("f4 relachee\n");
	return (0);
}

void	*P_die(void *arg)
{
	t_data	*data;

	data = (t_data*)arg;
	while (data->dead == 0)
	{
		if(tv() - data->s_e >= data->phi->t_d)
			{
				printf("%lld P%d died\n", tv(), data->id);
				data->dead = 1;
			}
		usleep(1);
	}
	return (NULL);
}

long long	tv(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
