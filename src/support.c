/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:02:36 by lkarlon-          #+#    #+#             */
/*   Updated: 2019/04/28 23:21:07 by lkarlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

double	f_part(double x)
{
	return (x - (int)x);
}

int		set_transp(int color, int transp)
{
	int final;

	final = (transp << 24) | color;
	return (final);
}

void	ft_error(char *str)
{
	ft_putstr(str);
	exit(1);
}
