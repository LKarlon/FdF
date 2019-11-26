/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:35:08 by lkarlon-          #+#    #+#             */
/*   Updated: 2019/04/29 00:56:22 by lkarlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/fdf.h"

void	push_img(t_win *win, int key)
{
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	if (key == 126)
	{
		win->params.y_corr -= 5 * NET;
		win->params.x_corr -= 5 * NET;
		print_iso(win);
	}
	if (key == 125)
	{
		win->params.y_corr += 5 * NET;
		win->params.x_corr += 5 * NET;
		print_iso(win);
	}
	if (key == 123)
	{
		win->params.x_corr -= 5 * NET;
		win->params.y_corr += 5 * NET;
		print_iso(win);
	}
	if (key == 124)
	{
		win->params.x_corr += 5 * NET;
		win->params.y_corr -= 5 * NET;
		print_iso(win);
	}
}

void	z_scale(t_win *win, int key)
{
	ft_bzero(win->addr, H * W * 4);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	if (key == 27)
	{
		win->params.z_corr -= 0.1;
		print_iso(win);
	}
	if (key == 24)
	{
		win->params.z_corr += 0.1;
		print_iso(win);
	}
}

int		key_check(int key, t_win *win)
{
	if (key == 53)
		exit(0);
	if (key == 34)
	{
		ft_bzero(win->addr, H * W * 4);
		mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
		win->params.x_corr = 0;
		win->params.y_corr = 0;
		print_iso(win);
		mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	}
	if (key == 126 || key == 125 || key == 123 || key == 124)
	{
		ft_bzero(win->addr, H * W * 4);
		push_img(win, key);
	}
	if (key == 27 || key == 24)
		z_scale(win, key);
	if (key == 40)
	{
		ft_bzero(win->addr, H * W * 4);
		mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
		print_k(win);
	}
	return (0);
}
