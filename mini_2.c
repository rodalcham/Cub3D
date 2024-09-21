/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:28:48 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/21 17:34:48 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_fixed	relative_x(u_int32_t x, t_cub *cub)
{
	t_fixed	ret;
	double	temp;

	temp = x;
	temp = temp * cub->map->width / (cub->img[0]->width * 2);
	ret = double_to_fixed(temp);
	ret += cub->p->p.x / 2;
	return (ret);
}

t_fixed	relative_y(u_int32_t y, t_cub *cub)
{
	t_fixed	ret;
	double	temp;

	temp = y;
	temp = temp * cub->map->heigth / (cub->img[0]->height * 2);
	ret = double_to_fixed(temp);
	ret += cub->p->p.y / 2;
	return (ret);
}
t_fixed	abs_x(u_int32_t x, t_cub *cub)
{
	t_fixed	ret;
	double	temp;

	temp = x;
	temp = temp * cub->map->width / (cub->img[0]->width);
	ret = double_to_fixed(temp);
	return (ret);
}

t_fixed	abs_y(u_int32_t y, t_cub *cub)
{
	t_fixed	ret;
	double	temp;

	temp = y;
	temp = temp * cub->map->heigth / (cub->img[0]->height);
	ret = double_to_fixed(temp);
	return (ret);
}


void	minimap(t_cub	*cub)
{
	u_int32_t	i;
	u_int32_t	j;
	t_point	p;

	j = 0;
	p.plane = cub->map;
	while (j < cub->img[0]->height)
	{
		p.y = relative_y(j, cub);
		i = 0;
		while (i < cub->img[0]->width)
		{
			p.x = relative_x(i, cub);
			if (paccess(p))
				mlx_put_pixel(cub->img[0], i, j, 42424242);
			else
				mlx_put_pixel(cub->img[0], i, j, 0);
			i++;
		}
		j++;
	}
}

void	static_map(t_cub	*cub)
{
	u_int32_t	i;
	u_int32_t	j;
	t_point	p;

	j = 0;
	p.plane = cub->map;
	while (j < cub->img[0]->height)
	{
		p.y = abs_y(j, cub);
		i = 0;
		while (i < cub->img[0]->width)
		{
			p.x = abs_x(i, cub);
			if (paccess(p))
				mlx_put_pixel(cub->img[0], i, j, 42424242);
			else
				mlx_put_pixel(cub->img[0], i, j, 0);
			i++;
		}
		j++;
	}
}
