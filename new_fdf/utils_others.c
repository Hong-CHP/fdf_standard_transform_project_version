/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:17:02 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/19 11:48:47 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double  deg_to_rad(void)
{
    double pi;
    double degree;
    double  radian;

    pi = 3.14159265;
    degree = 30.0;
    radian = degree * (pi / 180.0);
    return (radian);
}

void    *ft_memset(void *s, int c, int n)
{
    char    *p;
    int     i;
    char    ch;
    
    p = (char *)s;
    ch = (char)c;
    i = 0;
    while (i < n)
    {
        p[i] = ch;
        i++;
    }
    return ((void *)p);
}

int	parse_color(char *str)
{
	int	res;
	int	value;
	int	i;
	
	res = 0;
	i = 0;
	if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			value = str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			value = str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			value = str[i] - 'A' + 10;
		else
			break;
		res = res * 16 + value;
		i++;
	}
	return (res);
}

void	if_color(t_point *point, char *str)
{
	int	i;
	char	*s_color;
	
	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			s_color = &str[i + 1];
			point->color = parse_color(s_color);
			break;
		}
		i++;
	}
}

int	pre_colored(char *str)
{
	int	k;
	k = 0;
	
	while (str[k])
	{
		if (str[k] == ',')
			return (1);
		k++;
	}
	return (0);
}

// void	free_map_view(t_point **map_view, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->height)
// 	{
// 		free(map_view[i]);
// 		i++;
// 	}
// 	free(map_view);
// 	map_view = NULL;
// }

// t_point **allocate_map_view(t_data *data)
// {
//     t_point **map_mview;
// //map is malloc need to be free after used
//     int row;
    
//     row = 0;
//     map_mview = malloc(sizeof(t_point *) * data->height);
// 	if (!map_mview)
// 		return (NULL);
//     while (row < data->height)
//     {
//         map_mview[row] = malloc(sizeof(t_point) * data->width);
// 		if (!map_mview[row])
//         {
//             while (--row >= 0)
//                 free(map_mview[row]);
//             free(map_mview);
//             return (NULL);
//         }
//         row++;
//     }
//     return (map_mview);
// }