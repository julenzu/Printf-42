/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzuazo <jzuazo@student.42urduliz.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 14:05:28 by jzuazo            #+#    #+#             */
/*   Updated: 2026/10/24 14:17:22 by jzuazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_conversion_type(char character, va_list ap)
{
	int	len;

	len = 0;
	if (character == 'c')
		len += ft_print_char(va_arg(ap, int));
	else if (character == 's')
		len += ft_print_str(va_arg(ap, char *));
	else if (character == 'p')
		len += ft_print_ptr(va_arg(ap, void *));
	else if (character == 'd' || character == 'i')
		len += ft_print_nbr(va_arg(ap, int));
	else if (character == 'u')
		len += ft_print_unsigned(va_arg(ap, unsigned int));
	else if (character == 'x')
		len += ft_print_hex(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (character == 'X')
		len += ft_print_hex(va_arg(ap, unsigned int), "0123456789ABCDEF");
	if (character == '%')
		len += ft_print_char('%');
	return (len);
}

int	ft_printf(char const *format, ...)
{
	va_list	ap;
	int		len;
	int		i;

	if (!format)
		return (-1);
	len = 0;
	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			len += ft_conversion_type(format[i + 1], ap);
			i += 2;
		}
		else
		{
			len += ft_print_char(format[i]);
			i++;
		}
	}
	va_end(ap);
	return (len);
}
