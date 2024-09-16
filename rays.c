/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:36:37 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/09/15 22:31:48 by rchavez@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void draw_ray(t_player *p)
// {
// 	int x;
// 	// Angle should be in radians
// 	x = 0;
// 	double dirX = cos(p->angle);
// 	double dirY = sin(p->angle);
// 	double planeX = -dirY * tan(FOV / 2);
// 	double planeY = dirX * tan(FOV / 2);

// 	while (x < WIDTH)
// 	{
// 		double cameraX = 2 * x / (double)(WIDTH) - 1;
// 		double rayDirX = dirX + planeX * cameraX;
// 		double rayDirY = dirY + planeY * cameraX;
		
// 		// Map indices
// 		int mapX = (int)(p->p.x);
// 		int mapY = (int)(p->p.y);

// 		double sideDistX;
// 		double sideDistY;
// 		double deltaDistX = fabs(1 / rayDirX);
// 		double deltaDistY = fabs(1 / rayDirY);
// 		double perpWallDist;

// 		// Direction of step in x or y-direction (either +1 or -1)
// 		int stepX;
// 		int stepY;

// 		int hit = 0; // was there a wall hit?
// 		int side;    // was a NS or an EW wall hit?

// 		// Calculate step and initial sideDist
// 		if (rayDirX < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (p->p.x - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - p->p.x) * deltaDistX;
// 		}
// 		if (rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (p->p.y - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - p->p.y) * deltaDistY;
// 		}

// 		// Perform DDA
// 		while (hit == 0)
// 		{
// 			// Jump to next map square, either in x-direction, or in y-direction
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}

// 			// Check if ray has hit a wall
// 			if (worldMap[mapX][mapY] > 0)
// 				hit = 1;
// 		}

// 		// Calculate distance projected on camera direction (Euclidean distance would give fisheye effect)
// 		if (side == 0)
// 			perpWallDist = (sideDistX - deltaDistX);
// 		else
// 			perpWallDist = (sideDistY - deltaDistY);

// 		x++;
// 	}
// }
