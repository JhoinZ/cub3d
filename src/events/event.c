/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:47:00 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/23 16:33:54 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Closes the window when X is clicked and finish with a clean exit
int	xclose(t_game *game)
{
	clean_exit(0, game, NULL);
	return (0);
}

// Main function when a key is clicked
int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		xclose(game);
    printf("Kecode of the key pressed: %d\n", keycode);
	return (0);
}

