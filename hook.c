/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:12:11 by rchavez           #+#    #+#             */
/*   Updated: 2024/09/12 15:33:47 by rchavez          ###   ########.fr       */
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

void	check_angles(mlx_key_data_t key, t_cub *cub)
{
	t_fixed delta = double_to_fixed(FOV / RAY_NBR);
	int i;

	i = -1;
	if (key.key == MLX_KEY_RIGHT)
		cub->p->angle = normalize(cub->p->angle - int_to_fixed(TURN));
	else if (key.key == MLX_KEY_LEFT)
		cub->p->angle = normalize(cub->p->angle + int_to_fixed(TURN));
	while (++i < RAY_NBR)
		cub->p->view[i].angle = cub->p->angle + f_mult(delta, double_to_fixed(i - RAY_NBR / 2));
}

void	check_wasd(mlx_key_data_t key, t_cub *cub)
{
	t_point	temp;

	pcopy(&temp, cub->p->p);
	if (key.key == MLX_KEY_W)
		temp.y -= f_mult(double_to_fixed(STEP), f_sin(cub->p->angle));
	else if (key.key == MLX_KEY_S)
		temp.y += double_to_fixed(STEP);
	else if (key.key == MLX_KEY_A)
		temp.x -= double_to_fixed(STEP);
	else if (key.key == MLX_KEY_D)
		temp.x += double_to_fixed(STEP);
	if (temp.x > 0 && temp.y > 0 && temp.x < int_to_fixed(temp.plane->width)
		&& temp.y < int_to_fixed(temp.plane->heigth) && !paccess(temp))
		pcopy(&cub->p->p, temp);
}

void	key_hook(mlx_key_data_t key, void *tcub)
{
	t_cub	*cub = (t_cub *)tcub;
	
	if (key.key == MLX_KEY_ESCAPE && cub)
		mlx_close_window(cub->win);
	else if (key.key == MLX_KEY_RIGHT || key.key == MLX_KEY_LEFT)
		check_angles(key, cub);
	else if (key.key == MLX_KEY_W || key.key == MLX_KEY_S
		|| key.key == MLX_KEY_A || key.key == MLX_KEY_D)
		check_wasd(key, cub);
	draw_mini(cub);
}
