
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
	if (game->map.grid[y][x] == '1')
		return (1);
	return (0);
}

void	player_move(t_game *game, int keycode)
{
	if (keycode == KEY_W)
	{
		game->player.posX += game->player.dirX * game->player.move_speed;
		game->player.posY += game->player.dirY * game->player.move_speed;
	}
	if (keycode == KEY_S)
	{		
		game->player.posX -= game->player.dirX * game->player.move_speed;
		game->player.posY -= game->player.dirY * game->player.move_speed;
	}
	if (keycode == KEY_A)
	{
		game->player.posX -= game->player.dirY * game->player.move_speed;
		game->player.posY += game->player.dirX * game->player.move_speed;
	}
	if (keycode == KEY_D)
	{
		game->player.posX += game->player.dirY * game->player.move_speed;
		game->player.posY -= game->player.dirX * game->player.move_speed;
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
