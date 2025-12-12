/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startgame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:43:07 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/12 19:07:28 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_menu_texture(t_game *game, t_data *data)
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

void	load_wall_texture(t_game *game)
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
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_length, &game->img.endian);
	load_wall_texture(game);
	load_menu_texture(game, &game->controls_menu);
	game->menu_background.img = mlx_xpm_file_to_image(game->mlx,
			"textures/Menu_inicial.xpm", &game->menu_background.width,
			&game->menu_background.height);
	if (game->menu_background.img)
		game->menu_background.addr = mlx_get_data_addr(
				game->menu_background.img, &game->menu_background.bpp,
				&game->menu_background.line_length,
				&game->menu_background.endian);
}

static void	ft_set_direction(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.dir_y = -1.0;
		game->player.plane_x = 0.66;
	}
	else if (dir == 'S')
	{
		game->player.dir_y = 1.0;
		game->player.plane_x = -0.66;
	}
	else if (dir == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.plane_y = -0.66;
	}
}

void	ft_init_player_vectors(t_game *game)
{
	ft_set_direction(game, game->player.initial_dir);
	game->player.move_speed = 0.05f;
	game->player.rot_speed = 0.07f;
	game->player.run = 1;
}
