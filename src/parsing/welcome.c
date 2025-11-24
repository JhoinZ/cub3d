/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:44:23 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/11/24 19:33:46 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_img(t_game *game)
{
	game->menu_background.img = mlx_xpm_file_to_image(game->mlx,
			"textures/menu_background.xpm",
			&game->menu_background.width,
			&game->menu_background.height);
	if (!game->menu_background.img)
		ft_error(3, game);
}

void	draw_menu(t_game *game)
{
	init_img(game);
	mlx_put_image_to_window(game->mlx, game->win, game->menu_background.img, 0, 0);
	mlx_string_put(game->mlx, game->win, 500, 200, 0xFFFFFF, "CUB3D - IL GIOCO");
	if (game->menu_selection == 0)
		mlx_string_put(game->mlx, game->win, 550, 350, 0xFF0000, "> START GAME <");
	else
		mlx_string_put(game->mlx, game->win, 550, 350, 0xFFFFFF, "  START GAME  ");
    if (game->menu_selection == 1)
	{
		mlx_string_put(game->mlx, game->win, 550, 400, 0xFF0000, "> EXIT <");
	}
	else
	{
		mlx_string_put(game->mlx, game->win, 550, 400, 0xFFFFFF, "  EXIT  ");
	}
}
