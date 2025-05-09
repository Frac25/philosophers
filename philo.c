#include"philo.h"

int	init_philo(t_philo *phi)
{
	phi->nb_p = 4;
	phi->t_d = 410;
	phi->t_e = 200;
	phi->t_s = 200;
	phi->nb_e = 50;
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

void	*routine(void *arg)
{
	t_data	*data;
	t_philo	*phi;
	int		n;

	data = (t_data*)arg;
	phi = data->phi;

	while(tv() < phi->start_time)
		usleep(1);
	n = 0;
	while (data->phi->dead == 0 && n < data->phi->nb_e)
	{
		if(p_eat(data) == -1)
			break;
		if(p_sleep(data) == -1)
			break;
		if(p_think(data) == -1)
			break;
		n++;
	}
	data->phi->dead = 1;//checker
	return (NULL);
}

int	creat_tread(t_philo *phi)
{
	pthread_t	thread[phi->nb_p];
	pthread_t	thread_d[phi->nb_p];
	pthread_t	thread_t;
	t_data		*data_tmp;
	t_data		*data_tmp1;
	int			i;

	pthread_mutex_init(&phi->gen_m, NULL);
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
			pthread_create(&thread_t, NULL, tic, data);
		}
		data_tmp = data;
		pthread_mutex_init(&data->fork_m, NULL);
		pthread_create(&thread[i], NULL, routine, data);
		pthread_create(&thread_d[i], NULL, P_die, data);
		i++;
	}
	data_tmp1->next = data_tmp;

	i = 0;
	while (i < phi->nb_p)
	{
		pthread_join(thread[i], NULL);
		pthread_join(thread_d[i], NULL);
		i++;
	}
	pthread_join(thread_t, NULL);

	pthread_mutex_destroy(&phi->gen_m);
	pthread_mutex_destroy(&phi->dead_m);
	pthread_mutex_destroy(&phi->look_m);
	//pthread_mutex_destroy(&data->fork_m); //a faire pour chaque fork
	return(0);
}

int main(int argc, char** argv)
{
	t_philo	*phi;

	(void)argv;
	if (argc < 2)
	{
		ft_dprintf(1, "argc KO\n");
		return(-1);
	}
	phi = malloc(sizeof(t_philo));
	init_philo(phi);
//	if(argc == 2)
//		phi->nb_p = ft_atoi(argv[1]);
//	printf("nb_p = %d, nb_e = %d, t_d = %d, t_e = %d, t_s = %d\n", p->nb_p, p->nb_e, p->t_d, p->t_e, p->t_s);

	creat_tread(phi);
	return (0);
}


/*
	while(1)
	{
		printf("tv = %lld\n", tv());
		usleep(1000);
	}
*/
