/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:56:30 by sydubois          #+#    #+#             */
/*   Updated: 2025/06/11 16:57:14 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<stdarg.h>

# include<pthread.h>
# include<sys/time.h>

typedef struct s_philo
{
	pthread_t		thread_d;
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
	t_philo			*phi;
	struct s_data	*next;
	int				id;
	pthread_t		thread_l;
	int				fork;
	pthread_mutex_t	fork_m;
	long long		start_eat;
	int				count_eat;
}	t_data;

//philo
int			init_philo(t_philo *phi);
void		*p_live(void *arg);
t_data		*creat_thread(t_philo *phi, int i, t_data *data_tmp);
int			play(t_philo *phi);
//main

//close
void		free_data(t_data *data_tmp1);
void		join_and_destroy(t_data *data_tmp1);

//act
int			p_sleep(t_data *data);
int			p_think(t_data *data);
int			p_eat(t_data *data);

//die
void		*p_die(void *arg);
int			check_die(t_data *data);
int			check_eat_enaf(t_data *data);

//lock
int			f_unlock(t_data *data);
int			f_lock(t_data *data);
int			f_lock_w(t_data *data);

//lib1
int			ft_atoi(const char *str);
long long	tv(void);
int			printf_m(t_data *data, char *c);
int			printf_l(t_data *data, char *c);

#endif
