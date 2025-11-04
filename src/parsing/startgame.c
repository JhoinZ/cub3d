/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startgame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:43:07 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/11/04 12:44:03 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_game *game)
{
	int	i;
	int	width;
	int	height;

	i = 0;
	while (i < 4)
	{
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx, 
			game->map.textures[i], &width, &height);
		if (!game->texture[i].img)
			ft_error(12, game);
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,
			&game->texture[i].bpp, &game->texture[i].line_length,
			&game->texture[i].endian);
		game->texture[i].width = width;
		game->texture[i].height = height;
		i++;
	}
}

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
	game->player.move_speed = 2;
	game->player.rot_speed = 0.05;
}
