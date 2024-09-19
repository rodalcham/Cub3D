/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:16:54 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/19 11:21:57 by rchavez          ###   ########.fr       */
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
		if (!str[i] || !ft_isdigit(str[i]))
			return (-1);
		count++;
		while (str[i] && ft_isdigit(str[i]))
			i++;
		while (str[i] && is_spc(str[i]))
			i++;
		if (str[i] && str[i] != ',' && str[i] != ';' && str[i] != ':'
			&& str[i] != '-')
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
