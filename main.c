/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:36:45 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/10/10 11:16:47 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * malloc attributes:
 * 
 * 1. Window
 * 2. 3 images
 * 3. 4 textures
 * 4. A t_plane object <No leaks possible>
 * 5. All strings allocated by the get_next_line function <No leaks possible>
 * 6. All strings allocated with ft_strdup() <No leaks possible>
 * 
 */

void	destroy_cub(t_cub *cub)
{
	if (cub->img[0])
		mlx_delete_image(cub->win, cub->img[0]);
	if (cub->img[1])
		mlx_delete_image(cub->win, cub->img[1]);
	if (cub->img[2])
		mlx_delete_image(cub->win, cub->img[2]);
	if (cub->win)
		mlx_terminate(cub->win);
	destroy_plane(cub->map);
	destroy_obj(*cub->wall);
	link_free();
}

void	mlx_exit(t_cub *cub)
{
	err("MLX error.\n");
	destroy_cub(cub);
	exit (1);
}

void	init_mlx(t_cub *cub)
{
	cub->win = mlx_init(WIDTH, HEIGHT, "Cub3D", 1);
	if (!cub->win)
		mlx_exit(cub);
	cub->img[0] = mlx_new_image(cub->win, HEIGHT / 4, HEIGHT / 4);
	if (!cub->img[0])
		mlx_exit(cub);
	cub->img[1] = mlx_new_image(cub->win, WIDTH, HEIGHT);
	if (!cub->img[1])
		mlx_exit(cub);
	cub->img[2] = mlx_new_image(cub->win, WIDTH, HEIGHT);
	if (!cub->img[2])
		mlx_exit(cub);
	if (load_textures(cub->wall))
		mlx_exit(cub);
	if (mlx_image_to_window(cub->win, cub->img[2], 0, 0))
		mlx_exit(cub);
	if (mlx_image_to_window(cub->win, cub->img[1], 0, 0))
		mlx_exit(cub);
	if (mlx_image_to_window(cub->win, cub->img[0], 0, 0))
		mlx_exit(cub);
}

void	check_leaks(void)
{
	system("leaks Cub3d");
}

int	main(int argc, char **argv)
{
	t_cub		cub;
	t_object	obj;
	t_player	p;

	atexit(check_leaks);
	cub.wall = &obj;
	cub.p = &p;
	cub.win = NULL;
	cub.img[0] = NULL;
	cub.img[1] = NULL;
	cub.img[2] = NULL;
	cub.map = NULL;
	if (argc != 2)
		return (err("Incorrect number of arguments.\n"), 1);
	if (obj_init(&obj, &cub, argv[1]) < 0)
		return (err("Invalid Map.\n"), destroy_plane(cub.map), link_free(), 1);
	init_mlx(&cub);
	// setup_mouse(&cub);
	draw_background(&cub, 42424, 4265367);
	load_gun(&obj, &cub);
	draw_gun(&obj, &cub);
	mlx_loop_hook(cub.win, key_hook, &cub);
	mlx_cursor_hook(cub.win, cur_hook, &cub);
	mlx_loop(cub.win);
	free_gun(obj, cub);
	destroy_cub(&cub);
}
