/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:45 by rchavez           #+#    #+#             */
/*   Updated: 2024/09/19 11:41:16 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_fixed	normalize(t_fixed angle)
{
	while (angle >= int_to_fixed(Q5))
		angle -= int_to_fixed(Q5);
	while (angle < int_to_fixed(Q1))
		angle += int_to_fixed(Q5);
	return (angle);
}

void	pcopy(t_point *dst, t_point src)
{
	dst->x = src.x;
	dst->y = src.y;
	dst->plane = src.plane;
}

int	frame_function(void)
{
	static double		previous_time = 0.0;
	double				current_time;
	static const double	frame_time = 1.0 / 30.0;

	current_time = mlx_get_time();
	if (current_time - previous_time >= frame_time)
	{
		previous_time = current_time;
		return (1);
	}
	return (0);
}
