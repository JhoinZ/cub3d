/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:07:42 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/30 11:42:10 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(char **av, int ac)
{
	t_tools	tools;

	ft_full_parsing(av, ac, &tools);
	ft_init_player_vectors(&tools);
	ft_setup_mlx_and_game(&tools);
	ft_run_game_loop(&tools);
	return (0);
}
