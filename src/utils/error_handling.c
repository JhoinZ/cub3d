/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:29:06 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/11/01 16:38:15 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_mem(t_game *game)
{
	int i;

	if (!game)
		return ;
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
	if (game->map.grid != NULL)
	{
		ft_free_split(game->map.grid);
		game->map.grid = NULL;
	}
	if (game->mlx != NULL)
	{
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
}

void	ft_error(int error_code, t_game *game)
{
	const char	*message;
	static const char 	*g_error_message[] = {
		"Fatal: Unknown Error. The program closed due to an anomaly.\n", // 0 default
		"Usage: The program requires exactly one argument (path to .cub file).\n", // 1 usage error
		"File Error: Scene file extension must be .cub.\n", // 2 file error
		"File Error: Unable to open, read, or access the scene file.\n", // 3 file error
		"MLX Error: Failed to initialize graphics connection or create window.\n", // 4 mlx error
		"Parsing: Unrecognized line or invalid syntax in configuration file.\n", // 5 syntax error
		"Parsing: Duplicate configuration element (Texture/Color).\n", // 6 dup texture
		"Parsing: Missing configuration elements (NO, SO, WE, EA, F, C).\n", // 7 missing conf
		"Map: Invalid character in grid ('0', '1', ' ', 'N', 'S', 'E', 'W').\n", // 8 map invalid
		"Map: Must have exactly one starting position ('N', 'S', 'E', 'W').\n", // 9 inalid player
		"Memory: Allocation failed during map creation or grid rectification.\n", // 10 mem allocation
		"Map: Map is not enclosed or free space found on the border (Flood Fill Failed).\n" // 11 map open
	};

	if (error_code > 0 && error_code < 12)
		message = g_error_message[error_code];
	else
		message = g_error_message[0];
	printf(RED"Error:\n"RST);
	printf(WIT"%s"RST, message);
	ft_free_mem(game);
	exit(EXIT_FAILURE);
}

void	ft_error_light(int error_code)
{
	const char			*message;
	static const char	*g_error_message[] = {
		"Fatal: Unknown Error. The program closed due to an anomaly.\n", // 0 default
		"Usage: The program requires exactly one argument (path to .cub file).\n", // 1 usage error
		"File Error: Scene file extension must be .cub.\n", // 2 file error
		"File Error: Unable to open, read, or access the scene file.\n", // 3 file error
		"MLX Error: Failed to initialize graphics connection or create window.\n", // 4 mlx error
		"Parsing: Unrecognized line or invalid syntax in configuration file.\n", // 5 syntax error
		"Parsing: Duplicate configuration element (Texture/Color).\n", // 6 dup texture
		"Parsing: Missing configuration elements (NO, SO, WE, EA, F, C).\n", // 7 missing conf
		"Map: Invalid character in grid ('0', '1', ' ', 'N', 'S', 'E', 'W').\n", // 8 map invalid
		"Map: Must have exactly one starting position ('N', 'S', 'E', 'W').\n", // 9 inalid player
		"Memory: Allocation failed during map creation or grid rectification.\n", // 10 mem allocation
		"Map: Map is not enclosed or free space found on the border (Flood Fill Failed).\n" // 11 map open
	};

	if (error_code > 0 && error_code < 12)
		message = g_error_message[error_code];
	else
		message = g_error_message[0];
	printf(RED"Error:\n"RST);
	printf(WIT"%s"RST, message);
	exit(EXIT_FAILURE);
}
