/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:21:40 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/25 16:25:05 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_parse_element(char *line,t_tools *tools)
{}

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
	if (tools->elements_count < 6)
		ft_error();
	if (!map_buffer)
		ft_error();
	return (map_buffer);
}
