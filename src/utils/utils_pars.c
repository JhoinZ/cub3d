/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:09:23 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/02 13:00:58 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_tools(t_game *game)
{
	int i;

	ft_memset(game, 0, sizeof(t_game));
	game->mlx = NULL;
	game->win = NULL;
	i = 0;
	while (i < 4)
		game->map.textures[i++] = NULL;
	game->map.grid = NULL;
	game->map.height = 0;
	game->map.width = 0;
	game->map.elements_count = 0;
	game->map.floor_color = -1;
	game->map.ceiling_color = -1;
	game->status = false;
	game->player.initial_dir = 0;
	game->in_menu = 0;
}

int	ft_check_argv(char **av, int ac)
{
	int	fd;

	if (ac != 2)
		ft_error_light(1);
	else if (!ft_endwith(av[1], ".cub"))
		ft_error_light(2);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_error_light(3);
	return (fd);
}

char	*ft_skipspace(char *str)
{
	size_t	i;
	char	*ptr;

	ptr = str;
	i = 0;
	while (ptr[i] != '\0' && (ptr[i] == ' ' || ptr[i] == '\t' || ptr[i] == '\n'
			|| ptr[i] == '\v' || ptr[i] == '\f' || ptr[i] == '\r'))
		i++;
	return (&ptr[i]);
}

int	ft_endwith(char *str, char *suffix)
{
	size_t	len_str;
	size_t	len_suffix;
	size_t	start_i;

	if (!str || !suffix)
		return (0);
	len_str = ft_strlen(str);
	len_suffix = ft_strlen(suffix);
	if (len_suffix > len_str)
		return (0);
	start_i = len_str - len_suffix;
	if (ft_strncmp(&str[start_i], suffix, len_suffix) != 0)
		return (0);
	return (1);
}

int	ft_checkspace(char *line)
{
	int	i;

	if (line == NULL)
		return (1);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\v' && line[i] != '\f' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}
