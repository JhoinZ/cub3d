/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:29:06 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/05 16:43:48 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_free_map_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->map.textures[i] != NULL)
		{
			free(game->map.textures[i]);
			game->map.textures[i] = NULL;
		}
		i++;
	}
	if (game->menu_background.img)
	{
		mlx_destroy_image(game->mlx, game->menu_background.img);
		game->menu_background.img = NULL;
	}
	if (game->controls_menu.img)
	{
		mlx_destroy_image(game->mlx, game->controls_menu.img);
		game->controls_menu.img = NULL;
	}
	if (game->img.img)
	{
		mlx_destroy_image(game->mlx, game->img.img);
		game->img.img = NULL;
	}
}

static void	ft_free_game_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture[i].img)
		{
			mlx_destroy_image(game->mlx, game->texture[i].img);
			game->texture[i].img = NULL;
		}
		i++;
	}
	if (game->img.img)
	{
		mlx_destroy_image(game->mlx, game->img.img);
		game->img.img = NULL;
	}
}

static void	ft_destroy_window(t_game *game)
{
	if (game->win != NULL)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	mlx_loop_end(game->mlx);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	game->mlx = NULL;
}

void	ft_free_mem(t_game *game)
{
	if (!game)
		return ;
	ft_free_map_textures(game);
	if (game->map.grid != NULL)
	{
		ft_free_split(game->map.grid);
		game->map.grid = NULL;
	}
	if (game->mlx != NULL)
	{
		ft_free_game_images(game);
		ft_destroy_window(game);
	}
}

static const char	*ft_get_error_message(int error_code)
{
	static const char *const	g_error[] = {
		"Fatal: Unknown Error. The program closed due to an anomaly.\n",
		"Usage: The program requires exactly one argument.\n",
		"File Error: Scene file extension must be .cub.\n",
		"File Error: Unable to open, read, or access file.\n",
		"MLX Error: Failed to initialize or create window.\n",
		"Parsing: Unrecognized line or invalid syntax.\n",
		"Parsing: Duplicate configuration element.\n",
		"Parsing: Missing configuration elements.\n",
		"Map: Invalid character in grid.\n",
		"Map: Must have exactly one starting position.\n",
		"Memory: Allocation failed during map creation.\n",
		"Map: Map is not enclosed (Flood Fill Failed).\n",
		"Texture: Failed to load texture file.\n"
	};

	if (error_code > 0 && error_code <= 12)
		return (g_error[error_code]);
	return (g_error[0]);
}

void	ft_error(int error_code, t_game *game)
{
	if (error_code == 0)
	{
		ft_free_mem(game);
		exit(EXIT_SUCCESS);
	}
	ft_putstr_fd(RED"Error\n"RST, 2); 
	ft_putstr_fd((char *)ft_get_error_message(error_code), 2);
	ft_putstr_fd(RST, 2);
	ft_free_mem(game);
	exit(EXIT_FAILURE);
}

void	ft_error_light(int error_code)
{
	printf(RED"Error:\n"RST);
	printf(WIT"%s"RST, ft_get_error_message(error_code));
	exit(EXIT_FAILURE);
}
