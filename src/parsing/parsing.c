/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:12:45 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/04 16:59:40 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_parse_texture_element(char *data, t_game *game)
{
	if (!ft_strncmp(data, "NO ", 3))
		ft_texture(data, game, "NO");
	else if (!ft_strncmp(data, "SO ", 3))
		ft_texture(data, game, "SO");
	else if (!ft_strncmp(data, "WE ", 3))
		ft_texture(data, game, "WE");
	else if (!ft_strncmp(data, "EA ", 3))
		ft_texture(data, game, "EA");
	else
		return (0);
	return (1);
}

static int	ft_parse_color_element(char *data, t_game *game)
{
	if (!ft_strncmp(data, "F ", 2))
		ft_color(data, game, "F");
	else if (!ft_strncmp(data, "C ", 2))
		ft_color(data, game, "C");
	else
		return (0);
	return (1);
}

int	ft_parse_element(char *line, t_game *game)
{
	char	*data;

	data = ft_skipspace(line);
	if (data[0] == '\0')
		return (0);
	if (ft_parse_texture_element(data, game))
		return (1);
	if (ft_parse_color_element(data, game))
		return (1);
	return (0);
}

static void	ft_process_config_line(char *line, t_game *game, char **map_buffer)
{
	if (ft_checkspace(line))
		free(line);
	else
	{
		if (game->map.elements_count == 6)
			*map_buffer = ft_strjoin(*map_buffer, line);
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

static void	ft_strip_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

char	*ft_parse_config(int fd, t_game *game)
{
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
			ft_strip_newline(line);
		ft_process_config_line(line, game, &map_buffer);
	}
	if (game->map.elements_count < 6)
		ft_error(7, game);
	if (!map_buffer)
		ft_error(3, game);
	return (map_buffer);
}

static void	ft_calculate_tile_size(t_game *game)
{
	double	aspect_ratio_map;
	double	aspect_ratio_screen;

	aspect_ratio_map = (double)game->map.width / (double)game->map.height;
	aspect_ratio_screen = (double)WIDTH / (double)HEIGHT;
	if (aspect_ratio_map <= aspect_ratio_screen)
		game->map.tile_size = (HEIGHT / game->map.height);
	else
		game->map.tile_size = (WIDTH / game->map.width);
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
	ft_calculate_tile_size(game);
}
