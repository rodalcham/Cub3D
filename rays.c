/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:36:37 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/17 14:03:38 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	calc_coll(t_ray ray, int sign, char mode);

t_crash rec_ray(t_ray ray, t_point point, t_fixed xdelta, t_fixed ydelta)
{
	t_crash ret;

	while (point.x > 0 && point.x < int_to_fixed(ray.src->plane->width) && point.y > 0 && point.y < int_to_fixed(ray.src->plane->heigth))
	{
		if (paccess(point))
		{
			ret.dir = 'c';
			ret.distance = distance(*ray.src, point);
			ret.p = point;
			ret.obj = paccess(point);
			return (ret);
		}
		point.x += xdelta;
		point.y += ydelta;
	}
	ret.dir = 'c';
	ret.distance = distance(*ray.src, point);
	ret.p = point;
	ret.obj = paccess(point);
	return (ret);
}

t_crash	castray_X(int xsign, t_ray ray, t_point point)
{
	t_fixed	xdelta;
	t_fixed	ydelta;

	xdelta = int_to_fixed(xsign);
	ydelta = f_mult(f_tan(ray.angle), xdelta);
	return (rec_ray(ray, point, xdelta, ydelta));
}

t_crash	castray_Y(int ysign, t_ray ray, t_point point)
{
	t_fixed	xdelta;
	t_fixed	ydelta;

	ydelta = int_to_fixed(ysign);
	if (f_tan(ray.angle) < int_to_fixed(1000))
		xdelta = f_div(ydelta, f_tan(ray.angle));
	else 
		xdelta = 0;
	return (rec_ray(ray, point, xdelta, ydelta));
}

t_crash	cast_ray(t_ray ray)
{
	t_crash crash[2];
	int		xsign;
	int		ysign;

	xsign = 0;
	ysign = 0;
	if (ray.angle > int_to_fixed(1) && ray.angle < int_to_fixed(199))
		ysign = 1;
	else if (ray.angle > (int_to_fixed(201)) &&  ray.angle < int_to_fixed(399))
		ysign = -1;
	if (ray.angle < int_to_fixed(99) || ray.angle > int_to_fixed(301))
		xsign = 1;
	else if (ray.angle > int_to_fixed(101) && ray.angle < int_to_fixed(299))
		xsign = -1;
	if (xsign)
		crash[0] = castray_X(xsign, ray, calc_coll(ray, xsign, 'x'));
	if (ysign)
		crash[1] = castray_Y(ysign, ray, calc_coll(ray, ysign, 'y'));
	if (!xsign)
		return (crash[1]);
	if (!ysign)
		return (crash[0]);
	if (crash[0].distance < crash[1].distance)
		return (crash[0]);
	return (crash[1]);
}

t_point	calc_coll(t_ray ray, int sign, char mode)
{
	t_point ret;
	t_fixed temp;

	ret.plane = ray.src->plane;
	if (mode == 'x')
	{
		ret.x = ray.src->x >> 16;
		ret.x = ret.x << 16;
		if (sign == 1)
			ret.x += int_to_fixed(1);
		else
		{
			ret.x -= 2;
			ret.y--;
		}
		ret.x++;
		temp = ret.x - ray.src->x;
		ret.y = ray.src->y + f_mult(f_tan(ray.angle), temp);
	}
	else
	{
		ret.y = ray.src->y >> 16;
		ret.y = ret.y << 16;
		if (sign == 1)
			ret.y += int_to_fixed(1);
		else
		{
			ret.y -= 2;
			ret.x--;
		}
		ret.y++;
		temp = ret.y - ray.src->y;
		ret.x = ray.src->x + f_div(temp, f_tan(ray.angle));
	}
	return (ret);
}
