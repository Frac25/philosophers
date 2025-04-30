/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintnb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:40:26 by sydubois          #+#    #+#             */
/*   Updated: 2025/04/30 15:09:51 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_dputnbr(int fd, int n, int j)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		j = 11;
	}
	else
	{
		if (n < 0)
		{
			n = -n;
			j += ft_dputchar(fd, '-');
		}
		if (n >= 10)
			j += ft_dputnbr(fd, n / 10, 0);
		n = n % 10;
		if (n < 10)
			j += ft_dputchar(fd, n + 48);
	}
	return (j);
}

int	ft_dputnbr_ui(int fd, unsigned int n, int j)
{
	if (n >= 10)
		j += ft_dputnbr(fd, n / 10, 0);
	n = n % 10;
	if (n < 10)
		j += ft_dputchar(fd, n + 48);
	return (j);
}

int	ft_dputbase(int fd, unsigned long n, char *b, int j)
{
	unsigned long	sb;

	sb = ft_strlen(b);
	if (n >= sb)
		j += ft_dputbase(fd, n / sb, b, 0);
	n = n % sb;
	if (n <= sb)
	{
		write(fd, &b[n], 1);
		j++;
	}
	return (j);
}

int	ft_dputbase_ui(int fd, unsigned int n, char *b, int j)
{
	unsigned int	sb;

	sb = ft_strlen(b);
	if (n >= sb)
		j += ft_dputbase_ui(fd, n / sb, b, 0);
	n = n % sb;
	if (n <= sb)
	{
		write(fd, &b[n], 1);
		j++;
	}
	return (j);
}
