/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:13:14 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/07/23 17:41:32 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	0 -> empty space
//	1 -> floor & ceiling
//	2 -> Wall
//	3 -> Invalid

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	if	(!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	free_chars(char **chars)
{
	int	i;

	i = -1;
	if (!chars)
		return ;
	while (chars[++i])
		free_t(chars[i]);
	free_t(chars);
}

char	**add_str(char **old, char *new)
{
	char	**ret;
	int		size;
	int		i;

	i = 0;
	if (!old)
		size = 0;
	else
	{
		while (old[i])
			i++;
		size = i;
	}
	i = 0;
	ret = (char **)malloc_t(sizeof(char *) * (size + 2));
	if (!ret)
		return (free_chars(old), free_t(new), NULL);
	while (old && old[i])
	{
		ret[i] = old[i];
		i++;
	}
	ret[i] = new;
	ret[++i] = NULL;
	return (free_t(old), ret);
}

char	**extract_chars(int fd)
{
	char	*line;
	char	**ret;

	ret = NULL;
	line = get_next_line(fd);
	while (line && !ft_strcmp(line, "\n"))
	{
		free_t(line);
		line = get_next_line(fd);
	}
	if (!line)
		return (NULL);
	while (line && ft_strcmp(line, "\n"))
	{
		ret = add_str(ret, line);
		if (!ret)
			return (NULL);
		line = get_next_line(fd);
	}
	if (line)
		free_t(line);
	return (ret);
}

int	extract_grid(t_cub *map, int fd)
{
	char	**chars;
	int		width;
	int		heigth;
	int		i;

	chars = extract_chars(fd);
	if (!chars)
		return (-1);
	width = 0;
	heigth = 0;
	while (chars[width])
	{
		i = ft_strlen(chars[width]);
		if (i > heigth)
			heigth = i;
		width++;
	}
	map->width = width;
	map->heigth = heigth;
	map->grid = chars;
	return (0);
}
