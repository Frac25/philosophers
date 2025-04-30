#ifndef PHILO_H
# define PHILO_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdarg.h>

#include<pthread.h>

#include"ft_dprintf.h"

# define NC "\e[0m"
# define YELLOW "\e[1;33m"

typedef struct philo
{
	int	nb_p;
	int	t_d;
	int	t_e;
	int	t_s;
	int	nb_e;
	int	tid;
}	t_philo;


//lib1
int	ft_atoi(const char *str);
int ft_strlen(char *c);

#endif