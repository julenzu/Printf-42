/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzuazo <jzuazo@student.42urduliz.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 14:57:02 by jzuazo            #+#    #+#             */
/*   Updated: 2026/10/24 14:26:04 by jzuazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned long n, char *base)
{
	int	len;

	len = 0;
	if (n >= 16)
		len += ft_print_hex(n / 16, base);
	len += ft_print_char(base[n % 16]);
	return (len);
}

int	ft_print_ptr(void *ptr)
{
	int	len;

	len = 0;
	if (!ptr)
		return (ft_print_str("(nil)"));
	len += ft_print_str("0x");
	len += ft_print_hex((unsigned long)ptr, "0123456789abcdef");
	return (len);
}
