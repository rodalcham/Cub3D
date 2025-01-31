/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:45 by rchavez           #+#    #+#             */
/*   Updated: 2024/10/10 14:46:35 by mbankhar         ###   ########.fr       */
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
	double				current_time;
	static double		previous_time = 0.0;
	static const double	frame_time = 1.0 / 30.0;

	current_time = mlx_get_time();
	if (current_time - previous_time >= frame_time)
	{
		previous_time = current_time;
		return (1);
	}
	return (0);
}

void	err(char *str)
{
	if (!str)
		return ;
	while (*str)
		write(2, str++, 1);
}

void	cur_hook(double xpos, double ypos, void *tcub)
{
	static t_cub	*cub = NULL;
	static t_fixed	delta = 0;
	int				i;

	i = -1;
	if (!delta)
		delta = f_div(int_to_fixed(FOV), int_to_fixed(RAY_NBR));
	if (!cub)
		cub = (t_cub *)tcub;
	if (xpos > WIDTH / 2)
	{
		cub->p->angle = normalize(cub->p->angle + int_to_fixed(TURN));
	}
	else if (xpos < WIDTH / 2)
	{
		cub->p->angle = normalize(cub->p->angle - int_to_fixed(TURN));
	}
	if (ypos)
		ypos = 0;
	while (++i < RAY_NBR)
		cub->p->view[i].angle = normalize(cub->p->angle
				+ f_mult(delta, int_to_fixed(i - RAY_NBR / 2)));
	mlx_set_mouse_pos(cub->win, WIDTH / 2, HEIGHT / 2);
}
