/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:56:40 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/19 11:48:38 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_r(int h_color)
{
	return ((h_color >> 16) & 0xFF);
}

int	get_g(int h_color)
{
	return ((h_color >> 8) & 0xFF);
}

int	get_b(int h_color)
{
	return (h_color & 0xFF);
}

int	ft_gradient(int s_color, int e_color, double percent)
{
	int a;
	int	r;
	int	g;
	int	b;

	r = (int)round((1 - percent) * get_r(s_color) + percent * get_r(e_color));
	g = (int)round((1 - percent) * get_g(s_color) + percent * get_g(e_color));
	b = (int)round((1 - percent) * get_b(s_color) + percent * get_b(e_color));
	a = e_color & (0xFF << 24);
	return (a << 24 | r << 16 | g << 8 | b);
}

int     get_color(t_point *point, t_vue *view)
{
	double	percent;
	double	threshold;
	
	if (point->color != -1)
        return (point->color);
	threshold = view->z_max - view->z_min;
	if (threshold == 0)
		return (0x432371);
	percent = (point->org_z - view->z_min) / threshold;
    if (percent <= 0.2)
        return (0x0000FF);
    else if (percent <= 0.4)
        return (0x00FF00);
    else if (percent <= 0.6)
        return (0x00FFFF);
    else if (percent <= 0.8)
        return (0xFFFF00);   
    else
        return (0xFFFFFF);
}
