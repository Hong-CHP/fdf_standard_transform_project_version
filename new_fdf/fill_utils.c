/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 08:49:24 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/23 17:59:29 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"

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

int	gradient_color(int dst, int i, t_point s, t_point e)
{
	double	percent;
	int		color;

	if (dst == 0.0)
		percent = 0.0;
	else
		percent = (double)i / (double)dst;
	color = ft_gradient(s.color, e.color, percent);
	return (color);
}
