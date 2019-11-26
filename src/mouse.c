/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:07:57 by lkarlon-          #+#    #+#             */
/*   Updated: 2019/04/29 01:07:43 by lkarlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/fdf.h"

void	update_net(t_point **map, int count, int c_words, t_win *win)
{
	int		v;
	int		h;

	v = 0;
	while (v < count)
	{
		h = 0;
		while (h < c_words)
		{
			map[v][h] = new_point(!h ? 1 : h * (win->params.size + 1) + 1,
			!v ? 1 : v * (win->params.size + 1) + 1, map[v][h].z);
			h++;
		}
		v++;
	}
}

void	scale(int key, t_win *win)
{
	if (key == 5 && win->params.size - 1 <= 0)
		return ;
	ft_bzero(win->addr, H * W * 4);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	if (key == 5)
	{
		win->params.size -= 1;
		update_net(win->map, win->hight, win->widh, win);
		print_iso(win);
	}
	if (key == 4)
	{
		win->params.size += 1;
		update_net(win->map, win->hight, win->widh, win);
		print_iso(win);
	}
}

int		mouse_check(int key, int x, int y, t_win *win)
{
	int v;
	int	h;

	h = x;
	v = y;
	if (key == 4 || key == 5)
		scale(key, win);
	return (0);
}

void	k(t_point point, t_point *changed, t_win *win, int z)
{
	int		previous_x;
	int		previous_y;

	previous_x = point.x + 600;
	previous_y = point.y + 600;
	changed->x = previous_x - previous_y / 2;
	changed->y = previous_y / 2 - z;
	changed->z = z;
}

void	print_k(t_win *win)
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
				k(win->map[v][h], &changed_s, win, win->map[v][h].z);
				k(win->map[v][h + 1], &changed_e, win, win->map[v][h + 1].z);
				fdf(win, changed_s, changed_e);
			}
			if (v < win->hight - 1)
			{
				k(win->map[v][h], &changed_s, win, win->map[v][h].z);
				k(win->map[v + 1][h], &changed_e, win, win->map[v + 1][h].z);
				fdf(win, changed_s, changed_e);
			}
		}
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}
