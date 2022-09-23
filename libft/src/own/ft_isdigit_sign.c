/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_sign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:28:27 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/19 13:28:27 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isdigit_sign(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c == '-' || c == '+')
		return (1);
	else
		return (0);
}

int	ft_isnum_sign(char *num)
{
	int	i;

	i = 0;
	if (!num)
		return (0);
	while (num[i])
	{
		if (i == 0 && ft_isdigit_sign(num[i]) == 0)
			return (0);
		else if (i > 0 && ft_isdigit(num[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
