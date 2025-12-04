/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startgame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:43:07 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/04 16:56:13 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_game *game, t_data *data)
{
	int	width;
	int	height;

	data->img = mlx_xpm_file_to_image(game->mlx,
			"textures/MenuControles.xpm", &width, &height);
	if (!data->img)
		ft_error(12, game);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_length, &data->endian);
	data->width = width;
	data->height = height;
}

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
		game->texture[i].addr = mlx_get_data_addr(
				game->texture[i].img, &game->texture[i].bpp,
				&game->texture[i].line_length, &game->texture[i].endian);
		game->texture[i].width = width;
		game->texture[i].height = height;
		i++;
	}
}

static void	ft_setup_main_image(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->img.img == NULL)
		ft_error(4, game);
	game->img.addr = mlx_get_data_addr(
			game->img.img,
			&game->img.bpp,
			&game->img.line_length,
			&game->img.endian);
}

static void	ft_setup_menu_background(t_game *game)
{
	game->menu_background.img = mlx_xpm_file_to_image(game->mlx,
			"textures/Menu_inicial.xpm",
			&game->menu_background.width,
			&game->menu_background.height);
	if (game->menu_background.img)
		game->menu_background.addr = mlx_get_data_addr(
				game->menu_background.img, &game->menu_background.bpp,
				&game->menu_background.line_length,
				&game->menu_background.endian);
}

void	ft_setup_mlx_and_game(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		ft_error(4, game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (game->win == NULL)
		ft_error(4, game);
	ft_setup_main_image(game);
	load_textures(game);
	load_texture(game, &game->controls_menu);
	ft_setup_menu_background(game);
}

static void	ft_set_direction_north(t_game *game)
{
	game->player.dirY = -1.0;
	game->player.planeX = 0.66;
}

static void	ft_set_direction_south(t_game *game)
{
	game->player.dirY = 1.0;
	game->player.planeX = -0.66;
}

static void	ft_set_direction_east(t_game *game)
{
	game->player.dirX = 1.0;
	game->player.planeY = 0.66;
}

static void	ft_set_direction_west(t_game *game)
{
	game->player.dirX = -1.0;
	game->player.planeY = -0.66;
}

static void	ft_set_player_speeds(t_game *game)
{
	game->player.move_speed = 0.05f;
	game->player.rot_speed = 0.07f;
	game->player.run = 1;
}

void	ft_init_player_vectors(t_game *game)
{
	char	dir;

	dir = game->player.initial_dir;
	if (dir == 'N')
		ft_set_direction_north(game);
	else if (dir == 'S')
		ft_set_direction_south(game);
	else if (dir == 'E')
		ft_set_direction_east(game);
	else if (dir == 'W')
		ft_set_direction_west(game);
	ft_set_player_speeds(game);
}
