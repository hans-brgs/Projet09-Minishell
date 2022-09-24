/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x_up.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:03:07 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/03/20 15:48:39 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_x_up(va_list arg)
{
	int				size;
	unsigned int	hex_up;

	size = 0;
	hex_up = (unsigned int)va_arg(arg, int);
	size = ft_putnbr_base_fd(hex_up, "0123456789ABCDEF", 1);
	return (size);
}
