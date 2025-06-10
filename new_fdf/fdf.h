/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:54:40 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/10 16:35:25 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line.h"
# include <math.h>

# define WIN_W 1000
# define WIN_H 800
# define BGC_COLOR 0x1A1A1D

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	res_x;
	double	res_y;
	int		screen_x;
	int		screen_y;
	double	org_z;
	int	color;
}				t_point;

typedef struct s_vue
{
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	z_min;
	double	z_max;
	// double radian;
}				t_vue;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*add;
	int		bpp;
	int		line_len;
	int		endian;
	t_point **map;
	int		height;
	int		width;
	t_vue	view;
}				t_data;

void	free_map_view(t_point **map_view, t_data *data);
int		ft_atoi(const char *str);
double  deg_to_rad(void);
int		ft_min(int a, int b);
int		ft_abs(int nb);
int     get_color(t_point *point, t_vue *view);
void    find_max_min_val(t_data *data, t_vue *view);
char	**ft_split(char	const *s);
int		count_lines(char *file);
int	pre_colored(char *str);
void	if_color(t_point *point, char *str);
t_point	**recup_points_data(int fd, t_data *data);
// t_point	**project_map(t_data *data, t_point **map_mview);
t_vue	project_map(t_data *data);
t_point    **translate_3d_to_origin(t_data *data, t_vue *view);
// t_point    **translate_3d_to_origin(t_data *data, t_point **map_tview, t_vue *view);
int	ft_gradient(int s_color, int e_color, double percent);
// t_vue	isometric_project(t_data *data);
// t_vue    projection_3d_to_res(t_data *data);
void	put_pixel(t_data *data, int x, int y, int color);
void    draw_bgc(t_data *data);
// t_point **allocate_map_view(t_data *data);
void    draw_map(t_data *data);
void    add_event_listener(t_data *img_data);
void	clean_all(t_data *data);

#endif