/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:46 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/29 17:58:41 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	game_loop(void *param)
{
	t_game			*game;
	int				size_player;
	
	game = (t_game *)param;
	player_actions(game);
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
		if (!game->init_screen)
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
	init_textures(&game);
	
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
