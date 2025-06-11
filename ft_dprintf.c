/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:50:32 by sydubois          #+#    #+#             */
/*   Updated: 2025/04/30 14:48:22 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_dputchar(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_dputstr(int fd, char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (s[i])
		i += ft_dputchar(fd, s[i]);
	return (i);
}

int	ft_dputptr(int fd, unsigned long n)
{
	int	i;

	write (fd, "0", 1);
	write (fd, "x", 1);
	i = 2 + ft_dputbase(fd, n, "0123456789abcdef", 0);
	return (i);
}

int	ft_dprint_type(int fd, va_list args, char format)
{
	int	i;

	i = 0;
	if (format == 'c')
		i += ft_dputchar(fd, va_arg(args, int));
	if (format == 'i')
		i += ft_dputnbr(fd, va_arg(args, int), 0);
	if (format == 's')
		i += ft_dputstr(fd, va_arg(args, char *));
	if (format == 'p')
		i += ft_dputptr(fd, (unsigned long)va_arg(args, char *));
	if (format == 'x')
		i += ft_dputbase_ui(fd, va_arg(args, int), "0123456789abcdef", 0);
	if (format == 'X')
		i += ft_dputbase_ui(fd, va_arg(args, int), "0123456789ABCDEF", 0);
	if (format == 'd')
		i += ft_dputnbr(fd, va_arg(args, int), 0);
	if (format == 'u')
		i += ft_dputnbr_ui(fd, (unsigned int)va_arg(args, unsigned int), 0);
	if (format == '%')
		i += ft_dputchar(fd, '%');
	return (i);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	char		sep;
	size_t		i;
	int			j;
	va_list		args;

	va_start(args, str);
	sep = '%';
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == sep)
		{
			i++;
			j += ft_dprint_type(fd, args, str[i]);
		}
		else
			j += ft_dputchar(fd, str[i]);
		i++;
	}
	va_end(args);
	return (j);
}
