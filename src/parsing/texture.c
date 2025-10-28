/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:55:56 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/28 11:52:11 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_texture(char *data, t_tools *tools, char *id)
{
	if (!ft_strncmp(id, "NO", 2))
	{
		if (tools->tex_no != NULL)
			ft_error(6, tools);
		tools->tex_no = ft_strdup(ft_skipspace(data + 2));
	}
	if (!ft_strncmp(id, "SO", 2))
	{
		if (tools->tex_so != NULL)
			ft_error(6, tools);
		tools->tex_so = ft_strdup(ft_skipspace(data + 2));
	}
	if (!ft_strncmp(id, "WE", 2))
	{
		if (tools->tex_we != NULL)
			ft_error(6, tools);
		tools->tex_we = ft_strdup(ft_skipspace(data + 2));
	}
	if (!ft_strncmp(id, "EA", 2))
	{
		if (tools->tex_ea != NULL)
			ft_error(6, tools);
		tools->tex_ea = ft_strdup(ft_skipspace(data + 2));
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

void	ft_color(char *data, t_tools *tools, char *id)
{
	char	**parts;
	int	r;
	int	g;
	int	b;

	if (!data)
		ft_error(3, tools);
	parts = ft_split(ft_skipspace(data + 1), ',');
	if (!parts)
		ft_error(3, tools);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		ft_free_split(parts);
		ft_error(3, tools);
	}
	if (!ft_parse_rgb_component(parts[0], &r)
		|| !ft_parse_rgb_component(parts[1], &g)
		|| !ft_parse_rgb_component(parts[2], &b))
	{
		ft_free_split(parts);
		ft_error(3, tools);
	}
	if (!ft_strncmp(id, "F", 1))
	{
		if (tools->floor_color.r != 0 || tools->floor_color.g != 0
			|| tools->floor_color.b != 0)
			ft_error(5, tools);
		tools->floor_color.r = r;
		tools->floor_color.g = g;
		tools->floor_color.b = b;
	}
	else if (!ft_strncmp(id, "C", 1))
	{
		if (tools->ceil_color.r != 0 || tools->ceil_color.g != 0
			|| tools->ceil_color.b != 0)
			ft_error(5, tools);
		tools->ceil_color.r = r;
		tools->ceil_color.g = g;
		tools->ceil_color.b = b;
	}
	ft_free_split(parts);
}
