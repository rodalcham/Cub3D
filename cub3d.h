/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:51:48 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/07/24 09:50:55 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define HEIGHT 420
# define WIDTH 420
# define FOV 42
# define OFFSET 1

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "MLX42/include/MLX42/MLX42.h"
# include "MLibft/libft.h"

# include <stdio.h> // REMOVE                										REMOVE

// My map struct
typedef struct	s_cub
{
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	char		*floor;
	char		*ceiling;
	int			width;
	int			heigth;
	char		**grid;
}				t_cub;

// My player struct
typedef struct	s_player
{
	float		x;
	float		y;
	float		delta;
}				t_player;


// Map functions
int		cub_init(t_cub *map, char *path);
int		extract_grid(t_cub *map, int fd);
int		ft_strcmp(char *s1, char *s2);
void	free_chars(char **chars);
void	destroy_cub(t_cub map);

// Player functions
t_player *get_player(void);

#endif