/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:54:52 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/12 10:02:55 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_cub *cub, int x, int y, char d)
{
	cub->p->p.x = int_to_fixed(y);
	cub->p->p.y = int_to_fixed(x);
	cub->p->p.plane = cub->map;
	if (d == 'N')
		cub->p->angle = int_to_fixed(Q2);
	else if (d == 'S')
		cub->p->angle = int_to_fixed(Q4);
	else if (d == 'E')
		cub->p->angle = int_to_fixed(Q1);
	else if (d == 'W')
		cub->p->angle = int_to_fixed(Q3);
}