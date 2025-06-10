/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:09:22 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/10 14:24:23 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	else
		return (nb);
}

int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void    ft_bzero(void *s, size_t n)
{
    size_t  i;
    char    *p;

    p = (char *)s;
    i = 0;
    while (i < n)
    {
        p[i] = '\0';
        i++;
    }
    return ;
}

void	put_pixel(t_data *data, int x, int y, int color)
{
    char *dst;
    
    if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
        return;
    dst = data->add + y * data->line_len + x * (data->bpp / 8);
    *(unsigned int *)dst = color;
}

void    draw_bgc(t_data *data)
{
    int x;
    int y;

    ft_bzero(data->add, data->height * data->width * (data->bpp / 8));
    y = 0;
    while (y < WIN_H)
    {
        x = 0;
        while (x < WIN_W)
        {
            put_pixel(data, x, y, BGC_COLOR);
            x++;
        }
        y++;
    }
}