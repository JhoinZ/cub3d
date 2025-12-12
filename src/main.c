/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:07:42 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/12 11:47:55 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_menu_states(t_game *game)
{
	if (game->state == STATE_START)
		print_start(game);
	else if (game->state == STATE_MENU)
		print_menu(game);
	else if (game->state == STATE_MAP)
	{
		clear_screen(game, 0x000C0C0C);
		ray_casting_loop(game);
		print_map(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	}
}

int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->state != STATE_GAME)
	{
		handle_menu_states(game);
		return (0);
	}
	player_actions(game);
	clear_screen(game, 0x000C0C0C);
	ray_casting_loop(game);
	print_mini_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_full_parsing(av, ac, &game);
	ft_init_player_vectors(&game);
	ft_setup_mlx_and_game(&game);
	game.state = STATE_START;
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, EVENT_CLOSE_BTN, 1L << 0, xclose, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
