/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:46 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/28 12:33:14 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_game init_game(void)
{
	t_game	game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Cub3D");
	game.img.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
									&game.img.line_length, &game.img.endian);
	return (game);
}

t_player	init_player(t_game *game)
{
	t_player player;

	(void)game;
	player.posX = game->map.tile_size * 2 + ((WIDTH - (game->map.tile_size * game->map.width)) / 2) + (game->map.tile_size / 2);
	player.posY = game->map.tile_size * 4 - (game->map.tile_size / 2);
	player.dirX = 0;
	player.dirY = -1;
	player.planeX = 0.66f;
	player.planeY = 0;
	player.rot_speed = 0.07f;
	player.move_speed = (WIDTH * HEIGHT) * 1.0e-5;
	return (player);
}

t_map	init_map()
{
	t_map	map;

	map.width = 9;
	map.height = 7;
	map.grid = malloc(sizeof(char *) * map.height);
	map.grid[0] = "111111111";
	map.grid[1] = "100000001";
	map.grid[2] = "100000101";
	map.grid[3] = "100000001";
	map.grid[4] = "100100001";
	map.grid[5] = "100010001";
	map.grid[6] = "111111111";
	map.ceiling_color = 0x0074D4FF;
	map.floor_color = 0x003F3F46;
	if ((WIDTH / map.width) > (HEIGHT / map.height))
		map.tile_size = (HEIGHT / map.height);
	else
		map.tile_size = (WIDTH / map.width);
	return (map);
}


int	game_loop(void *param)
{
	t_game			*game;
	int				size_player;
	
	game = (t_game *)param;
	clear_screen(game, 0x00224466);
	if (DEBUG)
	{
		draw_map(game);
		size_player = (int)(game->map.tile_size / (game->player.move_speed * 1.5));
		draw_square(&game->img, (int)(game->player.posX - (size_player / 2)),
				(int)(game->player.posY - (size_player / 2)), size_player, 0x00FF00);
		draw_multiple_rays(game, WIDTH);
	}
	else
	{
		ray_casting_loop(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;
	
	game = init_game();
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_hook(game.win, EVENT_CLOSE_BTN, 1L<<0, xclose, &game);
	game.map = init_map();
	game.player = init_player(&game);
	
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
