/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:21:40 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/26 20:42:36 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_create_map(char *map_buffer, t_tools *tools)
{
	int	row_indx;
	int	player_count;

	player_count = 0;
	if (!map_buffer)
		ft_error();
	tools->map_grid = ft_split(map_buffer, '\n');
	free(map_buffer);
	row_indx = 0;
	tools->map_width = 0;
	while (tools->map_grid[row_indx])
	{
		
	}
}