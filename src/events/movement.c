/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:49:39 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/12 19:13:37 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rot_move(t_player *player, int direction)
{
	double	old_dir_x;
	double	rot_speed;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	rot_speed = direction * player->rot_speed;
	player->dir_x = player->dir_x * cos(rot_speed)
		- player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed)
		+ player->dir_y * cos(rot_speed);
	player->plane_x = player->plane_x * cos(rot_speed)
		- player->plane_y * sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed)
		+ player->plane_y * cos(rot_speed);
}

int	ft_touch(double px, double py, t_game *game)
{
	int		map_x;
	int		map_y;
	double	aux;

	aux = px + 0.1f;
	if ((int)(px - 0.1f) < (int)px)
		aux = px - 0.1f;
	map_x = (int)(aux);
	aux = py + 0.1f;
	if ((int)(py - 0.1f) < (int)py)
		aux = py - 0.1f;
	map_y = (int)(aux);
	if (game->map.grid[map_y][map_x] >= '1'
			&& game->map.grid[map_y][map_x] <= '9')
		return (1);
	return (0);
}

int	colision(t_game *game, t_player player, int n, int sh)
{
	double	pos_x;
	double	pos_y;

	if (n == 1)
	{
		pos_x = player.pos_x + (player.dir_x * player.move_speed * sh);
		pos_y = player.pos_y + (player.dir_y * player.move_speed * sh);
	}
	else if (n == 2)
	{
		pos_x = player.pos_x - (player.dir_x * player.move_speed * sh);
		pos_y = player.pos_y - (player.dir_y * player.move_speed * sh);
	}
	else if (n == 3)
	{
		pos_x = player.pos_x + (player.dir_y * player.move_speed * sh);
		pos_y = player.pos_y - (player.dir_x * player.move_speed * sh);
	}
	else
	{
		pos_x = player.pos_x - (player.dir_y * player.move_speed * sh);
		pos_y = player.pos_y + (player.dir_x * player.move_speed * sh);
	}
	return (ft_touch(pos_x, pos_y, game));
}

void	player_move(t_game *game)
{
	int	sh;

	sh = game->player.run;
	if (game->keys.key_w && !colision(game, game->player, 1, sh))
	{
		game->player.pos_x += game->player.dir_x * game->player.move_speed * sh;
		game->player.pos_y += game->player.dir_y * game->player.move_speed * sh;
	}
	if (game->keys.key_s && !colision(game, game->player, 2, sh))
	{
		game->player.pos_x -= game->player.dir_x * game->player.move_speed * sh;
		game->player.pos_y -= game->player.dir_y * game->player.move_speed * sh;
	}
	if (game->keys.key_a && !colision(game, game->player, 3, sh))
	{
		game->player.pos_x += game->player.dir_y * game->player.move_speed * sh;
		game->player.pos_y -= game->player.dir_x * game->player.move_speed * sh;
	}
	if (game->keys.key_d && !colision(game, game->player, 4, sh))
	{
		game->player.pos_x -= game->player.dir_y * game->player.move_speed * sh;
		game->player.pos_y += game->player.dir_x * game->player.move_speed * sh;
	}
}
