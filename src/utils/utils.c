/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:50:00 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/30 12:17:02 by fosuna-g         ###   ########.fr       */
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
	if (map && map->grid)
	{
		free(map->grid);
		free(map->textures);
		map->grid = NULL;
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
	if (game->map.grid)
		free_map(&game->map);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_loop_end(game->mlx);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(n);
}
