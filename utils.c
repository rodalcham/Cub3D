/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:45 by rchavez           #+#    #+#             */
/*   Updated: 2024/09/16 14:28:57 by rchavez          ###   ########.fr       */
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