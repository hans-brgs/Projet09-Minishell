/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 08:23:29 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/02/18 10:12:53 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	write_args(char c, va_list arg)
{
	int	size;

	size = 0;
	if (c == 'c')
		size += ft_printf_c(arg);
	else if (c == 's')
		size += ft_printf_s(arg);
	else if (c == 'p')
		size += ft_printf_p(arg);
	else if (c == 'd')
		size += ft_printf_d(arg);
	else if (c == 'i')
		size += ft_printf_i(arg);
	else if (c == 'u')
		size += ft_printf_u(arg);
	else if (c == 'x')
		size += ft_printf_x_low(arg);
	else if (c == 'X')
		size += ft_printf_x_up(arg);
	else if (c == '%')
		size += ft_printf_per();
	else
		return (0);
	return (size);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		size;

	size = 0;
	va_start(arg, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			size += write_args(str[0], arg);
		}
		else
			size += write(1, str, 1);
		str++;
	}
	va_end(arg);
	return (size);
}
