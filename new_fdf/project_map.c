/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:38:41 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/21 09:16:22 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso_calculs(t_point *point, double rad)
{
	point->res_x = (point->x - point->y) * cos(rad) * 0.5;
	point->res_y = ((point->x + point->y) * sin(rad) - point->z * 0.2) * 0.5;
}

t_point	**iso_project(t_data *data)
{
	int		row;
	int		col;
	double	rad;

	row = 0;
	rad = deg_to_rad();
	while (row < data->height)
	{
		col = 0;
		while (col < data->width)
		{
			iso_calculs(&(data->map[row][col]), rad);
			col++;
		}
		row++;
	}
	return (data->map);
}

t_point	**view_tranform(t_data *data, t_point **map)
{
	int		row;
	int		col;
	double	screenx;
	double	screeny;

	row = 0;
	while (row < data->height)
	{
		col = 0;
		while (col < data->width)
		{
			screenx = (map[row][col].res_x + 1) * (WIN_W / 2) * 0.8;
			map[row][col].screen_x = (int)round(screenx + WIN_H * 0.1);
			// map[row][col].screen_x = (int)round((map[row][col].res_x + 1) * (WIN_W / 2) * 0.8 + WIN_H * 0.1);
			screeny = (map[row][col].res_y + 1) * (WIN_H / 2) * 0.8;
			map[row][col].screen_y = (int)round(screeny + WIN_H * 0.1);
			// map[row][col].screen_y = (int)round((map[row][col].res_y + 1) * (WIN_H / 2) * 0.8 + WIN_H * 0.1);
			col++;
		}
		row++;
	}
	return (map);
}

t_vue	project_map(t_data *data)
{
	t_vue	view;

	find_max_min_val(data, &view);
	translate_3d_to_origin(data, &view);
	scale_to_canonical_cube(data, &view);
	iso_project(data);
	view_tranform(data, data->map);
	return (view);
}
