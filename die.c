/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:40:59 by sydubois          #+#    #+#             */
/*   Updated: 2025/06/11 19:11:35 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	check_die(t_data *data)
{
	t_data	*data_tmp;
	int		i;

	data_tmp = data;
	i = 0;
	while (i < data->phi->nb_p)
	{
		if (tv() - data_tmp->start_eat >= data->phi->t_d)
		{
			printf_l(data_tmp, "died");
			data->phi->dead = 1;
			pthread_mutex_unlock(&data->phi->dead_m);
			return (-1);
		}
		i++;
		data_tmp = data->next;
	}
	return (0);
}

int	check_eat_enaf(t_data *data)
{
	t_data	*data_tmp;
	int		i;
	int		n;

	data_tmp = data;
	i = 0;
	n = 0;
	while (i < data->phi->nb_p)
	{
		if (data_tmp->count_eat >= data->phi->nb_e)
			n++;
		i++;
		data_tmp = data->next;
	}
	if (n >= data->phi->nb_p)
	{
		data->phi->dead = 1;
		pthread_mutex_unlock(&data->phi->dead_m);
		printf_l(data, "everybody has eaten enaf");
		return (-1);
	}
	return (0);
}

void	*p_die(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->phi->look_m);
	pthread_mutex_unlock(&data->phi->look_m);
	while (tv() < data->phi->start_time)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&data->phi->dead_m);
		if (check_die(data) == -1)
			return (NULL);
		if (data->phi->nb_e != 0)
		{
			if (check_eat_enaf(data) == -1)
				return (NULL);
		}
		pthread_mutex_unlock(&data->phi->dead_m);
		usleep(100);
	}
	return (NULL);
}
