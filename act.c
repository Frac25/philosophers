#include"philo.h"

int	p_sleep (t_data *data)
{
	printf_m(data, "is sleeping");
	usleep(data->phi->t_s * 1000);
//	printf("S1 P%d stop sleeping\n", data->id);
	return (0);
}

int	p_think (t_data *data)
{
	printf_m(data, "is thinking");
	return (0);
}

int	p_eat (t_data *data)
{
	if (f_lock_w(data) == -1)
		return (-1);
	pthread_mutex_lock(&data->phi->dead_m);
	data->s_e = tv();
	pthread_mutex_unlock(&data->phi->dead_m);
	printf_m(data, "is eating");
	usleep(data->phi->t_e * 1000);
	f_unlock(data);
	return (0);
}

void	*p_die(void *arg)
{
	t_data	*data;

	data = (t_data*)arg;
	while (1)
	{
		pthread_mutex_lock(&data->phi->dead_m);
		if(data->phi->dead == 1 || data->sta == 1)
		{
			pthread_mutex_unlock(&data->phi->dead_m);
			return(NULL);
		}
		if(tv() - data->s_e >= data->phi->t_d)
		{
			printf("print %lld P%d %s\n", tv(), data->id, "died");
			data->phi->dead = 1;
			pthread_mutex_unlock(&data->phi->dead_m);
			return(NULL);
		}
		pthread_mutex_unlock(&data->phi->dead_m);
		usleep(100);
	}
	return (NULL);
}


