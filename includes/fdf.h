/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:19:48 by lkarlon-          #+#    #+#             */
/*   Updated: 2019/04/29 01:10:51 by lkarlon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../src/libft/libft.h"
# include "fdf_prms.h"
# include "../minilibx_macos/mlx.h"

typedef struct	s_coords
{
	int x0;
	int x1;
	int y0;
	int y1;
	int xc;
	int yc;
	int color_start;
	int color_end;
}				t_coords;

typedef struct	s_point
{
	int		x;
	int		y;
	float	z;
	int		color;
}				t_point;

typedef struct	s_params
{
	int		hight;
	int		widh;
	int		x_corr;
	int		y_corr;
	float	z_corr;
	int		size;
}				t_params;

typedef struct	s_win
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			*img_ptr;
	int			*addr;
	char		**coords;
	t_point		**map;
	int			hight;
	int			widh;
	t_params	params;
}				t_win;

int				get_color(t_coords curr);
int				get_next_line(const int fd, char **line);
t_point			**build_net(char **coords, int count, int c_words, t_win *win);
void			draw_line(t_win *win, t_point map_s, t_point map_e);
void			draw_iterx(t_win *win, t_coords *curr, double grad);
void			draw_itery(t_win *win, t_coords *curr, double grad);
void			coords_rev(t_coords *curr);
void			iso(t_point point, t_point	*changed, t_win *win, int z);
void			print_iso(t_win *win);
void			fdf(t_win *win, t_point map_s, t_point map_e);
void			print(t_win *win);
int				key_check(int key, t_win *win);
int				mouse_check(int key, int x, int y, t_win *win);
double			f_part(double x);
int				set_transp(int color, int transp);
t_point			new_point(int x, int y, int z);
void			ft_error(char *str);
void			print_k(t_win *win);

#endif
