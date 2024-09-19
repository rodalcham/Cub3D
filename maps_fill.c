/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:13:14 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/19 11:22:30 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
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
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
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
	char	**str;
	int		x;
	int		y;

	str = extract_chars(fd);
	if (!str)
		return (-1);
	map->map = build_plane(str, 0, 0);
	if (!map->map)
		return (free_chars(str), -1);
	x = -1;
	while (++x < map->map->heigth)
	{
		y = -1;
		while (++y < map->map->width && y < (int)ft_strlen(str[x]))
		{
			if (str[x][y] == '1')
				map->map->grid[y][x] = map->wall;
			else if (str[x][y] == 'N' || str[x][y] == 'E'
				|| str[x][y] == 'E' || str[x][y] == 'W')
				init_player(map, x, y, str[x][y]);
		}
	}
	return (0);
}
