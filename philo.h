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
	int	nb_p;
	int	t_d;
	int	t_e;
	int	t_s;
	int	nb_e;
	pthread_mutex_t id_m;
}	t_philo;

typedef struct s_data
{
	int id;
	t_philo *phi;
}	t_data;


//lib1
int	ft_atoi(const char *str);
int ft_strlen(char *c);

#endif
