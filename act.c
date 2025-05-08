#include"philo.h"

int	p_sleep (t_data *data)
{
	t_philo	*phi;

	phi = data->phi;
	printf_m(data, "is sleeping");
	usleep(phi->t_s * 1000);
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
	data->s_e = tv();
	printf_m(data, "is eating");
	usleep(data->phi->t_e * 1000);
	f_unlock(data);
	return (0);
}

void	*P_die(void *arg)
{
	t_data	*data;

	data = (t_data*)arg;
	while (data->phi->dead == 0)
	{
		pthread_mutex_lock(&data->phi->dead_m);
		if(tv() - data->s_e >= data->phi->t_d)
		{
			printf_m(data, "died");
			data->phi->dead = 1;
			exit(EXIT_SUCCESS);
		}
		pthread_mutex_unlock(&data->phi->dead_m);
		usleep(10);
	}
	return (NULL);
}


