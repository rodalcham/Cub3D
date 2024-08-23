/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:54:52 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/07/31 09:53:58 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player *get_player(void)
{
	static t_player	player;

	return (&player);
}

void	draw_fov(t_player p, t_cub map, mlx_t *win, mlx_image_t *img)
{
	float	start;
	float	end;
	

	start = p.delta - (FOV / 2);
	end = p.delta + (FOV / 2);
	while (start <= end)
	{
		cast_ray(p, start, map, win, img);
		start += OFFSET;
	}
}