/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:49:34 by mbankhar          #+#    #+#             */
/*   Updated: 2024/09/18 10:23:51 by rchavez          ###   ########.fr       */
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


unsigned int	get_pixel(mlx_texture_t *texture, int hei)
{
	int		ret;
	uint8_t	*temp;
	int		i;

	temp = &texture->pixels[(hei) * sizeof(u_int32_t)];
	ret = 0;
	i = -1;
	while (++i < 4)
	{
		ret = ret << 8;
		if (temp == 0)
			ret = ret | 0;
		else
			ret = ret | temp[i];
	}
	return (ret);
}

unsigned int	get_color(mlx_texture_t	*img, double x, double y)
{
	int	pos;
	int	ret;
	uint8_t	*temp;
	int		i;

	// printf("%f :: %f\n", x, y);
	pos = (int)((((int)(y * img->height)) * img->width) + (x * img->width));
	temp = &img->pixels[pos * sizeof(u_int32_t)];
	ret = 0;
	i = -1;
	while (++i < 4)
	{
		ret = ret << 8;
		if (temp == 0)
			ret = ret | 0;
		else
			ret = ret | temp[i];
	}
	return (ret);
}

void draw_walls(t_crash crash, t_cub cub, int x)
{
	double	corrected_distance = fixed_to_double(crash.distance);
	int		wall_height = (int)(HEIGHT / corrected_distance);
	int		wall_start = HEIGHT / 2 - wall_height / 2;
	int		wall_end = wall_start + wall_height;
	int		y;
	mlx_texture_t	*image;
	double			pixel;

	if (crash.dir == 'N')
		image = cub.wall->north_texture;
	else if (crash.dir == 'S')
		image = cub.wall->south_texture;
	else if (crash.dir == 'E')
		image = cub.wall->east_texture;
	else if (crash.dir == 'W')
		image = cub.wall->west_texture;
	if (corrected_distance <= 0)
		corrected_distance = 1;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end >= HEIGHT)
		wall_end = HEIGHT - 1;
	y = 0;
	if (crash.dir == 'N' || crash.dir == 'S')
		pixel = (fixed_to_double(crash.p.x) - fixed_to_int(crash.p.x));
	if (crash.dir == 'E' || crash.dir == 'W')
		pixel = (fixed_to_double(crash.p.y) - fixed_to_int(crash.p.y));
	while (y < HEIGHT)
	{
		if (y >= wall_start && y < wall_end)
		{
			// mlx_put_pixel(cub.img[1], x, y, get_pixel());
			mlx_put_pixel(cub.img[1], x, y, get_color(image, pixel, (((double)y - wall_start) / wall_height)));
		}
		else
			mlx_put_pixel(cub.img[1], x, y, 0);
		y++;
		// pixel += image->width;
	}
}

