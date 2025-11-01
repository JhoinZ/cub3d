/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startgame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:43:07 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/11/01 16:21:20 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_setup_mlx_and_game(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		ft_error(4, game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (game->win == NULL)
		ft_error(4, game);
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->img.img == NULL)
		ft_error(4, game);
	game->img.addr = mlx_get_data_addr(
			game->img.img,
			&game->img.bpp,
			&game->img.line_length,
			&game->img.endian);
	load_textures(game);
	/* hook setup is handled in main.c currently */
}

void	ft_init_player_vectors(t_game *game)
{
	char	dir;

	dir = game->player.initial_dir;
	if (dir == 'N')
	{
		game->player.dirY = -1.0;
		game->player.planeX = 0.66;
	}
	else if (dir == 'S')
	{
		game->player.dirY = 1.0;
		game->player.planeX = -0.66;
	}
	else if (dir == 'E')
	{
		game->player.dirX = 1.0;
		game->player.planeY = 0.66;
	}
	else if (dir == 'W')
	{
		game->player.dirX = -1.0;
		game->player.planeY = -0.66;
	}
}
