/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:49:34 by mbankhar          #+#    #+#             */
/*   Updated: 2024/09/17 11:15:26 by mbankhar         ###   ########.fr       */
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
	object->east_image = mlx_texture_to_image()
}