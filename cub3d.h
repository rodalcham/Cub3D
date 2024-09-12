/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:51:48 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/12 17:00:10 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define HEIGHT 1200
# define WIDTH 1200
# define FOV 70
# define RAY_NBR 140
# define TURN 5
# define STEP 0.5

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# include "MLX42/include/MLX42/MLX42.h"
# include "MLibft/libft.h"
# include "2DPlane/Plane.h"
# include "2DPlane/Fixed.h"

// Our player struct
typedef struct	s_player
{
	t_point		p;
	t_fixed		angle;
	t_ray		view[RAY_NBR];
}				t_player;

// Our object struct
typedef struct	s_object
{
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	char		*floor;
	char		*ceiling;
}				t_object;

// Our map struct
typedef struct	s_cub
{
	mlx_t		*win;
	mlx_image_t	*img[3];
	t_plane		*map;
	t_player	*p;
	t_object	*wall;
}				t_cub;

//	Crash Struct
typedef	struct crash_s
{
	void		*obj;
	t_fixed		distance;
	char		dir;
}				t_crash;


// Map functions
int		obj_init(t_object *obj, t_cub *cub, char *path);
int		extract_grid(t_cub *map, int fd);
int		ft_strcmp(char *s1, char *s2);
void	free_chars(char **chars);
void	destroy_obj(t_object obj);

// Raycaster
void	draw_mini(t_cub	*cub);

// Player Functions
void	init_player(t_cub *cub, int x, int y, char d);
void	key_hook(mlx_key_data_t key, void *cub);


#endif