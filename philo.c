
#include"philo.h"


int init_philo(t_philo *p)
{
	p->nb_p = 4;
	p->t_d = 10;
	p->t_e = 1;
	p->t_s = 1;
	p->nb_e = 5;
	p->tid = 0;
	return(0);
}

void *routine(void *arg)
{
	t_philo *p;
	
	p = (t_philo*)arg;

	ft_dprintf(2,"routine\n");
	ft_dprintf(2,"tid = %d\n", p->tid);
	return(NULL);
}

int	creat_tread(t_philo *phi)
{
	pthread_t thread[phi->nb_p];
	int i;
	int mes;

	i = 0;
	while (i < phi->nb_p)
	{
		phi->tid = i + 1;
		mes = pthread_create(&thread[i], NULL, routine, phi);
		printf("creat thread[%d] = %ld  mes = %d\n", i, thread[i], mes);
		i++;
	}

	i = 0;
	while (i < phi->nb_p)
	{
		phi->tid = i + 1;
		mes = pthread_join(thread[i], NULL);
		printf("join thread[%d] = %ld  mes = %d\n", i, thread[i], mes);
		i++;
	}

	

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