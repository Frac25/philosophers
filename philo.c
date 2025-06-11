/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:00:11 by sydubois          #+#    #+#             */
/*   Updated: 2025/06/11 19:09:49 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *phi)
{
	phi->nb_p = 4;
	phi->t_d = 410;
	phi->t_e = 200;
	phi->t_s = 200;
	phi->nb_e = 0;
	phi->dead = 0;
	phi->start_time = tv() + 500;
	pthread_mutex_init(&phi->dead_m, NULL);
	pthread_mutex_init(&phi->look_m, NULL);
	return (0);
}

void	*p_live(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->phi->look_m);
	pthread_mutex_unlock(&data->phi->look_m);
	while (tv() < data->phi->start_time)
		usleep(100);
	if (data->id % 2 == 0)
		usleep(500);
	while (1)
	{
		p_eat(data);
		p_sleep(data);
		p_think(data);
		pthread_mutex_lock(&data->phi->dead_m);
		if (data->phi->dead == 1)
		{
			pthread_mutex_unlock(&data->phi->dead_m);
			return (NULL);
		}
		pthread_mutex_unlock(&data->phi->dead_m);
	}
	return (NULL);
}

t_data	*creat_thread(t_philo *phi, int i, t_data *data_tmp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->phi = phi;
	data->id = i + 1;
	data->fork = 0;
	data->next = data_tmp;
	data->start_eat = phi->start_time;
	data->count_eat = 0;
	pthread_mutex_init(&data->fork_m, NULL);
	pthread_create(&data->thread_l, NULL, p_live, data);
	return (data);
}

int	play(t_philo *phi)
{
	t_data		*data_tmp;
	t_data		*data_tmp1;
	int			i;

	data_tmp = NULL;
	i = 0;
	pthread_mutex_lock(&phi->look_m);
	while (i < phi->nb_p)
	{
		data_tmp = creat_thread(phi, i, data_tmp);
		if (i == 0)
			data_tmp1 = data_tmp;
		i++;
	}
	data_tmp1->next = data_tmp;
	pthread_create(&phi->thread_d, NULL, p_die, data_tmp1);
	pthread_mutex_unlock(&phi->look_m);
	join_and_destroy(data_tmp1);
	free_data(data_tmp1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*phi;

	(void)argv;
	if (argc < 1 || argc > 6)
	{
		printf("nb arg KO\n");
		return (-1);
	}
	phi = malloc(sizeof(t_philo));
	init_philo(phi);
	if (argc >= 2)
		phi->nb_p = ft_atoi(argv[1]);
	if (argc >= 3)
		phi->t_d = ft_atoi(argv[2]);
	if (argc >= 4)
		phi->t_e = ft_atoi(argv[3]);
	if (argc >= 5)
		phi->t_s = ft_atoi(argv[4]);
	if (argc >= 6)
		phi->nb_e = ft_atoi(argv[5]);
	printf("nb_p=%d td=%d te=%d ", phi->nb_p, phi->t_d, phi->t_e);
	printf("ts=%d nb_e=%d\n", phi->t_s, phi->nb_e);
	play(phi);
	free(phi);
	return (0);
}
