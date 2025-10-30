/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:49:39 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/30 12:33:23 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

void	rot_move(t_player *player, int direction)
{
	double	old_dirX;
	double	rot_speed;
	double	old_planeX;

	old_dirX = player->dirX;
	old_planeX = player->planeX;
	rot_speed = direction * player->rot_speed;
	player->dirX = player->dirX * cos(rot_speed) - player->dirY * sin(rot_speed);
	player->dirY = old_dirX * sin(rot_speed) + player->dirY * cos(rot_speed);
	player->planeX = player->planeX * cos(rot_speed) - player->planeY * sin(rot_speed);
	player->planeY = old_planeX * sin(rot_speed) + player->planeY * cos(rot_speed);

}

int	touch(double px, double py, t_game *game)
{
	int x;
	int	y;
	int	rel_sizemapX;
	int	rel_sizemapY;

	rel_sizemapX = WIDTH - (game->map.tile_size * game->map.width);
	rel_sizemapY = HEIGHT - (game->map.tile_size * game->map.height);
	x = (px - (rel_sizemapX / 2)) / game->map.tile_size;
	y = (py - (rel_sizemapY / 2)) / game->map.tile_size;
	if (game->map.grid[y][x] >= '1')
		return (1);
	return (0);
}

int	touch2(double px, double py, t_game *game)
{
	int	mapX;
	int mapY;

	mapX = (int)(px / game->map.tile_size);
	mapY = (int)(py / game->map.tile_size);
	if (game->map.grid[mapY][mapX] >= '1')
		return (1);
	return (0);
}

int	colision(t_game *game, t_player player, int n)
{
	if (n == 1)
	{
		player.posX += player.dirX * player.move_speed;
		player.posY += player.dirY * player.move_speed;
	}
	else if (n == 2)
	{
		player.posX -= player.dirX * player.move_speed;
		player.posY -= player.dirY * player.move_speed;
	}
	else if (n == 3)
	{
		player.posX += player.dirY * player.move_speed;
		player.posY -= player.dirX * player.move_speed;
	}
	else
	{
		player.posX -= player.dirY * player.move_speed;
		player.posY += player.dirX * player.move_speed;
	}
	return (touch(player.posX, player.posY, game));
}

void	player_move(t_game *game)
{
	if (game->keys.key_w)
	{
		game->player.posX += game->player.dirX * game->player.move_speed;
		game->player.posY += game->player.dirY * game->player.move_speed;
	}
	if (game->keys.key_s)
	{		
		game->player.posX -= game->player.dirX * game->player.move_speed;
		game->player.posY -= game->player.dirY * game->player.move_speed;
	}
	if (game->keys.key_a)
	{
		game->player.posX += game->player.dirY * game->player.move_speed;
		game->player.posY -= game->player.dirX * game->player.move_speed;
	}
	if (game->keys.key_d)
	{
		game->player.posX -= game->player.dirY * game->player.move_speed;
		game->player.posY += game->player.dirX * game->player.move_speed;
	}
}

double	ray_dist(t_game *game, double dirX, double dirY)
{
	double	dx;
	double	dy;
	double	ray_x;
	double	ray_y;

	ray_x = game->player.posX;
	ray_y = game->player.posY;
	while (!touch(ray_x, ray_y, game))
	{
		ray_x += dirX;
		ray_y += dirY;
	}
	dx = ray_x - game->player.posX;
	dy = ray_y - game->player.posY;
	return ((sqrt((dx * dx) + (dy * dy))));
}
