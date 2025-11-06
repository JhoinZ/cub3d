/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:49:39 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/11/06 13:20:24 by fosuna-g         ###   ########.fr       */
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
	int		mapX;
	int 	mapY;
	double	aux;

	printf("Px: %f\n", px);
	aux = px + 0.3f;
	printf("Aux1: %f\n", aux);
	mapX = (int)(aux);
	aux = py + 0.3f;
	//printf("Aux2: %f\n", aux);
	mapY = (int)(aux);
	if (game->map.grid[mapY][mapX] >= '1' && game->map.grid[mapY][mapX] <= '9')
		return (1);
	return (0);
}

int	colision(t_game *game, t_player player, int n, int sh)
{
	double	posX;
	double	posY;

	if (n == 1)
	{
		posX = player.posX + (player.dirX * player.move_speed * sh);
		posY = player.posY + (player.dirY * player.move_speed * sh);
	}
	else if (n == 2)
	{
		posX = player.posX - (player.dirX * player.move_speed * sh);
		posY = player.posY - (player.dirY * player.move_speed * sh);
	}
	else if (n == 3)
	{
		posX = player.posX + (player.dirY * player.move_speed * sh);
		posY = player.posY - (player.dirX * player.move_speed * sh);
	}
	else
	{
		posX = player.posX - (player.dirY * player.move_speed * sh);
		posY = player.posY + (player.dirX * player.move_speed * sh);
	}
	return (touch2(posX, posY, game));
}

void	player_move(t_game *game)
{
	int	sh;

	sh = game->player.run;
	if (game->keys.key_w && !colision(game, game->player, 1, sh))
	{
		game->player.posX += game->player.dirX * game->player.move_speed * sh;
		game->player.posY += game->player.dirY * game->player.move_speed * sh;
	}
	if (game->keys.key_s && !colision(game, game->player, 2, sh))
	{		
		game->player.posX -= game->player.dirX * game->player.move_speed * sh;
		game->player.posY -= game->player.dirY * game->player.move_speed * sh;
	}
	if (game->keys.key_a && !colision(game, game->player, 3, sh))
	{
		game->player.posX += game->player.dirY * game->player.move_speed * sh;
		game->player.posY -= game->player.dirX * game->player.move_speed * sh;
	}
	if (game->keys.key_d && !colision(game, game->player, 4, sh))
	{
		game->player.posX -= game->player.dirY * game->player.move_speed * sh;
		game->player.posY += game->player.dirX * game->player.move_speed * sh;
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
