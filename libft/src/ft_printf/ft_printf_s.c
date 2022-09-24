/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:05:56 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/02/18 10:20:46 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_s(va_list arg)
{
	int		size;
	char	*str;

	size = 0;
	str = va_arg(arg, char *);
	if (str == NULL)
	{
		size += ft_putstr_fd("(null)", 1);
		return (size);
	}
	while (*str)
	{
		size += write(1, str, 1);
		str++;
	}
	return (size);
}
