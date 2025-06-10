/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:54:57 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/10 17:02:09 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"
#include "mlx.h"

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
}

//malloc in func recup_points_data need to be free at last of program
// isometric_project(data);
void    ft_display_file_and_draw(char *file, t_data *data)
{   
    int fd;

	data->height = count_lines(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		clean_all(data);
		exit(1);
	}
	data->map = recup_points_data(fd, data);
	if ((data->height < 2 && data->width < 2) || !data->map)
	{
		clean_all(data);
		close(fd);
		exit(1);
	}
	data->img = mlx_new_image(data->mlx, WIN_W, WIN_H);
    data->add = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
	draw_bgc(data);
	draw_map(data);
    close(fd);
}

void	init_window(t_data *img_data)
{
	img_data->mlx = mlx_init();
    if (!img_data->mlx)
        return ;
    img_data->win = mlx_new_window(img_data->mlx, WIN_W, WIN_H, "fdf");
    if (!img_data->win)
	{
		mlx_destroy_display(img_data->mlx);
		free(img_data->mlx);
		free(img_data);
        return ;
	}
}

void	clean_all(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->map)
		free_map(data);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data);
}

int main(int argc, char *argv[])
{
    char    *file;
	t_data	*img_data;

    if (argc != 2)
        return (1);
    file = argv[1];
	img_data = malloc(sizeof(t_data));
	if (!img_data)
		return (1);
	init_window(img_data);
	ft_display_file_and_draw(file, img_data);
	add_event_listener(img_data);
	clean_all(img_data);
    return (0);
}
