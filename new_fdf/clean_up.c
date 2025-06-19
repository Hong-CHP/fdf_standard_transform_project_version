/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:15:33 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/19 13:05:45 by hporta-c         ###   ########.fr       */
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
