/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:16:26 by rchavez           #+#    #+#             */
/*   Updated: 2024/09/24 10:47:58 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	obj->north_texture = NULL;
	obj->south_texture = NULL;
	obj->east_texture = NULL;
	obj->west_texture = NULL;
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
	if (obj.north_texture)
		mlx_delete_texture(obj.north_texture);
	if (obj.east_texture)
		mlx_delete_texture(obj.east_texture);
	if (obj.west_texture)
		mlx_delete_texture(obj.west_texture);
	if (obj.south_texture)
		mlx_delete_texture(obj.south_texture);
}
