/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:59:16 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/28 13:21:16 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	distCalculation(t_ray_result *ray)
{
	if (ray->dirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->dirX);
	if (ray->dirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->dirY);
}

void	stepCalculation(int mapX, int mapY, t_ray_result *ray, t_game *game)
{
	if (ray->dirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->player.posX / game->map.tile_size - mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (mapX + 1.0 - game->player.posX / game->map.tile_size) * ray->deltaDistX;
	}
	if (ray->dirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->player.posY / game->map.tile_size - mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (mapY + 1.0 - game->player.posY / game->map.tile_size) * ray->deltaDistY;
		
	}
}

void	hit_loop(int *mapX, int *mapY, t_ray_result *ray, t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0) {
		if (ray->sideDistX < ray->sideDistY) 
		{
			ray->sideDistX += ray->deltaDistX;
			*mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			*mapY += ray->stepY;
			ray->side = 1;
		}
		if (*mapY >= 0 && *mapY < game->map.height && 
			*mapX >= 0 && *mapX < game->map.width) {
			if (game->map.grid[*mapY][*mapX] >= '1')
				hit = 1;
		}
		else
			hit = 1;
	}
}

void	cast_ray_dda(t_game *game, t_ray_result *ray)
{
	int	mapX;
	int	mapY;
	
	mapX = (int)(game->player.posX / game->map.tile_size);
	mapY = (int)(game->player.posY / game->map.tile_size);
	distCalculation(ray);
	stepCalculation(mapX, mapY, ray, game);
	hit_loop(&mapX, &mapY, ray, game);
	if (ray->side == 0)
	{
		ray->distance = (mapX - game->player.posX / game->map.tile_size + (1 - ray->stepX) / 2) / ray->dirX;		
	}
	else
	{
		ray->distance = (mapY - game->player.posY / game->map.tile_size + (1 - ray->stepY) / 2) / ray->dirY;
	}
	ray->hit_x = game->player.posX + ray->distance * ray->dirX;
	ray->hit_y = game->player.posY + ray->distance * ray->dirY;
}


void	ray_casting_loop(t_game *game)
{
	int				x;
	t_ray_result	ray;
	double			cameraX;
	int				draw_start;
	int				draw_end;
	
	x = 0;
	while (x < WIDTH)
	{
		cameraX = 2 * x / (double)WIDTH - 1;
		ray.dirX = game->player.dirX + game->player.planeX * cameraX;
		ray.dirY = game->player.dirY + game->player.planeY * cameraX;
		cast_ray_dda(game, &ray);
		draw_start = -((int)(HEIGHT / ray.distance)) / 2 + HEIGHT / 2;
		draw_end = (int)(HEIGHT / ray.distance) / 2 + HEIGHT / 2;
		draw_vertical_line(game, x, draw_start, draw_end, choose_color(ray.side));
		draw_vertical_line(game, x, 0, draw_start - 1, game->map.ceiling_color);
		draw_vertical_line(game, x, draw_end + 1, HEIGHT - 1, game->map.floor_color);
		x++;
	}
}
