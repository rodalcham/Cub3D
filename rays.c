/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:36:37 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/16 15:44:37 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define P2 (int_to_fixed(PI / 2))
#define P3 (int_to_fixed(3 * PI / 2))

t_crash cast_ray(t_ray ray, t_plane plane, t_crash crash)
{
	int mx, my; // Grid position
	int dof;    // Depth of field (how many iterations we've done)
	t_fixed rx, ry; // Ray X and Y positions in fixed-point
	t_fixed ra;   // Ray angle in fixed-point
	t_fixed xo, yo; // X and Y increments (step size) in fixed-point
	int r = 0;

	ra = float_to_fixed(ray.angle); // Convert ray angle to fixed-point

	while (r < 1) // Outer loop for raycasting
	{
		// Horizontal raycasting
		dof = 0;
		t_fixed aTan = f_tan(int_to_fixed(-1) / ra); // atan for fixed-point

		// Looking down (ray direction is downward)
		if (fixed_to_float(ra) > PI)
		{
			ry = int_to_fixed(((int)fixed_to_int(ray.src->y) >> 6) << 6) - int_to_fixed(0.0001);
			rx = (ray.src->y - ry) * aTan + ray.src->x;
			yo = int_to_fixed(-64);
			xo = -yo * aTan;
		}
		// Looking up (ray direction is upward)
		else if (fixed_to_float(ra) < PI)
		{
			ry = int_to_fixed(((int)fixed_to_int(ray.src->y) >> 6) << 6) + int_to_fixed(64);
			rx = (ray.src->y - ry) * aTan + ray.src->x;
			yo = int_to_fixed(64);
			xo = -yo * aTan;
		}
		// Looking straight left or right (no horizontal intersection)
		else if (fabs(fixed_to_float(ra) - PI) < 0.0001 || fabs(fixed_to_float(ra)) < 0.0001)
		{
			rx = ray.src->x;
			ry = ray.src->y;
			dof = 8;  // Max out the depth of field (no intersection)
		}

		// Horizontal ray-casting loop
		while (dof < 8)
		{
			mx = fixed_to_int(rx) >> 6;
			my = fixed_to_int(ry) >> 6;
			// Bounds checking (make sure we're inside the grid)
			if (mx >= 0 && mx < plane.width && my >= 0 && my < plane.heigth)
			{
				// Check if the ray hit something in the grid (non-zero means a hit)
				if (plane.grid[my][mx] != NULL) 
				{
					dof = 8; // Stop when a hit is detected
					crash.p.x = rx;
					crash.p.y = ry;
					crash.distance = sqrtf((fixed_to_float(rx - ray.src->x)) * (fixed_to_float(rx - ray.src->x)) + (fixed_to_float(ry - ray.src->y)) * (fixed_to_float(ry - ray.src->y)));
				}
				else
				{
					rx += xo;
					ry += yo;
					dof += 1;
				}
			}
			else
			{
				dof = 8; // Out of bounds
			}
		}

		// Vertical raycasting
		dof = 0;
		t_fixed nTan = f_tan(ra); // tan for fixed-point

		// Looking left
		if (fixed_to_float(ra) > PI / 2 && fixed_to_float(ra) < 3 * PI / 2)
		{
			rx = int_to_fixed(((int)fixed_to_int(ray.src->x) >> 6) << 6) - int_to_fixed(0.0001);
			ry = (ray.src->x - rx) * nTan + ray.src->y;
			xo = int_to_fixed(-64);
			yo = -xo * nTan;
		}
		// Looking right
		else if (fixed_to_float(ra) < PI / 2 || fixed_to_float(ra) > 3 * PI / 2)
		{
			rx = int_to_fixed(((int)fixed_to_int(ray.src->x) >> 6) << 6) + int_to_fixed(64);
			ry = (ray.src->x - rx) * nTan + ray.src->y;
			xo = int_to_fixed(64);
			yo = -xo * nTan;
		}
		// Looking straight up or down
		else if (fabs(fixed_to_float(ra) - PI / 2) < 0.0001 || fabs(fixed_to_float(ra) - 3 * PI / 2) < 0.0001)
		{
			rx = ray.src->x;
			ry = ray.src->y;
			dof = 8;  // Max out the depth of field (no intersection)
		}

		// Vertical ray-casting loop
		while (dof < 8)
		{
			mx = fixed_to_int(rx) >> 6;
			my = fixed_to_int(ry) >> 6;
			// Bounds checking (make sure we're inside the grid)
			if (mx >= 0 && mx < plane.width && my >= 0 && my < plane.heigth)
			{
				// Check if the ray hit something in the grid (non-zero means a hit)
				if (plane.grid[my][mx] != NULL) 
				{
					dof = 8; // Stop when a hit is detected
					crash.p.x = rx;
					crash.p.y = ry;
					crash.distance = sqrtf((fixed_to_float(rx - ray.src->x)) * (fixed_to_float(rx - ray.src->x)) + (fixed_to_float(ry - ray.src->y)) * (fixed_to_float(ry - ray.src->y)));
				}
				else
				{
					rx += xo;
					ry += yo;
					dof += 1;
				}
			}
			else
			{
				dof = 8; // Out of bounds
			}
		}
		r++;
	}
	return crash;
}
