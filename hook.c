/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:12:11 by rchavez           #+#    #+#             */
/*   Updated: 2024/10/05 16:28:40 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_angles(t_cub *cub)
{
	static t_fixed	delta = 0;
	int				i;

	i = -1;
	if (!delta)
		delta = f_div(int_to_fixed(FOV), int_to_fixed(RAY_NBR));
	if (mlx_is_key_down(cub->win, MLX_KEY_RIGHT))
		cub->p->angle = normalize(cub->p->angle + int_to_fixed(TURN));
	else
		cub->p->angle = normalize(cub->p->angle - int_to_fixed(TURN));
	while (++i < RAY_NBR)
		cub->p->view[i].angle = normalize(cub->p->angle + f_mult(delta,
					int_to_fixed(i - RAY_NBR / 2)));
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
	if (mlx_is_key_down(cub->win, MLX_KEY_W)
		|| mlx_is_key_down(cub->win, MLX_KEY_S))
		check_ws(cub, &temp);
	if (mlx_is_key_down(cub->win, MLX_KEY_A)
		|| mlx_is_key_down(cub->win, MLX_KEY_D))
		check_ad(cub, &temp);
	while (p->x < temp.x && p->x > 0 && p->x < int_to_fixed(p->plane->width)
		- 1 && !player_access(p->x + 1, p->y, p->plane))
		p->x++;
	while (p->x > temp.x && p->x > 0 && p->x < int_to_fixed(p->plane->width)
		- 1 && !player_access(p->x - 1, p->y, p->plane))
		p->x--;
	while (p->y < temp.y && p->y > 0 && p->y < int_to_fixed(p->plane->heigth)
		- 1 && !player_access(p->x, p->y + 1, p->plane))
		p->y++;
	while (p->y > temp.y && p->y > 0 && p->y < int_to_fixed(p->plane->heigth)
		- 1 && !player_access(p->x, p->y - 1, p->plane))
		p->y--;
}

void	key_hook(void *tcub)
{
	static t_cub	*cub = NULL;

	if (!frame_function())
		return ;
	if (!cub)
		cub = (t_cub *)tcub;
	if (mlx_is_key_down(cub->win, MLX_KEY_ESCAPE))
		mlx_close_window(cub->win);
	if (mlx_is_key_down(cub->win, MLX_KEY_RIGHT)
		|| mlx_is_key_down(cub->win, MLX_KEY_LEFT))
		check_angles(cub);
	if (mlx_is_key_down(cub->win, MLX_KEY_W)
		|| mlx_is_key_down(cub->win, MLX_KEY_S)
		|| mlx_is_key_down(cub->win, MLX_KEY_A)
		|| mlx_is_key_down(cub->win, MLX_KEY_D))
		check_wasd(cub);
	draw_mini(cub);
}

void	mouse_move_callback(double xpos, double ypos, void *param)
{
	t_cub			*cub;
	double			sensitivity;
	double			delta_x;
	static double	last_x = 0;

	cub = (t_cub *)param;
	ypos = 0;
	sensitivity = 0.005;
	delta_x = xpos - last_x;
	cub->p->angle += double_to_fixed(delta_x * sensitivity);
	if (cub->p->angle < int_to_fixed(0))
	{
		cub->p->angle += int_to_fixed(360);
	}
	if (cub->p->angle >= int_to_fixed(360))
	{
		cub->p->angle -= int_to_fixed(360);
	}
	last_x = xpos;
}

void	setup_mouse(t_cub *cub)
{
	mlx_cursor_hook(cub->win, mouse_move_callback, cub);
}
