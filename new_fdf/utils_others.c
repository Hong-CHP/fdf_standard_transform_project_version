/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:17:02 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/10 20:05:21 by hporta-c         ###   ########.fr       */
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