/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:55:56 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/15 12:16:26 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_texture(char *data, t_game *game, char *id)
{
	if (!ft_strncmp(id, "NO", 2))
	{
		if (game->map.textures[0] != NULL)
			ft_error(6, game);
		game->map.textures[0] = ft_strdup(ft_skipspace(data + 2));
	}
	if (!ft_strncmp(id, "SO", 2))
	{
		if (game->map.textures[1] != NULL)
			ft_error(6, game);
		game->map.textures[1] = ft_strdup(ft_skipspace(data + 2));
	}
	if (!ft_strncmp(id, "WE", 2))
	{
		if (game->map.textures[2] != NULL)
			ft_error(6, game);
		game->map.textures[2] = ft_strdup(ft_skipspace(data + 2));
	}
	if (!ft_strncmp(id, "EA", 2))
	{
		if (game->map.textures[3] != NULL)
			ft_error(6, game);
		game->map.textures[3] = ft_strdup(ft_skipspace(data + 2));
	}
}

bool	ft_parse_rgb_component(char *s, int *out_value)
{
	int	i;
	int	v;

	i = 0;
	s = ft_skipspace(s);
	if (*s == '\0' || !ft_isdigit((unsigned char)*s))
		return (false);
	while (ft_isdigit((unsigned char)s[i]))
		i++;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] != '\0')
		return (false);
	v = ft_atoi(s);
	if (v < 0 || v > 255)
		return (false);
	*out_value = v;
	return (true);
}

static bool	ft_parse_and_validate_rgb(char **parts, int *rgb, t_game *game)
{
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		ft_free_split(parts);
		ft_error(5, game);
		return (false);
	}
	if (!ft_parse_rgb_component(parts[0], &rgb[0])
		|| !ft_parse_rgb_component(parts[1], &rgb[1])
		|| !ft_parse_rgb_component(parts[2], &rgb[2]))
	{
		ft_free_split(parts);
		ft_error(5, game);
		return (false);
	}
	return (true);
}

static void	ft_assign_color(int color, char *id, t_game *game)
{
	if (!ft_strncmp(id, "F", 1))
	{
		if (game->map.floor_color != -1)
			ft_error(6, game);
		game->map.floor_color = color;
	}
	else if (!ft_strncmp(id, "C", 1))
	{
		if (game->map.ceiling_color != -1)
			ft_error(6, game);
		game->map.ceiling_color = color;
	}
}

void	ft_color(char *data, t_game *game, char *id)
{
	char	**parts;
	int		rgb[3];

	if (!data)
		ft_error(7, game);
	parts = ft_split(ft_skipspace(data + 1), ',');
	if (!parts)
		ft_error(10, game);
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	ft_parse_and_validate_rgb(parts, rgb, game);
	ft_assign_color(create_trgb(0, rgb[0], rgb[1], rgb[2]), id, game);
	ft_free_split(parts);
}
