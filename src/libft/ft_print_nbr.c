/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:41:52 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/22 13:41:54 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_hex(unsigned long num, int uppercase, int fd)
{
	char	*hex;
	int		bytes;

	hex = "0123456789abcdef";
	if (uppercase == 1)
		hex = "0123456789ABCDEF";
	if (num > 15)
	{
		bytes = ft_putnbr_hex(num / 16, uppercase, fd);
		return (bytes + ft_putchr_fd(hex[num % 16], fd));
	}
	else
		return (ft_putchr_fd(hex[num], fd));
}

int	ft_putptr(void *num, int fd)
{
	if (num == NULL)
		return (ft_putstr_fd("(nil)", fd));
	return (ft_putstr_fd("0x", fd) + ft_putnbr_hex((unsigned long)num, 0, fd));
}

int	ft_putunbr(unsigned int n, int fd)
{
	if (n > 9)
		return (ft_putunbr(n / 10, fd) + ft_putchr_fd(n % 10 + '0', fd));
	else
		return (ft_putchr_fd(n + '0', fd));
}

int	ft_putnbr(int n, int fd)
{
	long	num;
	int		i;

	num = n;
	i = 0;
	if (num < 0)
	{
		i += ft_putchr_fd('-', fd);
		num *= -1;
	}
	if (num > 9)
	{
		i += ft_putnbr(num / 10, fd);
		return (i + ft_putchr_fd(num % 10 + '0', fd));
	}
	else
		return (i + ft_putchr_fd(num + '0', fd));
}
