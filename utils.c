/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:45 by rchavez           #+#    #+#             */
/*   Updated: 2024/09/18 11:38:23 by rchavez          ###   ########.fr       */
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
	static int	i = 0;
	const int	frame_time = 3;

	i++;
	if (i == frame_time)
	{
		i = 0;
		return (1);
	}
	else
		return (0);
}

