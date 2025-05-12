#include"philo.h"

int	init_philo(t_philo *phi)
{
	phi->nb_p = 4;
	phi->t_d = 410;
	phi->t_e = 200;
	phi->t_s = 200;
	phi->nb_e = 10;
	phi->dead = 0;
	phi->g_tic = 1;
	phi->tic_min = 0;
	return(0);
}

int	init_data(t_data *data, t_philo *phi, int i, t_data *data_tmp)
{
	data->phi = phi;
	data->id = i + 1;
	data->fork = 0;
	data->next = data_tmp;
	data->s_e = phi->start_time;
	return(0);
}

void	*p_live(void *arg)
{
	t_data	*data;
	int		n;

	data = (t_data*)arg;
	while(tv() < data->phi->start_time)
		usleep(10);
	if (data->id%2 != 0)
		usleep(1000);
	n = 0;
	while (n < data->phi->nb_e )
	{
		if (p_eat(data) == -1)
		{
//			printf("LIVE11\n");
			return(NULL);
		}
		p_sleep(data);
//		printf("LIVE12\n");
		p_think(data);
//		printf("LIVE13\n");
		n++;
	}
//	printf("LIVE2\n");
	return (NULL);
}

int	creat_tread(t_philo *phi)
{
	pthread_t	thread_l[phi->nb_p];
	pthread_t	thread_d[phi->nb_p];
	pthread_t	thread_t;
	t_data		*data_tmp;
	t_data		*data_tmp1;
	int			i;

//	pthread_mutex_init(&phi->write, NULL);
	pthread_mutex_init(&phi->dead_m, NULL);
	pthread_mutex_init(&phi->look_m, NULL);
	data_tmp = NULL;
	phi->start_time = tv() + 10;
	i = 0;
	while (i < phi->nb_p)
	{
		t_data *data;
		data = malloc(sizeof(t_data));
		init_data(data, phi, i, data_tmp);
		if (i == 0)
		{
			data_tmp1 = data;
			pthread_create(&thread_t, NULL, ticket, data);
		}
		data_tmp = data;
		pthread_mutex_init(&data->fork_m, NULL);
		pthread_create(&thread_l[i], NULL, p_live, data);
		pthread_create(&thread_d[i], NULL, p_die, data);
		i++;
	}
	data_tmp1->next = data_tmp;

	i = 0;
	while (i < phi->nb_p)
	{
//		printf("F1\n");
		pthread_join(thread_l[i], NULL);
		i++;
	}
	i = 0;
	while (i < phi->nb_p)
	{
//		printf("F2\n");
		pthread_join(thread_d[i], NULL);
		i++;
	}
//	printf("F3\n");
	pthread_join(thread_t, NULL);
//	printf("F4\n");
	pthread_mutex_destroy(&phi->dead_m);
	pthread_mutex_destroy(&phi->look_m);
	data_tmp = data_tmp1;
	i = 0;
	while (i < phi->nb_p)
	{
//		printf("F5\n");
		pthread_mutex_destroy(&data_tmp->fork_m);
		data_tmp = data_tmp->next;
		i++;
	}
	data_tmp = data_tmp1;
	i = 0;
	while (i < phi->nb_p)
	{
//		printf("F6\n");
		data_tmp1 = data_tmp->next;
		free(data_tmp);
		data_tmp = data_tmp1;
		i++;
	}
	return(0);
}

int main(int argc, char** argv)
{
	t_philo	*phi;

	(void)argv;
	if (argc < 1 || argc > 6)
	{
		printf("nb arg KO\n");
		return(-1);
	}
	phi = malloc(sizeof(t_philo));
	init_philo(phi);
	if(argc >= 2)
		phi->nb_p = ft_atoi(argv[1]);
	if(argc >= 3)
		phi->t_d = ft_atoi(argv[2]);
	if(argc >= 4)
		phi->t_e = ft_atoi(argv[3]);
	if(argc >= 5)
		phi->t_s = ft_atoi(argv[4]);
	if(argc >= 6)
		phi->nb_e = ft_atoi(argv[5]);
	printf("nb_p = %d, td = %d te = %d ts= %d nb_e = %d\n", phi->nb_p, phi->t_d, phi->t_e, phi->t_s, phi->nb_e);
	creat_tread(phi);
	free(phi);
	return (0);
}


