/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:10:45 by mbankhar          #+#    #+#             */
/*   Updated: 2024/09/24 11:00:33 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_check(char **map)
{
	int		x;
	size_t	y;
	int	player_count;

	x = -1;
	player_count = 0;
	while (map[++x])
	{
		y = -1;
		while (++y < ft_strlen(map[x]))
		{
			if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'E' ||
			map[x][y] == 'W')
				player_count++;
		}
	}
	if (player_count != 1)
	{
		return (-1);
	}
	return (1);
}


int	copy_map(char **map, int g, int y)
{
	char	**map_cpy;
	int		x;
	int		rows;
	int		cols;
	int		i;

	rows = strnum(map);
	cols = maxlen(map);
	map_cpy = malloc_t(sizeof(char *) * (rows + 1));
	map_cpy[rows] = NULL;
	x = -1;
	while (map[++x])
		map_cpy[x] = ft_strdup(map[x]);
	if (flood_fill2(map_cpy, g, y, rows, cols) == 1)
	{
		i = -1;
		while (map_cpy[++i])
			free_t(map_cpy[i]);
		free_t(map_cpy);
		return (1);
	}
	i = -1;
	while (map_cpy[++i])
		free_t(map_cpy[i]);
	free_t(map_cpy);
	return (-1);
}

int	flood_fill2(char **map, int x, int y, int rows, int cols)
{
	if (x < 0 || y < 0 || x >= rows || y >= cols
		|| map[x][y] == '1' || map[x][y] == 'V')
		return (1);
	if ((x == 0 || y == 0 || x == rows - 1
			|| y == cols - 1) && map[x][y] != '1')
		return (-1);
	map[x][y] = 'V';
	if (flood_fill2(map, x - 1, y, rows, cols) == -1
		|| flood_fill2(map, x + 1, y, rows, cols) == -1
		|| flood_fill2(map, x, y - 1, rows, cols) == -1
		|| flood_fill2(map, x, y + 1, rows, cols) == -1)
	{
		return (-1);
	}

	return 1;
}
