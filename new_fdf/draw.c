/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:10:29 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/11 12:19:20 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void    high_slope(t_data *data, t_point s, t_point e)
{
    int err;
    int dx;
    int dy;
    int sx;
    int sy;
    int i;
    double percent;
    
    dx = ft_abs(e.screen_x - s.screen_x);
    dy = ft_abs(e.screen_y - s.screen_y);
    sx = (e.screen_x - s.screen_x > 0 ) ? 1 : -1;
    sy = (e.screen_y - s.screen_y > 0 ) ? 1 : -1;
    err = 0;
    i = 0;
    while (s.screen_y != e.screen_y)
    {
        percent = (dy == 0.0) ? 0.0 : (double)i / (double)dy;
        int color = ft_gradient(s.color, e.color, percent);
        put_pixel(data, s.screen_x, s.screen_y, color);
        err += dx;
        if (2 * err >= dy)
        {
            s.screen_x += sx;
            err -= dy;
        }
        s.screen_y += sy;
        i++;
    }
    put_pixel(data, s.screen_x, s.screen_y, e.color);
}

void    low_slope(t_data *data, t_point s, t_point e)
{
    int err;
    int dx;
    int dy;
    int sx;
    int sy;
    int i;
    double percent;
    
    dx = ft_abs(e.screen_x - s.screen_x);
    dy = ft_abs(e.screen_y - s.screen_y);
    sx = (e.screen_x - s.screen_x > 0 ) ? 1 : -1;
    sy = (e.screen_y - s.screen_y > 0 ) ? 1 : -1;
    err = 0;
    i = 0;
    while (s.screen_x != e.screen_x) 
    {
        percent = (dx == 0) ? 0.0 : (double)i / (double)dx;
        int color = ft_gradient(s.color, e.color, percent);
        put_pixel(data, s.screen_x, s.screen_y, color);
        err += dy;
        if (2 * err >= dx)
        {
            s.screen_y += sy;
            err -= dx;
        }
        s.screen_x += sx;
        i++;
    }
    put_pixel(data, s.screen_x, s.screen_y, e.color);
}

void    draw_line_bresenham(t_data *data, t_point *s, t_point *e)
{
    s->color = get_color(s, &(data->view));
    e->color = get_color(e, &(data->view));
    if (ft_abs(e->screen_y - s->screen_y) == 0
    && ft_abs(e->screen_x - s->screen_x) == 0)
    {
        put_pixel(data, s->screen_x, s->screen_y, s->color);
        return ;
    }
    if(ft_abs(e->screen_y - s->screen_y) <= ft_abs(e->screen_x - s->screen_x))
        low_slope(data, *s, *e);
    else
        high_slope(data, *s, *e);
}

void    draw_map(t_data *data)
{
    int row;
    int col;
    
    data->view = project_map(data);
    row = 0;
    while (row < data->height)
    {
        col = 0;
        while (col < data->width)
        {
            if (col < data->width - 1)
                draw_line_bresenham(data, &(data->map[row][col]), &(data->map[row][col + 1]));
            if (row < data->height - 1)
                draw_line_bresenham(data, &(data->map[row][col]), &(data->map[row + 1][col]));
            col++;
        }
        row++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}