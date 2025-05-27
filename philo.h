#ifndef PHILO_H
# define PHILO_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdarg.h>

#include<pthread.h>
#include<sys/time.h>

typedef struct s_philo
{
	int				nb_p;
	int				t_d;
	int				t_e;
	int				t_s;
	int				nb_e;
	long long		start_time;
	int				dead;
	pthread_mutex_t	dead_m;
	pthread_mutex_t	look_m;
}	t_philo;

typedef struct s_data
{
	struct s_data	*next;
	int				id;
	t_philo			*phi;
	int				fork;
	pthread_mutex_t	fork_m;
	long long		start_eat;
	int				count_eat;
}	t_data;

//philo
int			init_philo(t_philo *phi);
void		*p_live(void *arg);
int			creat_tread(t_philo *phi);
int			init_data(t_data *data, t_philo *phi, int i, t_data *data_tmp);
//main

//act
int			p_sleep (t_data *data);
int			p_think (t_data *data);
int			p_eat (t_data *data);
void		*p_die(void *arg);

//lock
int			f_unlock(t_data *data);
int			f_lock(t_data *data);
int			f_lock_w(t_data *data);

//lib1
int			ft_atoi(const char *str);
int			ft_strlen(char *c);
long long	tv(void);
int			printf_m(t_data *data, char *c);
int			printf_l(t_data *data, char *c);
int			check_dead(t_data *data);
int			gp(int n);

#endif
