/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:44:23 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/02 17:23:41 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_bold_text(t_game *game, int x, int y, int color, char *text)
{
	mlx_string_put(game->mlx, game->win, x, y, color, text);
	mlx_string_put(game->mlx, game->win, x + 1, y, color, text);
	mlx_string_put(game->mlx, game->win, x, y + 1, color, text);
	mlx_string_put(game->mlx, game->win, x + 1, y + 1, color, text);
}

void	print_start(t_game *game)
{
	int	y;

	clear_screen(game, 0x000000);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	if (game->menu_background.img)
		mlx_put_image_to_window(game->mlx, game->win, game->menu_background.img, 0, 0);
	y = HEIGHT / 2 - 50;
	if (game->menu_selection == 0)
		draw_bold_text(game, WIDTH / 2 - 50, y, 0xFF0000, "> START GAME <");
	else
		draw_bold_text(game, WIDTH / 2 - 50, y, 0xFFFFFF, "  START GAME  ");
	y += 70;
	if (game->menu_selection == 1)
		draw_bold_text(game, WIDTH / 2 - 42, y, 0xFF0000, "> CONTROLS <");
	else
		draw_bold_text(game, WIDTH / 2 - 42, y, 0xFFFFFF, "  CONTROLS  ");
	y += 70;
	if (game->menu_selection == 2)
		draw_bold_text(game, WIDTH / 2 - 28, y, 0xFF0000, "> EXIT <");
	else
		draw_bold_text(game, WIDTH / 2 - 28, y, 0xFFFFFF, "  EXIT  ");
	draw_bold_text(game, WIDTH / 2 - 135, HEIGHT - 50,
		0xFF0000, "Use UP/DOWN arrows, ENTER to select");
}

void	handle_start_menu_input(int keycode, t_game *game)
{
	if (keycode == KEY_UP)
		game->menu_selection = (game->menu_selection - 1 + 3) % 3;
	else if (keycode == KEY_DOWN)
		game->menu_selection = (game->menu_selection + 1) % 3;
	else if (keycode == KEY_ENTER)
	{
		if (game->menu_selection == 0)
			game->state = STATE_GAME;
		else if (game->menu_selection == 1)
		{
			game->prev_state = STATE_START;
			game->state = STATE_MENU;
		}
		else if (game->menu_selection == 2)
			xclose(game);
	}
}
