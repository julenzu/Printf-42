/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzuazo <jzuazo@student.42urduliz.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 14:56:44 by jzuazo            #+#    #+#             */
/*   Updated: 2026/10/24 14:18:14 by jzuazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_digits(long nbr)
{
	int	len;

	len = 0;
	if (nbr >= 10)
		len += ft_print_digits(nbr / 10);
	len += ft_print_char((char)(nbr % 10 + '0'));
	return (len);
}

int	ft_print_nbr(int nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		len += ft_print_char('-');
		len += ft_print_digits((long)nbr * -1);
	}
	else
		len += ft_print_digits(nbr);
	return (len);
}

int	ft_print_unsigned(unsigned int nbr)
{
	return (ft_print_digits(nbr));
}
