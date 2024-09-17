/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:49:34 by mbankhar          #+#    #+#             */
/*   Updated: 2024/09/17 16:33:44 by mbankhar         ###   ########.fr       */
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

// void	texture_to_image(t_object *object)
// {
// 	object->east_image = mlx_texture_to_image(object->mlxpointer,
// 			object->east_texture);
// 	if (!object->east_image)
// 		write(1, "Error converting east tex to img", 33);
// 	object->west_image = mlx_texture_to_image(object->mlxpointer,
// 			object->west_texture);
// 	if (!object->west_image)
// 		write(1, "Error converting west tex to img", 33);
// 	object->north_image = mlx_texture_to_image(object->mlxpointer,
// 			object->north_texture);
// 	if (!object->north_image)
// 		write(1, "Error converting north tex to img", 32);
// 	object->south_image = mlx_texture_to_image(object->mlxpointer,
// 			object->south_texture);
// 	if (!object->south_image)
// 		write(1, "Error converting south tex to img", 32);
// }

void draw_walls(t_crash crash, t_cub cub, int x)
{
	double	corrected_distance = fixed_to_double(crash.distance);
	int		wall_height = (int)(HEIGHT / corrected_distance);
	int		wall_start = HEIGHT / 2 - wall_height / 2;
	int		wall_end = wall_start + wall_height;
	int		y;

	if (corrected_distance <= 0) 
		corrected_distance = 1;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end >= HEIGHT)
		wall_end = HEIGHT - 1;
	y = 0;
	while (y < HEIGHT)
	{
		if (y >= wall_start && y < wall_end && crash.dir == 'N')
			mlx_put_pixel(cub.img[1], x, y, 424242);
		else if (y >= wall_start && y < wall_end && crash.dir == 'S')
			mlx_put_pixel(cub.img[1], x, y, 02550);
		else if (y >= wall_start && y < wall_end && crash.dir == 'E')
			mlx_put_pixel(cub.img[1], x, y, 25500);
		else if (y >= wall_start && y < wall_end && crash.dir == 'W')
			mlx_put_pixel(cub.img[1], x, y, 2552550);
		else
			mlx_put_pixel(cub.img[1], x, y, 1);
		y++;
	}
}

