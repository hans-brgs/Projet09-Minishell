/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:05:59 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/02/18 10:21:35 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_u(va_list arg)
{
	int				size;
	unsigned int	add;

	size = 0;
	add = va_arg(arg, unsigned int);
	size = ft_putnbr_unsigned_fd (add, 1);
	return (size);
}
