/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:29:06 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/30 10:20:42 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_mem(t_tools *tools)
{
	if (!tools)
		return;
	if (tools->tex_no != NULL)
	{
		free(tools->tex_no);
		tools->tex_no = NULL;
	}
	if (tools->tex_so != NULL)
	{
		free(tools->tex_so);
		tools->tex_so = NULL;
	}
	if (tools->tex_we != NULL)
	{
		free(tools->tex_we);
		tools->tex_we = NULL;
	}
	if (tools->tex_ea != NULL)
	{
		free(tools->tex_ea);
		tools->tex_ea = NULL;
	}
	if (tools->map_grid != NULL)
	{
		ft_free_split(tools->map_grid);
		tools->map_grid = NULL;
	}
	if (tools->mlx_ptr != NULL)
	{
		if (tools->win_ptr != NULL)
		{
			mlx_destroy_window(tools->mlx_ptr, tools->win_ptr);
			tools->win_ptr = NULL;
		}
		mlx_destroy_display(tools->mlx_ptr);
		free(tools->mlx_ptr);
		tools->mlx_ptr = NULL;
	}
}

void	ft_error(int error_code, t_tools *tools)
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
	ft_free_mem(tools);
	exit(EXIT_FAILURE);
}

void	ft_error_light(int error_code)
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
	exit(EXIT_FAILURE);
}
