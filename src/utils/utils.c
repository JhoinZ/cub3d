/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:50:00 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/11/06 17:04:28 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

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
		ft_free_split(map->grid);
		map->grid = NULL;
	}
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
