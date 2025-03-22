/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:41:52 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/22 13:41:54 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	process(va_list args, int fd, char **format, char specifier)
{
	int	bytes;

	bytes = 0;
	if (specifier == '%')
		bytes = ft_putchr_fd('%', fd);
	else if (specifier == 'c')
		bytes = ft_putchr_fd(va_arg(args, int), fd);
	else if (specifier == 's')
		bytes = ft_putstr_fd(va_arg(args, char *), fd);
	else if (specifier == 'd' || specifier == 'i')
		bytes = ft_putnbr(va_arg(args, int), fd);
	else if (specifier == 'u')
		bytes = ft_putunbr(va_arg(args, int), fd);
	else if (specifier == 'x' || specifier == 'X')
		bytes = ft_putnbr_hex(va_arg(args, unsigned int), specifier == 'X', fd);
	else if (specifier == 'p')
		bytes = ft_putptr(va_arg(args, void *), fd);
	*format += 2;
	return (bytes);
}

int	ft_vprintf_fd(va_list args, int fd, const char *format, ...)
{
	int		bytes;
	char	*specifier;
	char	*s;

	if (!format)
		return (-1);
	bytes = 0;
	s = (char *)format;
	while (*s)
	{
		if (*s != '%' && ++bytes)
		{
			ft_putchr_fd(*s, fd);
			s++;
			continue ;
		}
		specifier = ft_strchr("cspdiuxX%", *(s + 1));
		if (!specifier && ++bytes && ++s)
			ft_putchr_fd('%', fd);
		else
			bytes += process(args, fd, &s, *specifier);
	}
	return (bytes);
}

int	ft_vprintf(va_list args, const char *format, ...)
{
	return (ft_vprintf_fd(args, STDOUT_FILENO, format));
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		bytes;

	if (!format)
		return (-1);
	va_start(args, format);
	bytes = ft_vprintf_fd(args, fd, format);
	va_end(args);
	return (bytes);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		bytes;

	if (!format)
		return (-1);
	va_start(args, format);
	bytes = ft_vprintf(args, format);
	va_end(args);
	return (bytes);
}
