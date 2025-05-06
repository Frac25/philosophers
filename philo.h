#ifndef PHILO_H
# define PHILO_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdarg.h>

#include<pthread.h>
#include <sys/time.h>

#include"ft_dprintf.h"

# define NC "\e[0m"
# define YELLOW "\e[1;33m"

typedef struct s_philo
{
	int				nb_p;
	int				t_d;
	int				t_e;
	int				t_s;
	int				nb_e;
	long long		start_time;
	pthread_mutex_t	gen_m;
}	t_philo;

typedef struct s_data
{
	struct s_data	*next;
	int				id;
	t_philo			*phi;
	pthread_mutex_t	fork_m;
	long long		s_e;
	int				dead;
}	t_data;

//philo
int		init_philo(t_philo *phi);
void	*routine(void *arg);
int		creat_tread(t_philo *phi);
//main

//philo2
int			p_sleep (t_data *data);
int			p_think (t_data *data);
int			p_eat (t_data *data);
void		*P_die(void *arg);
long long	tv(void);

//lib1
int	ft_atoi(const char *str);
int ft_strlen(char *c);

#endif
