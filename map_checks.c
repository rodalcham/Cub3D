/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:10:45 by mbankhar          #+#    #+#             */
/*   Updated: 2024/09/19 12:40:08 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_check(char **map)
{
	int	x;
	int	y;
	int	player_x;
	int	player_y;
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
		return (0);
	return (1);
}

void	copy_map(char **map, t_player player)
{
	char	**map_cpy;
	int		x;
	int		y;

	x = 0;
	while (map[x])
		x++;
	map_cpy = malloc_t(sizeof(char *) * x +1);
	map_cpy[x + 1] = '\0';
	x = -1;
	while (map[++x])
		map_cpy[x] = ft_strdup(map[x]);
	flood_fill(map_cpy, player);
}


int	flood_fill(char **map, t_player player)
{
	int	x;
	int	y;
	int	rows;
	int	cols;

	rows = 0;
	cols = 0;
	x = player.p.x;
	y = player.p.y;
	while (map[rows])
		rows++;
	cols = ft_strlen(map[0]);
	if (x < 0 || y < 0 || x >= rows || y >= cols || map[x][y] == '1' ||
		map[x][y] == 'V')
		return (0);
	if (x == 0 || y == 0 || x == rows - 1 || y == cols - 1)
		return (0);
	map[x][y] = 'V';
	flood_fill(map, (t_player){.p.x = x - 1, .p.y = y});
	flood_fill(map, (t_player){.p.x = x + 1, .p.y = y});
	flood_fill(map, (t_player){.p.x = x, .p.y = y - 1});
	flood_fill(map, (t_player){.p.x = x, .p.y = y + 1});

	return (1);
}



