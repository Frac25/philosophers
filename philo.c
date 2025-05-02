
#include"philo.h"


int init_philo(t_philo *phi)
{
	phi->nb_p = 4;
	phi->t_d = 10;
	phi->t_e = 1;
	phi->t_s = 1;
	phi->nb_e = 5;
	return(0);
}

long long tv(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec);
}

void *routine(void *arg)
{
	t_data *data;
	t_philo *phi;
	int id;

	data = (t_data*)arg;
	phi = data->phi;
	id = data->id;
	pthread_mutex_lock(&phi->id_m);
	printf("%lld %d has taken a fork\n", tv(), id);
	printf("%lld %d is eating\n", tv(), id);
	printf("%lld %d is sleeping\n", tv(), id);
	usleep(phi->t_s);
	printf("%lld %d is thinking\n", tv(), id);

	pthread_mutex_unlock(&phi->id_m);
	return(NULL);
}

int	creat_tread(t_philo *phi)
{
	pthread_t thread[phi->nb_p];
	int i;
	int mes;

	pthread_mutex_init(&phi->id_m, NULL);

	i = 0;
	while (i < phi->nb_p)
	{
		t_data *data;

		data = malloc(sizeof(t_data));
		data->phi = phi;
		data->id = i + 1;

		printf("creat thread[%d]\n", i + 1);
		mes = pthread_create(&thread[i], NULL, routine, data);
		printf("thread[%d] = %ld  mes = %d\n", i + 1, thread[i], mes);
		i++;
	}

	i = 0;
	while (i < phi->nb_p)
	{
		mes = pthread_join(thread[i], NULL);
		printf("join thread[%d] = %ld  mes = %d\n", i + 1, thread[i], mes);
		i++;
	}

	pthread_mutex_destroy(&phi->id_m);

	return(0);
}

int main(int argc, char** argv)
{
	t_philo	*phi;


	(void)argv;
	if (argc < 2)
	{
		ft_dprintf(1, "argc KO");
		return(-1);
	}
	phi = malloc(sizeof(t_philo));
	init_philo(phi);
	if(argc == 2)
		phi->nb_p = ft_atoi(argv[1]);
//	printf("nb_p = %d, nb_e = %d, t_d = %d, t_e = %d, t_s = %d\n", p->nb_p, p->nb_e, p->t_d, p->t_e, p->t_s);
	creat_tread(phi);

	sleep(1);

	return (0);
}
