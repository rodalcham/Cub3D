/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:51:48 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/18 16:30:54 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# define HEIGHT 1200
# define WIDTH 2400
# define FOV 70
# define RAY_NBR 2400
# define TURN 2
# define STEP 0.05

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# include "MLX42/include/MLX42/MLX42.h"
# include "MLibft/libft.h"
# include "2DPlane/Plane.h"
# include "2DPlane/Fixed.h"

/** Our player Struct
* @param P The point at which the player is located
* @param angle The angle that the player is facing
* @param view An array of all the angles in the player's FOV
*/
typedef struct	s_player
{
	t_point		p;
	t_fixed		angle;
	t_ray		view[RAY_NBR];
}				t_player;

/** A struct for objects to be displayed
 * @param NORTH The texture of the object's north side
 * @param SOUTH The texture of the object's south side
 * @param EAST The texture of the object's east side
 * @param WEST The texture of the object's west side
 * @param FLOOR The texture of the object's bottom side
 * @param CEILING The texture of the object's top side
 */
typedef struct	s_object
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	char			*floor;
	char			*ceiling;
	mlx_t			*mlxpointer;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
}				t_object;
/** Our Cub3D Struct
 * @param WIN A pointer to the window
 * @param IMG An array of pointers to images
 * @param MAP A pointer to a plane object
 * @param P A pointer to the player
 * @param WALL A pointer to the object representing our walls
 */
typedef struct	s_cub
{
	mlx_t		*win;
	mlx_image_t	*img[3];
	t_plane		*map;
	t_player	*p;
	t_object	*wall;
}				t_cub;

/** A useful struct to store information about collisions
 * @param OBJ The object you have collided with
 * @param P The point of collision
 * @param DISTANCE How far away is the object from origin
 * @param DIR A char, indicating from which direction the collision occured
 */
typedef	struct crash_s
{
	void		*obj;
	t_point		p;
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
void	key_hook(void *cub);

t_fixed	normalize(t_fixed angle);
void	flood_fill(t_cub *cub, t_point p, uint32_t limit, uint32_t fill);
void	pcopy(t_point *dst, t_point src);
t_crash	cast_ray(t_ray ray);
void	draw_walls(t_crash crash, t_cub cub, int i, t_fixed angle);
void	load_textures(t_object *object);
int		frame_function(void);

#endif