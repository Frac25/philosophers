/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:52:49 by sydubois          #+#    #+#             */
/*   Updated: 2025/06/11 14:53:10 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	a;

	s = 1;
	a = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + str[i] - 48;
		i++;
	}
	return (s * a);
}

long long	tv(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	printf_m(t_data *data, char *c)
{
	pthread_mutex_lock(&data->phi->dead_m);
	if (data->phi->dead == 1)
	{
		pthread_mutex_unlock(&data->phi->dead_m);
		return (-1);
	}
	pthread_mutex_unlock(&data->phi->dead_m);
	pthread_mutex_lock(&data->phi->look_m);
	printf("%lld P%d %s\n", tv(), data->id, c);
	pthread_mutex_unlock(&data->phi->look_m);
	return (0);
}

int	printf_l(t_data *data, char *c)
{
	pthread_mutex_lock(&data->phi->look_m);
	printf("%lld P%d %s\n", tv(), data->id, c);
	pthread_mutex_unlock(&data->phi->look_m);
	return (0);
}

/*
int	check_dead(t_data *data)
{
	pthread_mutex_lock(&data->phi->dead_m);
	if(data->phi->dead == 1)
	{
		pthread_mutex_unlock(&data->phi->dead_m);
		return (-1);
	}
	pthread_mutex_unlock(&data->phi->dead_m);
	return(0);
}
*/