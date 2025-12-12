/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:59:16 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/12 13:15:57 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dist_calculation(t_ray_result *ray)
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

void	step_calculation(int mapX, int mapY, t_ray_result *ray, t_game *game)
{
	if (ray->dirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->player.posX - mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (mapX + 1.0 - game->player.posX) * ray->deltaDistX;
	}
	if (ray->dirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->player.posY - mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (mapY + 1.0 - game->player.posY) * ray->deltaDistY;
	}
}

void	hit_loop(int *mapX, int *mapY, t_ray_result *ray, t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
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
		if (*mapY >= 0 && *mapY < game->map.height
			&& *mapX >= 0 && *mapX < game->map.width)
		{
			if (game->map.grid[*mapY][*mapX] >= '1' &&
				game->map.grid[*mapY][*mapX] <= '9')
				hit = 1;
		}
		else
			hit = 1;
	}
}

void	cast_ray_dda(t_game *game, t_ray_result *ray)
{
	int	map_x;
	int	map_y;

	map_x = (int)(game->player.posX);
	map_y = (int)(game->player.posY);
	dist_calculation(ray);
	step_calculation(map_x, map_y, ray, game);
	hit_loop(&map_x, &map_y, ray, game);
	if (ray->side == 0)
		ray->distance = ray->sideDistX - ray->deltaDistX;
	else
		ray->distance = ray->sideDistY - ray->deltaDistY;
	ray->hit_x = game->player.posX + ray->distance * ray->dirX;
	ray->hit_y = game->player.posY + ray->distance * ray->dirY;
}

void	ray_casting_loop(t_game *game)
{
	t_ray_result	ray;
	t_vertical		vertical;
	double			camera_x;

	vertical.x = 0;
	while (vertical.x < WIDTH)
	{
		camera_x = 2 * vertical.x / (double)WIDTH - 1;
		ray.dirX = game->player.dirX + game->player.planeX * camera_x;
		ray.dirY = game->player.dirY + game->player.planeY * camera_x;
		cast_ray_dda(game, &ray);
		vertical.y_start = -((int)(HEIGHT / ray.distance)) / 2 + HEIGHT / 2;
		vertical.y_end = (int)(HEIGHT / ray.distance) / 2 + HEIGHT / 2;
		draw_vertical(game, &vertical, ray);
		vertical.x++;
	}
}
