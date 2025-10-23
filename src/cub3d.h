/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:08:18 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/23 17:00:25 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include "../Libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"


typedef struct s_mlx_tools
{
	mlx_t			*window;
}	t_mlx_tools;

typedef struct s_color
{
	int r;
	int a;
	int b;
}	t_color;

typedef struct s_map_tools
{
	char			**map;
	char			**m_map;
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	char			player_dir;
}	t_map_tools;

typedef struct s_tools
{
	t_mlx_tools		mlx;
	t_map_tools		map;
	bool			status;
	char			*tex_no;
	char			*tex_so;
	char			*tex_we;
	char			*tex_ea;
	t_color			floor_color;
	t_color			ceil_color;
}	t_tools;

/* parsing functions */
int ft_parse_file(const char *path, t_tools *tools);
int ft_parse_config(int fd, t_tools *tools);
int ft_create_map(char **lines, int nlines, t_tools *tools);
int ft_validate_map_closure(t_tools *tools);


#endif