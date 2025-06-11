/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:38:32 by sydubois          #+#    #+#             */
/*   Updated: 2025/06/11 16:53:30 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_and_destroy(t_data *data_tmp1)
{
	t_data	*data_tmp;
	int		i;

	i = 0;
	data_tmp = data_tmp1;
	while (i < data_tmp1->phi->nb_p)
	{
		pthread_join(data_tmp->thread_l, NULL);
		i++;
		data_tmp = data_tmp->next;
	}
	pthread_join(data_tmp1->phi->thread_d, NULL);
	pthread_mutex_destroy(&data_tmp1->phi->dead_m);
	pthread_mutex_destroy(&data_tmp1->phi->look_m);
	data_tmp = data_tmp1;
	i = 0;
	while (i < data_tmp1->phi->nb_p)
	{
		pthread_mutex_destroy(&data_tmp->fork_m);
		data_tmp = data_tmp->next;
		i++;
	}
}

void	free_data(t_data *data_tmp1)
{
	t_data	*data_tmp;
	int		i;
	int		n;

	data_tmp = data_tmp1;
	i = 0;
	n = data_tmp1->phi->nb_p;
	while (i < n)
	{
		data_tmp1 = data_tmp->next;
		free(data_tmp);
		data_tmp = data_tmp1;
		i++;
	}
}
