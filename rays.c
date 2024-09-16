/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:36:37 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/16 17:19:31 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_crash rec_ray(t_ray ray, t_point point, t_fixed xdelta, t_fixed ydelta)
{
	t_crash ret;

	while (1)
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
	xdelta = f_div(f_tan(ydelta), ray.angle);
	return (rec_ray(ray, point, xdelta, ydelta));
}

t_crash	cast_ray(t_ray ray)
{
	t_crash crash[2];
	int		xsign;
	int		ysign;

	xsign = -1;
	ysign = -1;
	if (ray.angle > 0 && ray.angle < int_to_fixed(200))
		ysign = 1;
	else if (ray.angle == 0 || ray.angle == int_to_fixed(200))
		ysign = 0;
	if (ray.angle < int_to_fixed(100) || ray.angle > int_to_fixed(300))
		xsign = 1;
	else if (ray.angle == int_to_fixed(100) || ray.angle == int_to_fixed(300))
		xsign = 0;
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

	if (mode == 'x')
	{
		ret.x = ray.src->x >> 16;
		ret.x = ret.x << 16;
		if (sign == 1)
			ret.x += int_to_fixed(1);
		temp = ret.x - ray.src->x;
		ret.y = ray.src->y + f_mult(f_tan(ray.angle), temp);
	}
	else
	{
		ret.y = ray.src->y >> 16;
		ret.y = ret.y << 16;
		if (sign == 1)
			ret.y += int_to_fixed(1);
		temp = ret.y - ray.src->y;
		ret.x = ray.src->x + f_div(temp, f_tan(ray.angle));
	}
	return (ret);
}
