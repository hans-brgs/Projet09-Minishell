/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:47:42 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/17 13:47:42 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_dup_matrix(char **mat)
{
	int		len;
	char	**dup;

	len = 0;
	while (mat && mat[len])
		len++;
	dup = ft_calloc(len + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	len = 0;
	while (mat[len])
	{
		dup[len] = ft_strdup(mat[len]);
		if (!dup[len])
		{
			ft_free_array(dup);
			return (NULL);
		}
		len++;
	}
	return (dup);
}
