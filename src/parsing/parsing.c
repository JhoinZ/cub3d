/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:12:45 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/26 19:12:48 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_tools(t_tools *tools)
{
	ft_memset(tools, 0, sizeof(t_tools));
	tools->mlx_ptr = NULL;
	tools->win_ptr = NULL;
	tools->tex_no = NULL;
	tools->tex_so = NULL;
	tools->tex_we = NULL;
	tools->tex_ea = NULL;
	tools->map_grid = NULL;
	tools->map_height = 0;
	tools->map_width = 0;
	tools->elements_count = 0;
	tools->status = false;
	tools->player.initial_dir = 0;
}

int	ft_check_argv(char **av, int ac)
{
	int	fd;

	if (ac != 2)
		ft_error();
	else if (!ft_endwith(av[1], ".cub"))
		ft_error();
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_error();
	return (fd);
}

void	ft_full_parsing(char **av, int ac, t_tools *tools)
{
	int		fd;
	char	*map_buffer;

	ft_init_tools(tools);
	fd = ft_check_argv(av, ac);
	map_buffer = ft_parse_config(fd, tools);
}
