/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:07:42 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/11/24 20:26:32 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map1(t_game *game, int rel_width, int rel_begin)
{
	int i;
	int	j;
	int	rel_hegith;
	
	i = 0;
	rel_hegith = (HEIGHT / game->map.height);
	while (i < game->map.width)
	{
		j = 0;
		while (j < game->map.height)
		{
			rel_width = i * game->map.tile_size + rel_begin;
			rel_hegith = j * game->map.tile_size;
			if (game->map.grid[j][i] > '0' && game->map.grid[j][i] <= '9')
				draw_square(&game->img, rel_width, rel_hegith, game->map.tile_size, 0xFF81D8D0);	
			else
				draw_square(&game->img, rel_width, rel_hegith, game->map.tile_size, 0xFF084D6E);	
			draw_square2(&game->img, rel_width, rel_hegith, game->map.tile_size, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_map2(t_game *game, int rel_height, int rel_begin)
{
	int i;
	int	j;
	int	rel_width;
	
	i = 0;
	rel_width = (WIDTH / game->map.width);
	while (i < game->map.width)
	{
		j = 0;
		while (j < game->map.height)
		{
			rel_width = i * game->map.tile_size;
			rel_height = j * game->map.tile_size + rel_begin;
			if (game->map.grid[j][i] > '0' && game->map.grid[j][i] <= '9')
				draw_square(&game->img, rel_width, rel_height, game->map.tile_size, 0xFF81D8D0);	
			else
				draw_square(&game->img, rel_width, rel_height, game->map.tile_size, 0xFF084D6E);	
			draw_square2(&game->img, rel_width, rel_height, game->map.tile_size, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	print_menu(t_game *game)
{
	int	x;
	int	y;

	clear_screen(game, 0x000C0C0C);
	x = (WIDTH - game->controls_menu.width) / 2;
	y = (HEIGHT - game->controls_menu.height) / 2;
	mlx_put_image_to_window(game->mlx, game->win, game->controls_menu.img, x, y);
}

void	print_map(t_game *game)
{
	int	posX;
	int	posY;
	int	pS;

	clear_screen(game, 0x000C0C0C);
	if (WIDTH / game->map.tile_size > (game->map.width + 1))
	{
		pS = (WIDTH / 2) - (game->map.tile_size * game->map.width / 2);
		posX = game->player.posX * game->map.tile_size + pS;
		posY = game->player.posY * game->map.tile_size;
		draw_map1(game, game->map.tile_size, pS);
	}
	else
	{
		pS = (HEIGHT / 2) - (game->map.tile_size * game->map.height / 2);
		posX = game->player.posX * game->map.tile_size;
		posY = game->player.posY * game->map.tile_size + pS;
		draw_map2(game, game->map.tile_size, pS);
	}
	pS = (int)game->map.tile_size * 0.25;
	draw_square(&game->img, (posX - pS / 2), (posY - pS / 2), pS, 0x00FF00);
}

int	game_loop(void *param)
{
	t_game	*game;
	
	game = (t_game *)param;
	player_actions(game);
	clear_screen(game, 0x000C0C0C);
	ray_casting_loop(game);
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
