/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:38:41 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/10 20:05:28 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    t_view_calculs(t_point *point, t_vue *view)
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

t_point    **translate_3d_to_origin(t_data *data, t_vue *view)
{
    int row;
    int col;
    
    row = 0;
    while (row < data->height)
    {
        col = 0;
        while (col < data->width)
        {
            t_view_calculs(&(data->map[row][col]), view);
            // printf("map view to origin: %f, %f, %f\n", map_mview[row][col].x, map_mview[row][col].y, map_mview[row][col].z);
            col++;
        }
        row++;
    }
	return (data->map);
}

t_point **scale_to_canonical_cube(t_data *data, t_vue *view)
{
    int row;
    int col;
    double  s_x;
    double  s_y;
    double  s_z;
    
    s_x = (view->x_max - view->x_min != 0) ? 2.0 / (view->x_max - view->x_min) : 1.0;
    s_y = (view->y_max - view->y_min != 0) ? 2.0 / (view->y_max - view->y_min) : 1.0;
    s_z = (view->z_max - view->z_min != 0) ? 2.0 / (view->z_max - view->z_min) : 1.0;
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

void    iso_calculs(t_point *point, double rad)
{
    point->res_x = (point->x - point->y) * cos(rad) * 0.5;
    point->res_y = ((point->x + point->y) * sin(rad) - point->z * 0.2) * 0.5;
}

t_point    **iso_project(t_data *data)
{
    int row;
    int col;
    double  rad;
    
    row = 0;
    rad = deg_to_rad();
    printf("rad: %f\n", rad);
    while (row < data->height)
    {
        col = 0;
        while (col < data->width)
        {
            iso_calculs(&(data->map[row][col]), rad);
            printf("After iso: (%f, %f)\n", data->map[row][col].res_x, data->map[row][col].res_y);
            col++;
        }
        row++;
    }
    return (data->map);
}

t_point **view_tranform(t_data *data)
{
    int row;
    int col;

    row = 0;
    while (row < data->height)
    {
        col = 0;
        while (col < data->width)
        {
            data->map[row][col].screen_x = (int)round((data->map[row][col].res_x + 1) * (WIN_W / 2) * 0.8 + WIN_H * 0.1);
            data->map[row][col].screen_y = (int)round((data->map[row][col].res_y + 1) * (WIN_H / 2) * 0.8 + WIN_H * 0.1);
            printf("Final screen: (%d, %d)\n", data->map[row][col].screen_x, data->map[row][col].screen_y);
            col++;
        }
        row++;
    }
    return (data->map);
}

t_vue	project_map(t_data *data)
{
    t_vue view;

    find_max_min_val(data, &view);
    translate_3d_to_origin(data, &view);
    scale_to_canonical_cube(data, &view);
    iso_project(data);
    view_tranform(data);
    return (view);
}
