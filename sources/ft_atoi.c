/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 03:34:16 by sarayapa          #+#    #+#             */
/*   Updated: 2025/09/17 19:38:28 by sarayapa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *n)
{
	int		neg;
	long	i;
	int		res;

	i = 0;
	res = 0;
	neg = 1;
	while (n[i] == 32 || (n[i] >= 9 && n[i] <= 13))
	{
		i++;
	}
	if (n[i] == '-' || n[i] == '+')
		neg = 44 - n[i++];
	while (ft_isdigit(n[i]) && n[i])
	{
		res = (res * 10) + (n[i] - '0');
		i++;
	}
	return (res * neg);
}
