/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:07:42 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/11/27 18:10:29 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(void *param)
{
	t_game	*game;
	
	game = (t_game *)param;
	player_actions(game);
	clear_screen(game, 0x000C0C0C);
	ray_casting_loop(game);
	print_mini_map(game);
	if (game->in_menu == 2)
		print_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	if (game->in_menu == 1)
		print_menu(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_full_parsing(av, ac, &game);
	ft_init_player_vectors(&game);
	ft_setup_mlx_and_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, EVENT_CLOSE_BTN, 1L << 0, xclose, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
