/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:49:34 by mbankhar          #+#    #+#             */
/*   Updated: 2024/09/17 13:38:09 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_object *object)
{
	object->east_texture = mlx_load_png("textures/walls/08.png");
	if (!object->east_texture)
		write (1, "Error loading east texture", 27);
	object->west_texture = mlx_load_png("textures/walls/12.png");
	if (!object->east_texture)
		write (1, "Error loading east texture", 27);
	object->north_texture = mlx_load_png("textures/walls/30.png");
	if (!object->east_texture)
		write (1, "Error loading east texture", 27);
	object->south_texture = mlx_load_png("textures/walls/39.png");
	if (!object->east_texture)
		write (1, "Error loading east texture", 27);
}

void	texture_to_image(t_object *object)
{
	object->east_image = mlx_texture_to_image(object->mlxpointer,
			object->east_texture);
	if (!object->east_image)
		write(1, "Error converting east tex to img", 33);
	object->west_image = mlx_texture_to_image(object->mlxpointer,
			object->west_texture);
	if (!object->west_image)
		write(1, "Error converting west tex to img", 33);
	object->north_image = mlx_texture_to_image(object->mlxpointer,
			object->north_texture);
	if (!object->north_image)
		write(1, "Error converting north tex to img", 32);
	object->south_image = mlx_texture_to_image(object->mlxpointer,
			object->south_texture);
	if (!object->south_image)
		write(1, "Error converting south tex to img", 32);
}

// typedef	struct crash_s
// {
// 	void		*obj;
// 	t_point		p;
// 	t_fixed		distance;
// 	char		dir;
// }				t_crash;
void	draw_walls(t_object object, t_crash crash, t_player player, t_cub cub)
{
    for (int x = 0; x < WIDTH; x++)
	{
		float ray_angle = player.angle - FOV / 2 + (float)x / (float)WIDTH * FOV;
		float corrected_distance = crash.distance * cos(ray_angle - player.angle);
		int wall_height = (int)(HEIGHT / corrected_distance);
		int wall_start = HEIGHT / 2 - wall_height / 2;
		int wall_end = wall_start + wall_height;
		for (int y = wall_start; y < wall_end; y++)
		{
			mlx_put_pixel(cub.img[1], x, y, "#FF0000");
		}
	}
}
