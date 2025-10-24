/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:46 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/24 13:00:10 by fosuna-g         ###   ########.fr       */
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

int	main(void)
{
	t_game	game;

	game = init_game();
	
	//draw_with_shading(&game.img);
	mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
	mlx_hook(game.win, EVENT_CLOSE_BTN, 1L<<0, xclose, &game);
	//mlx_hook(game.win, 2, 1L<<0, windows_close, &game); // this is for keydown
	mlx_key_hook(game.win, key_hook, &game); // this is for keyup
	
	game.player_x = 400;
	game.player_y = 300;
	game.frame_count = 0;
	
	mlx_loop_hook(game.mlx, animation_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
