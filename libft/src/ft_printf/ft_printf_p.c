/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:05:48 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/02/18 10:18:14 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_p(va_list arg)
{
	int		size;
	void	*add;

	size = 0;
	add = va_arg(arg, void *);
	if (add == 0)
	{
		size += ft_putstr_fd("0x0", 1);
		return (size);
	}
	size += ft_putstr_fd("0x", 1);
	size += ft_putnbr_base_fd((unsigned long int)add, "0123456789abcdef", 1);
	return (size);
}
