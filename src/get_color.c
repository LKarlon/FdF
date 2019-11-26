/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:08:16 by lkarlon-          #+#    #+#             */
/*   Updated: 2019/04/27 19:30:12 by lkarlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		ft_abs(int i)
{
	return (i < 0 ? i * -1 : i);
}

double	percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int		get_color(t_coords curr)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (curr.color_start == curr.color_end)
		return (curr.color_start);
	if (ft_abs(curr.x1 - curr.x0) > ft_abs(curr.y1 - curr.y0))
		percentage = percent(curr.x0, curr.x1, curr.xc);
	else
		percentage = percent(curr.y0, curr.y1, curr.yc);
	red = get_light((curr.color_start >> 16) & 0xFF,
	(curr.color_end >> 16) & 0xFF, percentage);
	green = get_light((curr.color_start >> 8) & 0xFF,
	(curr.color_end >> 8) & 0xFF, percentage);
	blue = get_light(curr.color_start & 0xFF,
	curr.color_end & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
