/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:12:45 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/15 12:59:03 by fsaffiri         ###   ########.fr       */
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
		ft_texture(data, game, "NO");
	else if (!ft_strncmp(data, "SO ", 3))
		ft_texture(data, game, "SO");
	else if (!ft_strncmp(data, "WE ", 3))
		ft_texture(data, game, "WE");
	else if (!ft_strncmp(data, "EA ", 3))
		ft_texture(data, game, "EA");
	else if (!ft_strncmp(data, "F ", 2))
		ft_color(data, game, "F");
	else if (!ft_strncmp(data, "C ", 2))
		ft_color(data, game, "C");
	else
		return (0);
	return (1);
}

static void	ft_process_config_line(t_game *game, char **map_buffer)
{
	if (ft_checkspace(game->line))
		free(game->line);
	else
	{
		if (game->map.elements_count == 6)
		{
			*map_buffer = ft_strjoin_free(*map_buffer, game->line, 3);
			if (!*map_buffer)
				ft_error(10, game);
		}
		else if (ft_parse_element(game->line, game))
		{
			game->map.elements_count++;
			free(game->line);
			game->line = NULL;
		}
		else
			ft_error(5, game);
	}
}

char	*ft_parse_config(int fd, t_game *game)
{
	char	*map_buffer;
	size_t	len;

	map_buffer = NULL;
	while (1)
	{
		game->line = get_next_line(fd);
		if (!game->line)
			break ;
		if (game->map.elements_count != 6)
		{
			len = ft_strlen(game->line);
			if (len > 0 && game->line[len - 1] == '\n')
				game->line[len - 1] = '\0';
		}
		ft_process_config_line(game, &map_buffer);
	}
	if (game->map.elements_count < 6)
		ft_error(7, game);
	if (!map_buffer)
		ft_error(3, game);
	return (map_buffer);
}

void	ft_full_parsing(char **av, int ac, t_game *game)
{
	char	*map_buffer;
	double	aspect_map;
	double	aspect_screen;

	ft_init_tools(game);
	game->fd_config = ft_check_argv(av, ac);
	map_buffer = ft_parse_config(game->fd_config, game);
	close(game->fd_config);
	game->fd_config = -1;
	ft_create_map(map_buffer, game);
	ft_validate_map(game);
	if (game->map.width == 0)
		ft_error(11, game);
	aspect_map = (double)game->map.width / (double)game->map.height;
	aspect_screen = (double)WIDTH / (double)HEIGHT;
	if (aspect_map <= aspect_screen)
		game->map.tile_size = (HEIGHT / game->map.height);
	else
		game->map.tile_size = (WIDTH / game->map.width);
}
