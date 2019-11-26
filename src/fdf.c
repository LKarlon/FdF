/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:27:01 by lkarlon-          #+#    #+#             */
/*   Updated: 2019/04/29 01:27:51 by lkarlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/fdf.h"

void		is_valid(t_win *win, int count)
{
	int v;
	int h;

	v = 0;
	win->widh = ft_count_words(win->coords[0], ' ');
	while (v < count)
	{
		h = 0;
		if ((int)ft_count_words(win->coords[v], ' ') != win->widh)
		{
			ft_error("Map error\n");
		}
		while (win->coords[v][h])
		{
			if (!ft_strchr(SYM, win->coords[v][h]))
				ft_error("Map error\n");
			h++;
		}
		v++;
	}
}

t_coords	*curr_init(t_point map_s, t_point map_e)
{
	t_coords *curr;

	curr = (t_coords*)malloc(sizeof(t_coords));
	curr->x0 = map_s.x;
	curr->x1 = map_e.x;
	curr->y0 = map_s.y;
	curr->y1 = map_e.y;
	curr->xc = curr->x0;
	curr->yc = curr->y0;
	if (map_s.z != map_e.z)
	{
		curr->color_start = 0xed0000;
		curr->color_end = 0x047f00;
	}
	else
	{
		curr->color_start = 0xed0000;
		curr->color_end = 0xed0000;
	}
	return (curr);
}

t_win		*win_init(char *s, int count)
{
	t_win		*win;
	int			size;
	int			endian;
	int			bits;

	win = (t_win*)malloc(sizeof(t_win));
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, W, H, s);
	win->img_ptr = (int*)mlx_new_image(win->mlx_ptr, W, H);
	win->addr = (int*)mlx_get_data_addr(win->img_ptr, &bits, &size, &endian);
	win->coords = malloc(sizeof(char**) * (count));
	win->params.hight = H;
	win->params.widh = W;
	win->params.x_corr = 0;
	win->params.y_corr = 0;
	win->params.z_corr = 1;
	win->params.size = NET;
	win->hight = count;
	return (win);
}

void		fdf(t_win *win, t_point map_s, t_point map_e)
{
	int			dx;
	int			dy;
	double		grad;
	t_coords	*curr;

	curr = curr_init(map_s, map_e);
	dx = (map_e.x > map_s.x) ? (map_e.x - map_s.x) : (map_s.x - map_e.x);
	dy = (map_e.y > map_s.y) ? (map_e.y - map_s.y) : (map_s.y - map_e.y);
	if (dx == 0 || dy == 0)
		draw_line(win, map_s, map_e);
	else if (dy < dx)
	{
		if (map_e.x < map_s.x)
			coords_rev(curr);
		grad = (double)dy / dx;
		draw_iterx(win, curr, grad);
	}
	else
	{
		if (map_e.y < map_s.y)
			coords_rev(curr);
		grad = (double)dx / dy;
		draw_itery(win, curr, grad);
	}
	free(curr);
}

int			main(int argc, char **argv)
{
	int			fd;
	t_win		*win;
	char		*str;
	int			i;
	int			count;

	i = 0;
	count = 0;
	if (argc != 2)
		ft_error("Not correct count of arguments\n");
	fd = open((*(argv + 1)), O_RDONLY);
	while (get_next_line(fd, &str) && ++count)
		free(str);
	close(fd);
	win = win_init("A nu ka, zaczeni!", count);
	fd = open((*(argv + 1)), O_RDONLY);
	while (get_next_line(fd, &win->coords[i]))
		i++;
	is_valid(win, count);
	win->map = build_net(win->coords, count, win->widh, win);
	print(win);
	mlx_key_hook(win->win_ptr, key_check, win);
	mlx_mouse_hook(win->win_ptr, mouse_check, win);
	mlx_loop(win->mlx_ptr);
}
