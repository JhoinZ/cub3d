/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:59:16 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/12 19:33:27 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dist_calculation(t_ray_result *ray)
{
	if (ray->dir_x == 0)
		ray->deltadist_x = 1e30;
	else
		ray->deltadist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->deltadist_y = 1e30;
	else
		ray->deltadist_y = fabs(1 / ray->dir_y);
}

void	step_calculation(int map_x, int map_y, t_ray_result *ray, t_game *game)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (game->player.pos_x - map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (map_x + 1.0 - game->player.pos_x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (game->player.pos_y - map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (map_y + 1.0 - game->player.pos_y) * ray->deltadist_y;
	}
}

void	hit_loop(int *map_x, int *map_y, t_ray_result *ray, t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			*map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			*map_y += ray->step_y;
			ray->side = 1;
		}
		if (check_walls(map_x, map_y, game))
			hit = 1;
	}
}

void	cast_ray_dda(t_game *game, t_ray_result *ray)
{
	int	map_x;
	int	map_y;

	map_x = (int)(game->player.pos_x);
	map_y = (int)(game->player.pos_y);
	dist_calculation(ray);
	step_calculation(map_x, map_y, ray, game);
	hit_loop(&map_x, &map_y, ray, game);
	if (ray->side == 0)
		ray->distance = ray->sidedist_x - ray->deltadist_x;
	else
		ray->distance = ray->sidedist_y - ray->deltadist_y;
	ray->hit_x = game->player.pos_x + ray->distance * ray->dir_x;
	ray->hit_y = game->player.pos_y + ray->distance * ray->dir_y;
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
		ray.dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		ray.dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		cast_ray_dda(game, &ray);
		vertical.y_start = -((int)(HEIGHT / ray.distance)) / 2 + HEIGHT / 2;
		vertical.y_end = (int)(HEIGHT / ray.distance) / 2 + HEIGHT / 2;
		draw_vertical(game, &vertical, ray);
		vertical.x++;
	}
}
