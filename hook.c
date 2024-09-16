/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:12:11 by rchavez           #+#    #+#             */
/*   Updated: 2024/09/16 22:00:56 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_angles(t_cub *cub)
{
	t_fixed delta;
	int i;

	i = -1;
	delta = f_div(int_to_fixed(FOV), int_to_fixed(RAY_NBR));
	if (mlx_is_key_down(cub->win, MLX_KEY_RIGHT))
		cub->p->angle = normalize(cub->p->angle + int_to_fixed(TURN));
	else
		cub->p->angle = normalize(cub->p->angle - int_to_fixed(TURN));
	while (++i < RAY_NBR)
		cub->p->view[i].angle = normalize(cub->p->angle + f_mult(delta, int_to_fixed(i - RAY_NBR / 2)));
}

void	check_ws(t_cub *cub, t_point *temp)
{
	if (mlx_is_key_down(cub->win, MLX_KEY_W))
	{
		temp->x += f_mult(double_to_fixed(STEP), f_cos(cub->p->angle));
		temp->y += f_mult(double_to_fixed(STEP), f_sin(cub->p->angle));
	}
	else
	{
		temp->x -= f_mult(double_to_fixed(STEP), f_cos(cub->p->angle));
		temp->y -= f_mult(double_to_fixed(STEP), f_sin(cub->p->angle));
	}
}

void	check_ad(t_cub *cub, t_point *temp)
{
	if (mlx_is_key_down(cub->win, MLX_KEY_D))
	{
		temp->x -= f_mult(double_to_fixed(STEP), f_sin(cub->p->angle));
		temp->y += f_mult(double_to_fixed(STEP), f_cos(cub->p->angle));
	}
	else
	{
		temp->x += f_mult(double_to_fixed(STEP), f_sin(cub->p->angle));
		temp->y -= f_mult(double_to_fixed(STEP), f_cos(cub->p->angle));
	}
}

void	check_wasd(t_cub *cub)
{
	t_point	temp;
	t_point	*p;

	p = &cub->p->p;
	pcopy(&temp, *p);
	if (mlx_is_key_down(cub->win, MLX_KEY_W) || mlx_is_key_down(cub->win, MLX_KEY_S))
		check_ws(cub, &temp);
	if (mlx_is_key_down(cub->win, MLX_KEY_A) || mlx_is_key_down(cub->win, MLX_KEY_D))
		check_ad(cub, &temp);
	while (p->x < temp.x && p->x > 0 && p->x < int_to_fixed(p->plane->width) - 1 && !paccess((t_point){p->x + 1, p->y, p->plane}))
		p->x++;
	while (p->x > temp.x && p->x > 0 && p->x < int_to_fixed(p->plane->width) - 1 && !paccess((t_point){p->x - 1, p->y, p->plane}))
		p->x--;
	while (p->y < temp.y && p->y > 0 && p->y < int_to_fixed(p->plane->heigth) - 1 && !paccess((t_point){p->x, p->y + 1, p->plane}))
		p->y++;
	while (p->y > temp.y && p->y > 0 && p->y < int_to_fixed(p->plane->heigth) - 1 && !paccess((t_point){p->x, p->y - 1, p->plane}))
		p->y--;
}

void	key_hook(void *tcub)
{
	t_cub	*cub = (t_cub *)tcub;
	
	if (mlx_is_key_down(cub->win, MLX_KEY_ESCAPE))
		mlx_close_window(cub->win);
	if (mlx_is_key_down(cub->win, MLX_KEY_RIGHT) || mlx_is_key_down(cub->win, MLX_KEY_LEFT))
		check_angles(cub);
	if (mlx_is_key_down(cub->win, MLX_KEY_W) || mlx_is_key_down(cub->win, MLX_KEY_S) || mlx_is_key_down(cub->win, MLX_KEY_A) || mlx_is_key_down(cub->win, MLX_KEY_D))
		check_wasd(cub);
	draw_mini(cub);
}
