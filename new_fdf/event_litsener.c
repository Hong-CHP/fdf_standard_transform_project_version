/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_litsener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:43:19 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/19 11:56:23 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int	expose_handler(void *param)
{
	t_data *data;
    
    data = (t_data *)param;
	draw_map(data);
	return (0);
}

int keybroad_handler(int keycode, void *param)
{
	t_data *data;
    
    data = (t_data *)param;
    if (keycode == 65307)
	{
		clean_all(data);
		exit(0);
	}
	return (0);
}

int mouse_handler(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	(void)param;
	
    if (button == 1)
		fflush(stdout);
	return (0);
}

int	close_window(void *param)
{
	t_data *data;
    
    data = (t_data *)param;
	clean_all(data);
	exit(0);
}

void    add_event_listener(t_data *img_data)
{
    mlx_expose_hook(img_data->win, expose_handler, img_data);
    mlx_key_hook(img_data->win, keybroad_handler, img_data);
    mlx_mouse_hook(img_data->win, mouse_handler, img_data);
	mlx_hook(img_data->win, 17, 0, close_window, img_data);
	mlx_loop_hook(img_data->mlx, NULL, NULL);
    mlx_loop(img_data->mlx);
}