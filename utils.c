/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:45 by rchavez           #+#    #+#             */
/*   Updated: 2024/09/18 14:11:48 by mbankhar         ###   ########.fr       */
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


// int	frame_function(void)
// {
// 	static int	i = 0;
// 	const int	frame_time = 3;

// 	i++;
// 	if (i == frame_time)
// 	{
// 		i = 0;
// 		return (1);
// 	}
// 	else
// 		return (0);
// }


int	frame_function(void)
{
	static double	previous_time = 0.0;
	double			current_time;
	double			delta_time;
	double			frame_time;

	frame_time = 1.0 / 30.0;
	current_time = mlx_get_time();
	delta_time = current_time - previous_time;
	if (delta_time >= frame_time)
	{
		previous_time = current_time;
		return (1);
	}

	return (0);
}
