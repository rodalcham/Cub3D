/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:43:23 by mbankhar          #+#    #+#             */
/*   Updated: 2024/10/04 15:57:39 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_gun(t_object *object, t_cub *cub)
{
	object->gun_texture = mlx_load_png("./textures/gun1.png");
	if (!object->gun_texture)
	{
		write (2, "Error loading gun\n", 28);
		return (1);
	}
	object->gun_image = mlx_texture_to_image(cub->win, object->gun_texture);
	if (!object->gun_image)
	{
		write(1, "Error converting gun tex to img", 32);
		return (1);
	}
	return (0);
}

void	draw_gun(t_object *object, t_cub *cub)
{
	int	gun_x;
	int	gun_y;

	gun_x = (1200 / 2) - (object->gun_image->width / 2);
	gun_y = 800 - object->gun_image->height;
	mlx_image_to_window(cub->win, object->gun_image, gun_x, gun_y);
}

void	free_gun(t_object obj, t_cub cub)
{
	if (obj.gun_texture)
		mlx_delete_texture(obj.gun_texture);
	if (obj.gun_image)
		mlx_delete_image(cub.win, obj.gun_image);
}

t_fixed	relative_x(u_int32_t x, t_cub *cub)
{
	t_fixed	ret;
	double	temp;

	temp = x;
	temp = temp * cub->map->width / (cub->img[0]->width * 2);
	ret = double_to_fixed(temp);
	ret += cub->p->p.x / 2;
	return (ret);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
