/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:40:04 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/10 17:47:05 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"

void	find_x_max_min_val(t_data *data, t_vue *view)
{
	int	i;
	int	j;
	double	min;
	double	max;

	min = data->map[0][0].x;
	max = data->map[0][0].x;
	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (min > data->map[i][j].x)
				min = data->map[i][j].x;
			if (max < data->map[i][j].x)
				max = data->map[i][j].x;
			j++;
		}
		i++;
	}
	view->x_max = max;
	view->x_min = min;
}

void	find_y_max_min_val(t_data *data, t_vue *view)
{
	int	i;
	int	j;
	double	min;
	double	max;

	min = data->map[0][0].y;
	max = data->map[0][0].y;
	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (min > data->map[i][j].y)
				min = data->map[i][j].y;
			if (max < data->map[i][j].y)
				max = data->map[i][j].y;
			j++;
		}
		i++;
	}
	view->y_max = max;
	view->y_min = min;
}

void	find_z_max_min_val(t_data *data, t_vue *view)
{
	int	i;
	int	j;
	double	min;
	double	max;

	min = data->map[0][0].z;
	max = data->map[0][0].z;
	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (min > data->map[i][j].z)
				min = data->map[i][j].z;
			if (max < data->map[i][j].z)
				max = data->map[i][j].z;
			j++;
		}
		i++;
	}
	view->z_max = max;
	view->z_min = min;
}

void    find_max_min_val(t_data *data, t_vue *view)
{
	if (data->height < 2 || data->width < 2 || !data->map)
		return ;
    find_x_max_min_val(data, view);
    find_y_max_min_val(data, view);
    find_z_max_min_val(data, view);
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	flag;

	nb = 0;
	flag = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			flag *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10;
		nb = nb + (*str - '0');
		str++;
	}
	return (nb * flag);
}