/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:12:45 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/11/06 18:44:31 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_parse_element(char *line, t_game *game)
{
	char	*data;

	data = ft_skipspace(line);
	if (data[0] == '\0')
		return (0);
	if (!ft_strncmp(data, "NO ", 3))
		return (ft_texture(data, game, "NO"), 1);
	else if (!ft_strncmp(data, "SO ", 3))	
		return (ft_texture(data, game, "SO"), 1);
	else if (!ft_strncmp(data, "WE ", 3))
		return (ft_texture(data, game, "WE"), 1);
	else if (!ft_strncmp(data, "EA ", 3))
		return (ft_texture(data, game, "EA"), 1);
	else if (!ft_strncmp(data, "F ", 2))
		return (ft_color(data, game, "F"), 1);
	else if (!ft_strncmp(data, "C ", 2))
		return (ft_color(data, game, "C"), 1);
	else
		return (0);
}

char	*ft_parse_config(int fd, t_game *game)
{
	size_t	_len;
	char	*map_buffer;
	char	*line;

	map_buffer = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (game->map.elements_count != 6)
		{
			_len = ft_strlen(line);
			if (_len > 0 && line[_len - 1] == '\n')
				line[_len - 1] = '\0';
		}
		if (ft_checkspace(line))
			free(line);
		else
		{
			if (game->map.elements_count == 6)
				map_buffer = ft_strjoin(map_buffer, line);
			else if (ft_parse_element(line, game))
			{
				game->map.elements_count++;
				free(line);
			}
			else
			{
				free(line);
				ft_error(5, game);
			}
		}
	}
	if (game->map.elements_count < 6)
		ft_error(7, game);
	if (!map_buffer)
		ft_error(3, game);
	return (map_buffer);
}

void	ft_full_parsing(char **av, int ac, t_game *game)
{
	int		fd;
	char	*map_buffer;

	ft_init_tools(game);
	fd = ft_check_argv(av, ac);
	map_buffer = ft_parse_config(fd, game);
	close(fd);
	ft_create_map(map_buffer, game);
	ft_validate_map(game);
	if (game->map.width == 0)
		ft_error(11, game);
	game->map.tile_size = (WIDTH / game->map.width);
	game->player.posX = game->player.posX;
	game->player.posY = game->player.posY;
}
