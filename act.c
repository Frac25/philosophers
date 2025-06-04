#include"philo.h"

int	p_sleep (t_data *data)
{
	printf_m(data, "is sleeping");
	usleep(data->phi->t_s * 1000);
	return (0);
}

int	p_think (t_data *data)
{
	printf_m(data, "is thinking");
	return (0);
}

int	p_eat (t_data *data)
{
	f_lock(data);
	pthread_mutex_lock(&data->phi->dead_m);
	data->start_eat = tv();
	data->count_eat++;
	pthread_mutex_unlock(&data->phi->dead_m);
	printf_m(data, "is eating");
	usleep(data->phi->t_e * 1000);
	printf_m(data, "stop eating");
	f_unlock(data);
	printf_m(data, "unlock");
	return (0);
}

void	*p_die(void *arg)
{
	t_data	*data;
	t_data	*data_tmp;
	int i;
	int n;

	data = (t_data*)arg;
	pthread_mutex_lock(&data->phi->look_m);
	pthread_mutex_unlock(&data->phi->look_m);
	while(tv() < data->phi->start_time)
	usleep(100);

	while (1)
	{
		pthread_mutex_lock(&data->phi->dead_m);
		data_tmp = data;
		i = 0;
		while (i < data->phi->nb_p)
		{
			if(tv() - data_tmp->start_eat >= data->phi->t_d)
			{
//				printf("print %lld P%d %s\n", tv(), data_tmp->id, "died");
				printf_l(data_tmp, "died");
				data->phi->dead = 1;
				pthread_mutex_unlock(&data->phi->dead_m);
				return(NULL);
			}
			i++;
			data_tmp = data->next;
		}
		data_tmp = data;
		i = 0;
		n = 0;
		while (i < data->phi->nb_p)
		{
			if(data->count_eat >= data->phi->nb_e + 1)
				n++;
			i++;
			data_tmp = data->next;
		}
		if(n >= data->phi->nb_p)
		{
			data->phi->dead = 1;
			pthread_mutex_unlock(&data->phi->dead_m);
			printf_l(data, "everybody has eaten enaf");
			return(NULL);
		}
		pthread_mutex_unlock(&data->phi->dead_m);

		usleep(100);
	}
	return (NULL);
}
