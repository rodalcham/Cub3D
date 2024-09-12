/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:16:54 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/12 10:13:03 by rchavez          ###   ########.fr       */
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

int	line_fill(char *line, t_object *obj)
{
	if (!ft_strncmp(line, "NO", 2))
		obj->north = ft_strdup(line_skip(2, line));
	else if (!ft_strncmp(line, "SO", 2))
		obj->south = ft_strdup(line_skip(2, line));
	else if (!ft_strncmp(line, "EA", 2))
		obj->east = ft_strdup(line_skip(2, line));
	else if (!ft_strncmp(line, "WE", 2))
		obj->west = ft_strdup(line_skip(2, line));
	else if (!ft_strncmp(line, "F", 1))
		obj->floor = ft_strdup(line_skip(1, line));
	else if (!ft_strncmp(line, "C", 1))
		obj->ceiling = ft_strdup(line_skip(1, line));
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
		while (str[i] && is_spc(str[i]))
			i++;
		if (!str[i])
			i--;
	}
	if (count != 3)
		return (-1);
	return (0);
}

int	validate_textures(t_object *obj)
{
	if (!ft_strlen(obj->north) || !ft_strlen(obj->south)
		|| !ft_strlen(obj->east) || !ft_strlen(obj->west)
		|| !ft_strlen(obj->floor) || !ft_strlen(obj->ceiling))
		return (-1);
	if (verify_color(obj->ceiling) || verify_color(obj->floor))
		return (-1);
	return (0);
}

int	extract_textures(t_object *obj, int fd)
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
		i += line_fill(&line[j], obj);
		free_t(line);
		if (i < 6)
			line = get_next_line(fd);
	}
	if (i < 6)
		return (-1);
	return (validate_textures(obj));
}

int	obj_init(t_object *obj, t_cub *cub, char *path)
{
	int		fd;

	obj->ceiling = NULL;
	obj->floor = NULL;
	obj->north = NULL;
	obj->south = NULL;
	obj->east = NULL;
	obj->west = NULL;
	if (ft_strlen(path) < 5 || ft_strcmp(&path[ft_strlen(path) - 4], ".cub"))
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (extract_textures(obj, fd) < 0)
		return (destroy_obj(*obj), -1);
	if (extract_grid(cub, fd) < 0)
		return (destroy_obj(*obj), -1);
	close(fd);
	return (0);
}

void	destroy_obj(t_object obj)
{
	free_t(obj.north);
	free_t(obj.south);
	free_t(obj.west);
	free_t(obj.east);
	free_t(obj.floor);
	free_t(obj.ceiling);
}
