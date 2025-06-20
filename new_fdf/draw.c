/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:10:29 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/20 17:04:11 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int	gradient_color(int dst, int i, t_point s, t_point e)
{
	double	percent;
	int		color;

	percent = (dst == 0.0) ? 0.0 : (double)i / (double)dst;
	color = ft_gradient(s.color, e.color, percent);
	return (color);
}

void	high_slope(t_data *data, t_point s, t_point e)
{
	t_draw	d_line;
	int		i;
	int		color;

	d_line.dx = ft_abs(e.screen_x - s.screen_x);
	d_line.dy = ft_abs(e.screen_y - s.screen_y);
	d_line.sx = (e.screen_x - s.screen_x > 0 ) ? 1 : -1;
	d_line.sy = (e.screen_y - s.screen_y > 0 ) ? 1 : -1;
	d_line.err = 0;
	i = 0;
	while (s.screen_y != e.screen_y)
	{
		color = gradient_color(d_line.dy, i, s, e);
		put_pixel(data, s.screen_x, s.screen_y, color);
		d_line.err += d_line.dx;
		if (2 * d_line.err >= d_line.dy)
		{
			s.screen_x += d_line.sx;
			d_line.err -= d_line.dy;
		}
		s.screen_y += d_line.sy;
		i++;
	}
	put_pixel(data, s.screen_x, s.screen_y, e.color);
}

void	low_slope(t_data *data, t_point s, t_point e)
{
	int		i;
	t_draw	d_line;
	int		color;

	d_line.dx = ft_abs(e.screen_x - s.screen_x);
	d_line.dy = ft_abs(e.screen_y - s.screen_y);
	d_line.sx = (e.screen_x - s.screen_x > 0 ) ? 1 : -1;
	d_line.sy = (e.screen_y - s.screen_y > 0 ) ? 1 : -1;
	d_line.err = 0;
	i = 0;
	while (s.screen_x != e.screen_x)
	{
		color = gradient_color(d_line.dx, i, s, e);
		put_pixel(data, s.screen_x, s.screen_y, color);
		d_line.err += d_line.dy;
		if (2 * d_line.err >= d_line.dx)
		{
			s.screen_y += d_line.sy;
			d_line.err -= d_line.dx;
		}
		s.screen_x += d_line.sx;
		i++;
	}
	put_pixel(data, s.screen_x, s.screen_y, e.color);
}

void	draw_line_bresenham(t_data *data, t_point *s, t_point *e)
{
	s->color = get_color(s, &(data->view));
	e->color = get_color(e, &(data->view));
	if (ft_abs(e->screen_y - s->screen_y) == 0
		&& ft_abs(e->screen_x - s->screen_x) == 0)
	{
		put_pixel(data, s->screen_x, s->screen_y, s->color);
		return ;
	}
	if (ft_abs(e->screen_y - s->screen_y) <= ft_abs(e->screen_x - s->screen_x))
		low_slope(data, *s, *e);
	else
		high_slope(data, *s, *e);
}

void	draw_map(t_data *data)
{
	int		row;
	int		col;
	t_point	point;

	data->view = project_map(data);
	row = 0;
	while (row < data->height)
	{
		col = 0;
		while (col < data->width)
		{
			point = data->map[row][col];
			if (col < data->width - 1)
				draw_line_bresenham(data, &point, &(data->map[row][col + 1]));
			if (row < data->height - 1)
				draw_line_bresenham(data, &point, &(data->map[row + 1][col]));
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
