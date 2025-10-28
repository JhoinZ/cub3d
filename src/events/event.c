/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:47:00 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/28 11:26:25 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Closes the window when X is clicked and finish with a clean exit
int	xclose(t_game *game)
{
	clean_exit(0, game, NULL);
	return (0);
}

// Main function when a key is pressed
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		xclose(game);
	else if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S ||
			keycode == KEY_D)
		player_move(game, keycode);
	else if (keycode == KEY_LEFT)
		rot_move(&game->player, -1);
	else if (keycode == KEY_RIGHT)
		rot_move(&game->player, 1);
	else
   		printf("Kecode of the key pressed: %d\n", keycode);
	return (0);
}

// Main function when a key is released
int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		xclose(game);
	return (0);
}

