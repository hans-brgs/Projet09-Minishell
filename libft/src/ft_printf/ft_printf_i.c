/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:05:34 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/02/18 10:18:28 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_i(va_list arg)
{
	int	size;
	int	add;

	size = 0;
	add = va_arg(arg, int);
	size = ft_putnbr_fd (add, 1);
	return (size);
}
