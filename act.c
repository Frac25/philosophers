/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:40:22 by sydubois          #+#    #+#             */
/*   Updated: 2025/06/11 17:33:35 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	p_sleep(t_data *data)
{
	printf_m(data, "is sleeping");
	usleep(data->phi->t_s * 1000);
	return (0);
}

int	p_think(t_data *data)
{
	printf_m(data, "is thinking");
	return (0);
}

int	p_eat(t_data *data)
{
	f_lock(data);
	pthread_mutex_lock(&data->phi->dead_m);
	if (data->phi->dead == 1)
	{
		f_unlock(data);
		pthread_mutex_unlock(&data->phi->dead_m);
		return (0);
	}
	data->start_eat = tv();
	data->count_eat++;
	pthread_mutex_unlock(&data->phi->dead_m);
	printf_m(data, "is eating");
	usleep(data->phi->t_e * 1000);
	f_unlock(data);
	return (0);
}
