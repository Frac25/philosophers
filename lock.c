#include"philo.h"

int	f_unlock(t_data *data)
{
	pthread_mutex_unlock(&data->fork_m);
	pthread_mutex_unlock(&data->next->fork_m);
	return(0);
}

int	f_lock(t_data *data)
{
	if(data->phi->nb_p == 1)
	{
		pthread_mutex_lock(&data->fork_m);
		printf_m(data, "has taken a fork");
		usleep(( data->phi->t_d + 10) * 1000);
	}
	else if(data->id >= data->next->id)
	{
		pthread_mutex_lock(&data->fork_m);
		printf_m(data, "has taken a fork");
		pthread_mutex_lock(&data->next->fork_m);
		printf_m(data, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->next->fork_m);
		printf_m(data, "has taken a fork");
		pthread_mutex_lock(&data->fork_m);
		printf_m(data, "has taken a fork");
	}
	return (0);
}
