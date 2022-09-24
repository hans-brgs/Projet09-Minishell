/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:59:43 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/02/18 10:15:58 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_c(va_list arg)
{
	int		size;
	char	c;

	size = 0;
	c = va_arg(arg, int);
	size = write(1, &c, 1);
	return (size);
}
