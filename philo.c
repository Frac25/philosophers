#include"philo.h"


int	init_philo(t_philo *phi)
{
	phi->nb_p = 4;
	phi->t_d = 410;
	phi->t_e = 200;
	phi->t_s = 100;
	phi->nb_e = 7;
	return(0);
}

void	*routine(void *arg)
{
	t_data	*data;
	t_philo	*phi;
	int		id;
	int		n;

	data = (t_data*)arg;
	phi = data->phi;
	id = data->id;


	while(tv() < phi->start_time)
		usleep(1);
//	printf("   tv2 = %lld phi->start_time = %lld\n", tv(), phi->start_time);

	n = 0;
	while (data->dead == 0 && n < data->phi->nb_e)
	{
		if(p_eat(data) == -1)
			break;
		p_sleep(data);
		p_think(data);
		n++;
	}
	data->dead = 1;
	return (NULL);
}

int	creat_tread(t_philo *phi)
{
	pthread_t	thread[phi->nb_p];
	pthread_t	thread_d[phi->nb_p];
	t_data		*data_tmp;
	t_data		*data_tmp1;
	int			i;
	int			mes;

	pthread_mutex_init(&phi->gen_m, NULL);
	data_tmp = NULL;
	phi->start_time = tv() + 10;
	//	printf("   tv = %lld phi->start_time = %lld\n", tv(), phi->start_time);
	i = 0;
	while (i < phi->nb_p)
	{
		t_data *data;
		data = malloc(sizeof(t_data));
		if (i == 0)
			data_tmp1 = data;
		data->phi = phi;
		data->id = i + 1;
		data->next = data_tmp;
		data->s_e = phi->start_time;
		data->dead = 0;
		data_tmp = data;
		pthread_mutex_init(&data->fork_m, NULL);
//		printf("   creat thread[%d]\n", i + 1);
		mes = pthread_create(&thread[i], NULL, routine, data);
		printf("   thread[%d] = %ld   mes = %d\n", i + 1, (long)thread[i], mes);
		pthread_create(&thread_d[i], NULL, P_die, data);
		i++;
	}
	data_tmp1->next = data_tmp;

	i = 0;
	while (i < phi->nb_p)
	{
		mes = pthread_join(thread[i], NULL);
//		printf("join thread[%d] = %ld  mes = %d\n", i + 1, thread[i], mes);
		mes = pthread_join(thread_d[i], NULL);
		i++;
	}

	pthread_mutex_destroy(&phi->gen_m);
//	pthread_mutex_destroy(&&data->fork_m); a checker
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
	if(argc == 2)
		phi->nb_p = ft_atoi(argv[1]);
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
