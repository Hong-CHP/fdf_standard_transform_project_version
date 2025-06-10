/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:33:42 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/10 16:17:25 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"

void    free_split(char **str_split)
{
    int i;
    
    i = 0;
    while(str_split[i])
    {
        free(str_split[i]);
        i++;
    }
    free(str_split);
    str_split = NULL;
}

int	count_lines(char *file)
{
	char	*line;
	int		count;
	int		fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	if (!line)
		return (-1);
    while (line)
    {
		count++;
        free(line);
        line = get_next_line(fd);
    }
	close(fd);
	return (count);
}

int	count_cols(char **line_split)
{
	int	count;

	count = 0;
	while (line_split[count])
		count++;
	return (count);
}

void	fill_map(t_point **map, char **line_split, int y, int width)
{
	int i;
	
    map[y] = malloc(sizeof(t_point) * width);
	if (!map[y])
		return ;
	i = 0;
	while (i < width)
	{
		map[y][i].x = i;
		map[y][i].y = y;
		map[y][i].color = -1;
		if (pre_colored(line_split[i]))
			if_color(&map[y][i], line_split[i]);
		if (!line_split[i])
			map[y][i].z = 0;
		else
			map[y][i].z = (double)ft_atoi(line_split[i]);
		map[y][i].org_z = map[y][i].z;
		// printf("map origin: %f, %f, %f, %d\n", map[y][i].x, map[y][i].y, map[y][i].z, map[y][i].color);
		i++;
	}
}

t_point	**recup_points_data(int fd, t_data *data)
{
	int	y;
	t_point **map;
	char	*line;
	char	**line_split;
	int		expected_w;

	map = (t_point **)malloc(data->height * sizeof(t_point *));
	if (!map)
		return (NULL);
	y = 0;
	expected_w = -1;
	line = get_next_line(fd);
	while (line && y < data->height)
	{
		line_split = ft_split(line);
        data->width = count_cols(line_split);
		if (expected_w == -1)
			expected_w = data->width;
		else if (data->width != expected_w)
			data->width = expected_w;
		fill_map(map, line_split, y, data->width);
        free_split(line_split);
		free(line);
        line = get_next_line(fd);
		y++;
	}
	return (map);
}
