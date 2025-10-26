/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:21:40 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/26 16:55:29 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_parse_element(char *line,t_tools *tools)
{
	char	*data;

	data = ft_skipspace(line);
	if (data[0] == '\0')
		return (0);
	if (!ft_strncmp(data, "NO ", 3))
	{
		ft_texture(data, tools, "NO");
		return (1);
	}
	else if (!ft_strncmp(data, "SO ", 3))
	{
		ft_texture(data, tools, "SO");
		return (1);
	}
	else if (!ft_strncmp(data, "WE ", 3))
	{
		ft_texture(data, tools, "WE");
		return (1);
	}
	else if (!ft_strncmp(data, "EA ", 3))
	{
		ft_texture(data, tools, "EA");
		return (1);
	}
	else if (!ft_strncmp(data, "F ", 2))
	{
		ft_color(data, tools, "F");
		return (1);
	}
	else if (!ft_strncmp(data, "C ", 2))
	{
		ft_color(data, tools, "C");
		return (1);
	}
	else
		return (0);
}

char	*ft_parse_config(int fd, t_tools *tools)
{
	char	*map_buffer;
	char	*line;
	
	map_buffer = NULL;
	line = NULL;
	while (17)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_checkspace(line))
			free(line);
		else
		{
			if (tools->elements_count == 6)
				map_buffer = ft_strjoin(map_buffer, line);
			else if (ft_parse_element(line, tools))
			{
				tools->elements_count++;
				free(line);
			}
			else
			{
				free(line);
				ft_error();
			}
		}
	}
	if (tools->elements_count < 6)
		ft_error();
	if (!map_buffer)
		ft_error();
	return (map_buffer);
}
