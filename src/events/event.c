/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:47:00 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/02 16:59:24 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	xclose(t_game *game)
{
	ft_error(0, game);
	return (0);
}

// Main function when a key is pressed
int	key_press(int keycode, t_game *game)
{
	if (game->state == STATE_START)
		handle_start_menu_input(keycode, game);
	if (keycode == KEY_ESC)
		xclose(game);
	else if (keycode == KEY_W)
		game->keys.key_w = 1;
	else if (keycode == KEY_A)
		game->keys.key_a = 1;
	else if (keycode == KEY_S)
		game->keys.key_s = 1;
	else if (keycode == KEY_D)
		game->keys.key_d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.key_left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.key_right = 1;
	else if (keycode == KEY_E)
		game->keys.key_e = 1;
	else if (keycode == KEY_SHIFT)
		game->player.run = 2;
	else
   		printf("Kecode of the key pressed: %d\n", keycode);
	return (0);
}

void	player_actions(t_game *game)
{
	if (game->state == STATE_GAME)
	{
		player_move(game);
		if (game->keys.key_left)
			rot_move(&game->player, -1);
		if (game->keys.key_right)
			rot_move(&game->player, 1);
	}
}

// Main function when a key is released
int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		xclose(game);
	if (keycode == KEY_W)
		game->keys.key_w = 0;
	if (keycode == KEY_A)
		game->keys.key_a = 0;
	if (keycode == KEY_S)
		game->keys.key_s = 0;
	if (keycode == KEY_D)
		game->keys.key_d = 0;
	if (keycode == KEY_LEFT)
		game->keys.key_left = 0;
	if (keycode == KEY_RIGHT)
		game->keys.key_right = 0;
	if (keycode == KEY_E)
		game->keys.key_e = 0;
	if (keycode == KEY_SHIFT)
		game->player.run = 1;
	if (keycode == KEY_M && game->state == STATE_MAP)
		game->state = STATE_GAME;
	else if (keycode == KEY_M && game->state == STATE_GAME)
		game->state = STATE_MAP;
	if (keycode == KEY_TAB && game->state == STATE_MENU)
	{
		if (game->prev_state == STATE_START)
			game->state = STATE_START;
		else
			game->state = STATE_GAME;
	}
	else if (keycode == KEY_TAB && game->state == STATE_GAME)
	{
		game->prev_state = STATE_GAME;
		game->state = STATE_MENU;
	}
	if (keycode == KEY_ESC && game->state == STATE_MENU)
	{
		if (game->prev_state == STATE_START)
			game->state = STATE_START;
		else
			game->state = STATE_GAME;
	}
	return (0);
}
