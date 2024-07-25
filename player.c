/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:54:52 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/07/23 15:26:36 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_player(mlx_t *win)
{
	mlx_image_t	*img;

	img = mlx_new_image(win, 42, 42);
	if (!img)
	{
		mlx_close_window(win);
		return (-1);
	}
	if (mlx_image_to_window(win, img, 0 ,0) < 0)
	{
		mlx_close_window(win);
		return (-1);
	}
}

t_player *get_player(void)
{
	static t_player	player;

	return (&player);
}