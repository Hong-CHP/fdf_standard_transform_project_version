/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:54:57 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/19 12:05:17 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"
#include "mlx.h"

void	free_map(t_point **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (map[i])
		{
			free(map[i]);
			map[i] = NULL;
		}
		i++;
	}
	free(map);
	map = NULL;
}

//allocated data->map
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

//allocated img_data->mlx img_data->win
int	init_window(t_data *img_data)
{
	img_data->mlx = mlx_init();
    if (!img_data->mlx)
        return (0);
    img_data->win = mlx_new_window(img_data->mlx, WIN_W, WIN_H, "fdf");
    if (!img_data->win)
	{
		mlx_destroy_display(img_data->mlx);
		free(img_data->mlx);
		free(img_data);
        return (0);
	}
	return (1);
}

void	clean_all(t_data *data)
{
	if (data->map && data->height > 0)
	{
		free_map(data->map, data->height);
		data->map = NULL;
	}
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img);
		data->img = NULL;
		data->add = NULL;
	}
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	free(data);
}

//allocated img_data
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
	ft_memset(img_data, 0, sizeof(t_data));
	if (!init_window(img_data))
	{	
		free(img_data);
		return (1);
	}
	ft_display_file_and_draw(file, img_data);
	add_event_listener(img_data);
	clean_all(img_data);
    return (0);
}
