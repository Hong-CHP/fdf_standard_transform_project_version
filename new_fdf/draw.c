/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:10:29 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/21 08:45:44 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int	gradient_color(int dst, int i, t_point s, t_point e)
{
	double	percent;
	int		color;

	if (dst == 0.0)
		percent = 0.0;
	else
		percent = (double)i / (double)dst;
	color = ft_gradient(s.color, e.color, percent);
	return (color);
}

t_draw	*init_t_draw_val(t_draw *d_line, t_point s, t_point e)
{
	d_line->dx = ft_abs(e.screen_x - s.screen_x);
	d_line->dy = ft_abs(e.screen_y - s.screen_y);
	if (e.screen_x - s.screen_x > 0 )
		d_line->sx = 1;
	else
		d_line->sx = -1;
	if (e.screen_y - s.screen_y > 0 )
		d_line->sy = 1;
	else
		d_line->sy = -1;
	d_line->err = 0;
	return (d_line);
}

void	high_slope(t_data *data, t_point s, t_point e)
{
	t_draw	y_line;
	int		i;
	int		color;

	init_t_draw_val(&y_line, s, e);
	i = 0;
	while (s.screen_y != e.screen_y)
	{
		color = gradient_color(y_line.dy, i, s, e);
		put_pixel(data, s.screen_x, s.screen_y, color);
		y_line.err += y_line.dx;
		if (2 * y_line.err >= y_line.dy)
		{
			s.screen_x += y_line.sx;
			y_line.err -= y_line.dy;
		}
		s.screen_y += y_line.sy;
		i++;
	}
	put_pixel(data, s.screen_x, s.screen_y, e.color);
}

void	low_slope(t_data *data, t_point s, t_point e)
{
	int		i;
	t_draw	x_line;
	int		color;

	init_t_draw_val(&x_line, s, e);
	i = 0;
	while (s.screen_x != e.screen_x)
	{
		color = gradient_color(x_line.dx, i, s, e);
		put_pixel(data, s.screen_x, s.screen_y, color);
		x_line.err += x_line.dy;
		if (2 * x_line.err >= x_line.dx)
		{
			s.screen_y += x_line.sy;
			x_line.err -= x_line.dx;
		}
		s.screen_x += x_line.sx;
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
