/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x_low.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:02:49 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/02/18 10:23:49 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_x_low(va_list arg)
{
	int				size;
	unsigned int	hex_low;

	size = 0;
	hex_low = (unsigned int)va_arg(arg, int);
	size = ft_putnbr_base_fd (hex_low, "0123456789abcdef", 1);
	return (size);
}
