/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:36:37 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/19 11:36:34 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	calc_coll(t_ray ray, int sign[2], char mode);

t_crash	rec_ray(t_ray ray, t_point point, t_fixed delta[2], char dir)
{
	t_crash	ret;

	while (point.x > 0 && point.x < int_to_fixed(ray.src->plane->width)
		&& point.y > 0 && point.y < int_to_fixed(ray.src->plane->heigth))
	{
		if (paccess(point))
		{
			ret.dir = dir;
			ret.distance = distance(*ray.src, point);
			ret.p = point;
			ret.obj = paccess(point);
			return (ret);
		}
		point.x += delta[0];
		point.y += delta[1];
	}
	ret.dir = dir;
	ret.distance = distance(*ray.src, point);
	ret.p = point;
	ret.obj = paccess(point);
	return (ret);
}

t_crash	castray_x(int xsign, t_ray ray, t_point point)
{
	t_fixed	delta[2];

	delta[0] = int_to_fixed(xsign);
	delta[1] = f_mult(f_tan(ray.angle), delta[0]);
	if (xsign > 0)
		return (rec_ray(ray, point, delta, 'W'));
	return (rec_ray(ray, point, delta, 'E'));
}

t_crash	castray_y(int ysign, t_ray ray, t_point point)
{
	t_fixed	delta[2];

	delta[1] = int_to_fixed(ysign);
	if (f_tan(ray.angle) < int_to_fixed(1000))
		delta[0] = f_div(delta[1], f_tan(ray.angle));
	else
		delta[0] = 0;
	if (ysign > 0)
		return (rec_ray(ray, point, delta, 'S'));
	return (rec_ray(ray, point, delta, 'N'));
}

t_crash	cast_ray(t_ray ray)
{
	t_crash	crash[2];
	int		sign[2];

	sign[0] = 0;
	sign[1] = 0;
	if (ray.angle > int_to_fixed(1) && ray.angle < int_to_fixed(199))
		sign[1] = 1;
	else if (ray.angle > (int_to_fixed(201)) && ray.angle < int_to_fixed(399))
		sign[1] = -1;
	if (ray.angle < int_to_fixed(99) || ray.angle > int_to_fixed(301))
		sign[0] = 1;
	else if (ray.angle > int_to_fixed(101) && ray.angle < int_to_fixed(299))
		sign[0] = -1;
	if (sign[0])
		crash[0] = castray_x(sign[0], ray, calc_coll(ray, sign, 'x'));
	if (sign[1])
		crash[1] = castray_y(sign[1], ray, calc_coll(ray, sign, 'y'));
	if (!sign[0])
		return (crash[1]);
	if (!sign[1])
		return (crash[0]);
	if (crash[0].distance < crash[1].distance)
		return (crash[0]);
	return (crash[1]);
}

t_point	calc_coll(t_ray ray, int sign[2], char mode)
{
	t_point	ret;
	t_fixed	temp;

	ret.plane = ray.src->plane;
	if (mode == 'x')
	{
		ret.x = (ray.src->x >> 16) << 16;
		if (sign[0] == 1)
			ret.x += int_to_fixed(1) + 5;
		temp = ret.x - ray.src->x;
		ret.y = ray.src->y + f_mult(f_tan(ray.angle), temp);
	}
	else
	{
		ret.y = (ray.src->y >> 16) << 16;
		if (sign[1] == 1)
			ret.y += int_to_fixed(1) + 5;
		temp = ret.y - ray.src->y;
		ret.x = ray.src->x + f_div(temp, f_tan(ray.angle));
	}
	if (sign[0] == -1)
		ret.x -= 5;
	if (sign[1] == -1)
		ret.y -= 5;
	return (ret);
}
