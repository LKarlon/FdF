/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_net.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 17:47:34 by lkarlon-          #+#    #+#             */
/*   Updated: 2019/04/28 22:56:41 by lkarlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_point		new_point(int x, int y, int z)
{
	t_point point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

void		iso(t_point point, t_point *changed, t_win *win, int z)
{
	int		previous_x;
	int		previous_y;

	previous_x = point.x + 600 + win->params.x_corr;
	previous_y = point.y + win->params.y_corr;
	changed->x = (previous_x - previous_y) * cos(0.523599);
	changed->y = -(point.z * win->params.size * win->params.z_corr)
	+ (previous_x + previous_y) * sin(0.523599);
	changed->z = z;
}

void		print_iso(t_win *win)
{
	int		v;
	int		h;
	t_point	changed_s;
	t_point	changed_e;

	v = -1;
	while (++v < win->hight && (h = -1))
	{
		while (++h < win->widh)
		{
			if (h < win->widh - 1)
			{
				iso(win->map[v][h], &changed_s, win, win->map[v][h].z);
				iso(win->map[v][h + 1], &changed_e, win, win->map[v][h + 1].z);
				fdf(win, changed_s, changed_e);
			}
			if (v < win->hight - 1)
			{
				iso(win->map[v][h], &changed_s, win, win->map[v][h].z);
				iso(win->map[v + 1][h], &changed_e, win, win->map[v + 1][h].z);
				fdf(win, changed_s, changed_e);
			}
		}
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}

void		print(t_win *win)
{
	int		v;
	int		h;

	v = 0;
	while (v < win->hight)
	{
		h = 0;
		while (h < win->widh)
		{
			if (h < win->widh - 1)
				fdf(win, win->map[v][h], win->map[v][h + 1]);
			if (v < win->hight - 1)
				fdf(win, win->map[v][h], win->map[v + 1][h]);
			h++;
		}
		v++;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}

t_point		**build_net(char **coords, int count, int c_words, t_win *win)
{
	int		v;
	int		h;
	int		x;
	t_point **map;

	v = 0;
	map = (t_point**)malloc(sizeof(t_point) * count);
	while (v < count)
	{
		h = 0;
		x = 0;
		map[v] = (t_point*)malloc(sizeof(t_point) * c_words);
		while (h < c_words)
		{
			map[v][h] = new_point(!h ? 1 : h * (win->params.size + 1) + 1,
			!v ? 1 : v * (win->params.size + 1) + 1, ft_atoi(&coords[v][x]));
			while (coords[v][x] != ' ' && coords[v][x] != '\0')
				x++;
			while (coords[v][x] == ' ')
				x++;
			h++;
		}
		v++;
	}
	return (map);
}
