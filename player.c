/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:54:52 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/19 11:26:19 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_cub *cub, int x, int y, char d)
{
	int		i;
	t_fixed	delta;

	cub->p->p.x = int_to_fixed(y);
	cub->p->p.y = int_to_fixed(x);
	cub->p->p.plane = cub->map;
	if (d == 'N')
		cub->p->angle = int_to_fixed(Q4);
	else if (d == 'S')
		cub->p->angle = int_to_fixed(Q2);
	else if (d == 'E')
		cub->p->angle = int_to_fixed(Q1);
	else if (d == 'W')
		cub->p->angle = int_to_fixed(Q3);
	i = -1;
	delta = f_div(int_to_fixed(FOV), int_to_fixed(RAY_NBR));
	while (++i < RAY_NBR)
	{
		cub->p->view[i].src = &cub->p->p;
		cub->p->view[i].angle = normalize(cub->p->angle
				+ f_mult(delta, int_to_fixed(i - RAY_NBR / 2)));
	}
}

int	player_access(t_fixed x, t_fixed y, t_plane *plane)
{
	t_point	arr[8];

	arr[0] = (t_point){x, y + 5214, plane};
	arr[1] = (t_point){x, y - 5214, plane};
	arr[2] = (t_point){x + 5214, y, plane};
	arr[3] = (t_point){x - 5214, y, plane};
	arr[4] = (t_point){x + 3536, y + 3536, plane};
	arr[5] = (t_point){x + 3536, y - 3536, plane};
	arr[6] = (t_point){x - 3536, y + 3536, plane};
	arr[7] = (t_point){x - 3536, y - 3536, plane};
	if (paccess(arr[0]) || paccess(arr[1]) || paccess(arr[2])
		|| paccess(arr[3]) || paccess(arr[4]) || paccess(arr[5])
		|| paccess(arr[6]) || paccess(arr[7]))
		return (1);
	return (0);
}
