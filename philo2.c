#include"philo.h"

int	p_sleep (t_data *data)
{
	t_philo	*phi;
	int		id;

	phi = data->phi;
	id = data->id;
	if(data->phi->dead == 1)
		return(-1);
	printf_m(data, "is sleeping");
	usleep(phi->t_s * 1000);
	return (0);
}

int	p_think (t_data *data)
{
	t_philo	*phi;
	int		id;

	phi = data->phi;
	id = data->id;
	if(data->phi->dead == 1)
		return(-1);
	printf_m(data, "is thinking");
	return (0);
}

int	f_lock(t_data *data, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	pthread_mutex_lock(f1);
	if(data->phi->dead == 1)
	{
		pthread_mutex_unlock(f1);
		return(-1);
	}
	printf_m(data, "has taken a fork");
	pthread_mutex_lock(f2);
	if(data->phi->dead == 1)
	{
		pthread_mutex_unlock(f1);
		pthread_mutex_unlock(f2);
		return(-1);
	}
	printf_m(data, "has taken a fork");
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
	printf_m(data, "is eating");
	usleep(phi->t_e * 1000);
	pthread_mutex_unlock(&data->fork_m);
	pthread_mutex_unlock(&data->next->fork_m);
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
		}
		pthread_mutex_unlock(&data->phi->dead_m);
		usleep(1);
	}
	return (NULL);
}


