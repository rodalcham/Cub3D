/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:10:45 by mbankhar          #+#    #+#             */
/*   Updated: 2024/09/21 15:23:05 by rchavez@stu      ###   ########.fr       */
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
	int	i = -1;
	while (map[++i])
	{
		// printf("%s\n", map[i]);
	}
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
		// printf("%d\n", player_count);
		return (-1);
	}
	return (1);
}

int	copy_map(char **map, t_player player)
{
	char	**map_cpy;
	int		x;
	int		rows;
	int		cols;

	rows = strnum(map);
	cols = maxlen(map);
	map_cpy = malloc_t(sizeof(char *) * rows + 1);
	map_cpy[rows] = NULL;
	x = -1;
	while (map[++x])
		map_cpy[x] = ft_strdup(map[x]);
	if (flood_fill2(map_cpy, player, rows, cols))
		return (1);
	return (-1);
}


int	flood_fill2(char **map, t_player player, int rows, int cols)
{
	int	x;
	int	y;

	x = player.p.x;
	y = player.p.y;
	if (x < 0 || y < 0 || x >= rows || y >= cols || map[x][y] == '1' ||
		map[x][y] == 'V')
		return (1);
	if (x == 0 || y == 0 || x == rows - 1 || y == cols - 1)
		return (-1);
	map[x][y] = 'V';
	flood_fill2(map, (t_player){.p.x = x - 1, .p.y = y,}, rows, cols);
	flood_fill2(map, (t_player){.p.x = x + 1, .p.y = y}, rows, cols);
	flood_fill2(map, (t_player){.p.x = x, .p.y = y - 1}, rows, cols);
	flood_fill2(map, (t_player){.p.x = x, .p.y = y + 1}, rows, cols);

	return (1);
}



