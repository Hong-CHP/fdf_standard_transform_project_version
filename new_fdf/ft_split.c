/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:50:50 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/20 17:07:42 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	count_words(char *str)
{
	int	space;
	int	count;
	int	i;

	i = 0;
	count = 0;
	space = 1;
	while (str[i])
	{
		if (!is_space(str[i]))
		{
			if (space == 1)
			{
				count++;
				space = 0;
			}
		}
		else
			space = 1;
		i++;
	}
	return (count);
}

char	*allocate_copy_tab(int word_len, char *str)
{
	char	*word;
	int		i;

	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_fill_split(char **tab, char *str, int *tab_i)
{
	int	word_len;
	int	i;

	word_len = 0;
	i = 0;
	while (str[i])
	{
		if (is_space(str[i]))
		{
			if (word_len > 0)
			{
				tab[*tab_i] = allocate_copy_tab(word_len, &str[i - word_len]);
				(*tab_i)++;
				word_len = 0;
			}
		}
		else
			word_len++;
		i++;
	}
	if (word_len > 0)
		tab[(*tab_i)++] = allocate_copy_tab(word_len, &str[i - word_len]);
	tab[*tab_i] = NULL;
	return (tab);
}

char	**ft_split(char	const *s)
{
	char	**tab;
	char	*str;
	int		tab_i;

	tab_i = 0;
	str = (char *)s;
	tab = (char **)malloc((count_words(str) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab = ft_fill_split(tab, str, &tab_i);
	return (tab);
}
