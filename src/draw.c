/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 22:09:24 by lkarlon-          #+#    #+#             */
/*   Updated: 2019/04/28 22:42:53 by lkarlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	coords_rev(t_coords *curr)
{
	curr->x1 += curr->x0;
	curr->x0 = curr->x1 - curr->x0;
	curr->x1 -= curr->x0;
	curr->y1 += curr->y0;
	curr->y0 = curr->y1 - curr->y0;
	curr->y1 -= curr->y0;
	curr->xc = curr->x0;
	curr->yc = curr->y0;
}

int		s_l(t_coords *curr, double iter, int a)
{
	int res;

	if (a)
		res = set_transp(get_color(*curr), (int)(f_part(iter) * 255));
	else
		res = set_transp(get_color(*curr), (int)(255 - f_part(iter) * 255));
	return (res);
}

void	draw_line(t_win *win, t_point map_s, t_point map_e)
{
	if (map_s.x == map_e.x)
		while (map_s.y <= map_e.y)
		{
			if (map_s.y >= 0 && map_s.y < H &&
			map_e.x >= 0 && map_e.x < W)
			{
				win->addr[(map_e.x + win->params.x_corr) +
				W * (map_s.y + win->params.y_corr)] = 0xff0000;
			}
			map_s.y++;
		}
	else if (map_s.y == map_e.y)
		while (map_s.x <= map_e.x)
		{
			if (map_s.x >= 0 && map_s.x < W &&
			map_e.y >= 0 && map_e.y < H)
			{
				win->addr[(map_s.x + win->params.x_corr) +
				W * (map_e.y + win->params.y_corr)] = 0xff0000;
			}
			map_s.x++;
		}
}

void	draw_iterx(t_win *win, t_coords *c, double grad)
{
	double	i;

	i = (c->y0 > c->y1) ? c->y0 + grad : c->y0 - grad;
	if (c->y0 > c->y1)
		while (c->xc <= c->x1)
		{
			if (c->xc >= 0 && c->xc <= W && (int)i < H && ((int)i - 1) >= 0)
			{
				win->addr[(int)c->xc + W * (int)i] = s_l(c, i, 0);
				win->addr[(int)c->xc + W * ((int)i - 1)] = s_l(c, i, 1);
			}
			i = (c->yc > c->y1) ? i - grad : i + grad;
			c->xc++;
		}
	else
		while (c->xc <= c->x1)
		{
			if (c->xc >= 0 && c->xc < W && (int)i >= 0 && ((int)i + 1 < H))
			{
				win->addr[(int)c->xc + W * (int)i] = s_l(c, i, 1);
				win->addr[(int)c->xc + W * ((int)i + 1)] = s_l(c, i, 0);
			}
			i = (c->yc > c->y1) ? i - grad : i + grad;
			c->xc++;
		}
}

void	draw_itery(t_win *win, t_coords *c, double grad)
{
	double	i;

	i = (c->x0 > c->x1) ? c->x0 - grad : c->x0 + grad;
	if (c->x0 > c->x1)
		while (c->yc <= c->y1)
		{
			if (c->yc >= 0 && c->yc < H && ((int)i - 1) >= 0 && (int)i < W)
			{
				win->addr[(int)i + W * c->yc] = s_l(c, i, 0);
				win->addr[((int)i - 1) + W * c->yc] = s_l(c, i, 1);
			}
			i = (c->xc > c->x1) ? i - grad : i + grad;
			c->yc++;
		}
	else
		while (c->yc <= c->y1)
		{
			if (c->yc >= 0 && c->yc < H && ((int)i + 1) < W && (int)i >= 0)
			{
				win->addr[(int)i + W * c->yc] = s_l(c, i, 1);
				win->addr[((int)i + 1) + W * c->yc] = s_l(c, i, 0);
			}
			i = (c->xc > c->x1) ? i - grad : i + grad;
			c->yc++;
		}
}
