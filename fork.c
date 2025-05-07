#include"philo.h"

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

int	f_lock(t_data *d1, t_data *d2)
{

	pthread_mutex_lock(&d1->phi->look_m);

	if(d1->fork + d2->fork > 0)
	{
		pthread_mutex_unlock(&d1->phi->look_m);
		return (1);
	}

	if(d1->tic != d1->phi->g_tic - d1->phi->queue && d1->tic != d1->phi->g_tic - d1->phi->queue + 1)
	{
		printf("tic = %d   g-tic = %d   queue = %d\n", d1->tic, d1->phi->g_tic, d1->phi->queue);
		pthread_mutex_unlock(&d1->phi->look_m);
		return (1);
	}

	pthread_mutex_lock(&d1->fork_m);
	d1->fork = 1;
	if(d1->phi->dead == 1)
	{
		pthread_mutex_unlock(&d1->fork_m);
		d1->fork = 0;
		pthread_mutex_unlock(&d1->phi->look_m);
		return(-1);
	}
	printf_m(d1, "has taken a fork");
	pthread_mutex_lock(&d2->fork_m);
	d2->fork = 1;
	if(d1->phi->dead == 1)
	{
		pthread_mutex_unlock(&d1->fork_m);
		pthread_mutex_unlock(&d2->fork_m);
		d1->fork = 0;
		d2->fork = 0;
		pthread_mutex_unlock(&d1->phi->look_m);
		return(-1);
	}
	printf_m(d1, "has taken a fork");
	d1->phi->queue--;
	pthread_mutex_unlock(&d1->phi->look_m);
	return (0);
}
int	f_lock_w(t_data *d1, t_data *d2)
{
	int	i;

	pthread_mutex_lock(&d1->phi->look_m);
	d1->tic = d1->phi->g_tic;
	d1->phi->g_tic++;
	d1->phi->queue++;
	pthread_mutex_unlock(&d1->phi->look_m);
	i = 1;
	while(i == 1)
	{
//		printf("PASSE/n");
		i = f_lock(d1, d2);
		if (i == -1)
			return (-1);
		usleep(100);
	}
	return (0);
}
