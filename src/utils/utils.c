/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:50:00 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/11/01 16:38:11 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

void	display_error(int n, char *msg)
{
	ft_putstr_fd("\n========= \033[0;31mError\033[0m =========\n", 2);
	if (n == 0 && msg)
	{
		ft_putstr_fd("   ➤ ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	free_textures(t_game *game)
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
}

void	free_map(t_map *map)
{
	int i;

	if (map && map->grid)
	{
		/* map->grid was allocated via ft_split / malloc per row */
		ft_free_split(map->grid);
		map->grid = NULL;
	}
	/* free any texture path strings if allocated */
	if (map)
	{
		i = 0;
		while (i < 4)
		{
			if (map->textures[i])
			{
				free(map->textures[i]);
				map->textures[i] = NULL;
			}
			i++;
		}
	}
}

/* Clean up game resources and exit. 
 * n: exit code (0 = success, other = error)
 * game: game data to clean up (can be NULL)
 * msg: error message to display if n != 0
 */
void	clean_exit(int n, t_game *game, char *msg)
{
	if (n != 0)
		display_error(0, msg);
	if (!game)
		exit(n);
	/* Delegate full cleanup to ft_free_mem which handles images, textures,
	   map grid, window and mlx teardown. This centralizes resource freeing
	   and avoids ordering/double-free issues. */
	ft_free_mem(game);
	exit(n);
}
