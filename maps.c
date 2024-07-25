/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:16:54 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/07/25 10:33:43 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_spc(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

char	*line_skip(size_t toskip, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && i < toskip)
		i++;
	while (line[i] && is_spc(line[i]))
		i++;
	return (&line[i]);
}

int	line_fill(char *line, t_cub *map)
{
	if (!ft_strncmp(line, "NO", 2))
		map->north = ft_strdup(line_skip(2, line));
	else if (!ft_strncmp(line, "SO", 2))
		map->south = ft_strdup(line_skip(2, line));
	else if (!ft_strncmp(line, "EA", 2))
		map->east = ft_strdup(line_skip(2, line));
	else if (!ft_strncmp(line, "WE", 2))
		map->west = ft_strdup(line_skip(2, line));
	else if (!ft_strncmp(line, "F", 1))
		map->floor = ft_strdup(line_skip(1, line));
	else if (!ft_strncmp(line, "C", 1))
		map->ceiling = ft_strdup(line_skip(1, line));
	else
		return (0);
	return (1);
}

int	verify_color(char *str)
{
	size_t	i;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) && ++i)
		{
			count++;
			if (ft_isdigit(str[i]))
				i++;
			if (ft_isdigit(str[i]))
				i++;
		}
		else
			return (-1);
		while (str[i] && is_spc(str[i]))
			i++;
		if (str[i] && str[i] != ',' && str[i] != ';' && str[i] != ':' && str[i] != '-')
			return (-1);
		printf("\nDEBUG\n");
		while (str[i] && is_spc(str[i]))
			i++;
		if (!str[i])
			i--;
	}
	if (count != 3)
		return (-1);
	return (0);
}
int	validate_textures(t_cub *map)
{
	if (!ft_strlen(map->north) || !ft_strlen(map->south)
		|| !ft_strlen(map->east) || !ft_strlen(map->west)
		|| !ft_strlen(map->floor) || !ft_strlen(map->ceiling))
		return (-1);
	if (verify_color(map->ceiling) || verify_color(map->floor))
		return (-1);
	return (0);
}

int	extract_textures(t_cub *map, int fd)
{
	int		i;
	size_t	j;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (i < 6 && line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		j = -1;
		while (line[++j] && is_spc(line[j]))
			j++;
		i += line_fill(&line[j], map);
		free_t(line);
		line = get_next_line(fd);
	}
	if (i < 6)
		return (-1);
	return (validate_textures(map));
}

int	cub_init(t_cub *map, char *path)
{
	int		fd;

	map->ceiling = NULL;
	map->floor = NULL;
	map->north = NULL;
	map->south = NULL;
	map->east = NULL;
	map->west = NULL;
	map->grid = NULL;
	if (ft_strlen(path) < 5 || ft_strcmp(&path[ft_strlen(path) - 4], ".cub"))
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (extract_textures(map, fd) < 0)
		return (destroy_cub(*map), -1);
	if (extract_grid(map, fd) < 0)
		return (destroy_cub(*map), -1);
	close(fd);
	return (0);
}

void	destroy_cub(t_cub map)
{
	free_t(map.north);
	free_t(map.south);
	free_t(map.west);
	free_t(map.east);
	free_chars(map.grid);
}
