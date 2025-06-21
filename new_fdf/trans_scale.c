/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_scale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:15:46 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/21 09:16:26 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	t_view_calculs(t_point *point, t_vue *view)
{
	double	centre_x;
	double	centre_y;
	double	centre_z;

	centre_x = (view->x_min + view->x_max) / 2;
	centre_y = (view->y_min + view->y_max) / 2;
	centre_z = (view->z_min + view->z_max) / 2;
	point->x -= centre_x;
	point->y -= centre_y;
	point->z -= centre_z;
}

t_point	**translate_3d_to_origin(t_data *data, t_vue *view)
{
	int	row;
	int	col;

	row = 0;
	while (row < data->height)
	{
		col = 0;
		while (col < data->width)
		{
			t_view_calculs(&(data->map[row][col]), view);
			col++;
		}
		row++;
	}
	return (data->map);
}

void	init_val_canonical_cube(double *sx, double *sy, double *sz, t_vue *view)
{
	if (view->x_max - view->x_min != 0)
		*sx = 2.0 / (view->x_max - view->x_min);
	else
		*sx = 1.0;
	if (view->y_max - view->y_min != 0)
		*sy = 2.0 / (view->y_max - view->y_min);
	else
		*sy = 1.0;
	if (view->z_max - view->z_min != 0)
		*sz = 2.0 / (view->z_max - view->z_min);
	else
		*sz = 1.0;
}

t_point	**scale_to_canonical_cube(t_data *data, t_vue *view)
{
	int		row;
	int		col;
	double	s_x;
	double	s_y;
	double	s_z;

	init_val_canonical_cube(&s_x, &s_y, &s_z, view);
	row = 0;
	while (row < data->height)
	{
		col = 0;
		while (col < data->width)
		{
			data->map[row][col].x *= s_x;
			data->map[row][col].y *= s_y;
			data->map[row][col].z *= s_z;
			col++;
		}
		row++;
	}
	return (data->map);
}
