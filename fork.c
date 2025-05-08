#include"philo.h"

int	ticmin (t_data *data)
{
	int	i;
	t_data *data_tmp;
	int tic_min;

	pthread_mutex_lock(&data->phi->look_m);
	data_tmp = data;
	tic_min = 1000;
	i = 0;
	while (i < data->phi->nb_p)
	{
		if(data_tmp->tic > 0 && data_tmp->tic < tic_min)
			tic_min = data_tmp->tic;
		data_tmp = data_tmp->next;
		i++;
	}
	data->phi->tic_min = tic_min;
//	printf("tic_min = %d\n", data->phi->tic_min);
	pthread_mutex_unlock(&data->phi->look_m);
	return (0);
}

void	*tic(void *arg)
{
	t_data	*data;
	t_philo	*phi;

	data = (t_data*)arg;
	phi = data->phi;

	while(tv() < phi->start_time)
	usleep(1);

	while (data->phi->dead == 0)
	{
		ticmin(data);
		usleep(1000);
	}
	data->phi->dead = 1;
	return (NULL);
}

int	f_unlock(t_data *data)
{
	pthread_mutex_lock(&data->phi->look_m);
	pthread_mutex_unlock(&data->fork_m);
	pthread_mutex_unlock(&data->next->fork_m);
	data->fork = 0;
	data->next->fork = 0;
	pthread_mutex_unlock(&data->phi->look_m);
	return(0);
}

int	f_lock(t_data *data)
{

	pthread_mutex_lock(&data->phi->look_m);

	if(data->fork + data->next->fork > 0)
	{
		pthread_mutex_unlock(&data->phi->look_m);
		return (1);
	}
	if(data->tic != data->phi->tic_min)
	{
		pthread_mutex_unlock(&data->phi->look_m);
		return (1);
	}

	pthread_mutex_lock(&data->fork_m);
	data->fork = 1;
	printf_m(data, "has taken a fork");
	pthread_mutex_lock(&data->next->fork_m);
	data->next->fork = 1;
	printf_m(data, "has taken a fork");
	data->tic = 0;
	pthread_mutex_unlock(&data->phi->look_m);
	return (0);
}
int	f_lock_w(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->phi->look_m);
	data->tic = data->phi->g_tic;
	data->phi->g_tic++;
//	printf("lock W   P%d   tic = %d\n", data->id, data->tic);
	pthread_mutex_unlock(&data->phi->look_m);
	i = 1;
	while(i == 1)
	{
		i = f_lock(data);
		if (i == -1)
			return (-1);
		usleep(100);
	}
	return (0);
}
