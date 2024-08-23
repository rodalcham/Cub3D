/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:36:37 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/07/31 09:55:57 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	normalize(float angle)
{
	if (angle < 0)
		return (2 + angle);
	if (angle > 2)
		return (angle - 2);
	return (angle);
}

void	draw_pillar(float distance, float raynbr, mlx_image_t *img)
{
	if (distance && img)
		printf("\nray : %f\n", raynbr);
}

void	cast_ray(t_player p, float delta, t_cub map, mlx_t *win, mlx_image_t *img)
{
	int	prev[2];
	float	curr[2];
	float	distance;

	curr[0] = p.x;
	curr[1] = p.y;
	prev[0] = (int) curr[0];
	prev[1] = (int) curr[1];
	distance = 0;
	while (1)
	{
		if (map.grid[(int) curr[0]][(int) curr[1]] == '1' && win)
		{
			draw_pillar(distance, normalize(delta - (p.delta - (FOV / 2))) / OFFSET, img);
			return ;
		}
		curr[0] += sin(delta * M_PI) * STEP;
		curr[1] += cos(delta * M_PI) * STEP;
		distance += STEP;
	}
}
