/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:11:25 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/15 22:25:31 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	first_crash(t_ray r, int sign, char mode)
{
	t_fixed	temp;

	if (mode == 'x')
	{
		temp = r.src->x >> POINT;
		temp = temp << POINT;
		if (sign == 1)
			temp += int_to_fixed(1);
		return (from_x(r, temp));
	}
	else
	{
		temp = r.src->y >> POINT;
		temp = temp << POINT;
		if (sign == 1)
			temp += int_to_fixed(1);
		return (from_y(r, temp));
	}
}

t_crash	cast_x(t_ray r, int xsign)
{
	t_crash	ret;
	t_point	temp;
	int	i;

	i = 0;
	pcopy(&temp, first_crash(r, xsign, 'x'));
	while (++i && xsign)
	{
		if (paccess(temp) || temp.x < 0 || temp.y < 0
			|| temp.x >= int_to_fixed(temp.plane->width)
			|| temp.y >= int_to_fixed(temp.plane->heigth))
		{
			ret.obj = paccess(temp);
			if (xsign == 1)
				ret.dir = 'e';
			else
				ret.dir = 'w';
			ret.distance = distance(*r.src, temp);
			pcopy(&ret.p, temp);
			return (ret);
		}
		pcopy(&temp, from_x(r, int_to_fixed(xsign * i)));
	}
	return ((t_crash){NULL, *r.src, 0, '\0'});
}

t_crash	cast_y(t_ray r, int ysign)
{
	t_crash	ret;
	t_point	temp;
	int	i;

	i = 0;
	pcopy(&temp, first_crash(r, ysign, 'y'));
	while (++i && ysign)
	{
		if (paccess(temp) || temp.x < 0 || temp.y < 0
			|| temp.x >= int_to_fixed(temp.plane->width)
			|| temp.y >= int_to_fixed(temp.plane->heigth))
		{
			ret.obj = paccess(temp);
			if (ysign == 1)
				ret.dir = 's';
			else
				ret.dir = 'n';
			ret.distance = distance(*r.src, temp);
			pcopy(&ret.p, temp);
			return (ret);
		}
		pcopy(&temp, from_x(r, int_to_fixed(ysign * i)));
	}
	return ((t_crash){NULL, *r.src, 0, '\0'});
}

t_crash	cast_ray(t_ray r)
{
	int	xsign;
	int	ysign;
	t_crash	x;
	t_crash	y;

	if (r.angle < int_to_fixed(Q2) || r.angle > int_to_fixed(Q4))
		xsign = 1;
	else if (r.angle == int_to_fixed(Q2) || r.angle == int_to_fixed(Q4))
		xsign = 0;
	else
		xsign = -1;
	if (r.angle < int_to_fixed(Q3) && r.angle > int_to_fixed(Q1))
		ysign = 1;
	else if (r.angle == int_to_fixed(Q3) || r.angle == int_to_fixed(Q1))
		ysign = 0;
	else
		ysign = -1;
	x = cast_x(r, xsign);
	y = cast_y(r, ysign);
	if (!ysign)
		return (x);
	if (!xsign)
		return (y);
	if (x.distance < y.distance)
		return (x);
	return (y);
}