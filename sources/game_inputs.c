/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:25:36 by migusant          #+#    #+#             */
/*   Updated: 2025/06/17 16:37:49 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	return (0);
}

static void	handle_wa_wd(t_game *game, int *alternate)
{
	if (game->keys.w && game->keys.a)
	{
		if (*alternate % 2 == 0)
			handle_player(game, game->player_x, game->player_y - 1);
		else
			handle_player(game, game->player_x - 1, game->player_y);
	}
	else if (game->keys.w && game->keys.d)
	{
		if (*alternate % 2 == 0)
			handle_player(game, game->player_x, game->player_y - 1);
		else
			handle_player(game, game->player_x + 1, game->player_y);
	}
}

static void	handle_sa_sd(t_game *game, int *alternate)
{
	if (game->keys.s && game->keys.a)
	{
		if (*alternate % 2 == 0)
			handle_player(game, game->player_x, game->player_y + 1);
		else
			handle_player(game, game->player_x - 1, game->player_y);
	}
	else if (game->keys.s && game->keys.d)
	{
		if (*alternate % 2 == 0)
			handle_player(game, game->player_x, game->player_y + 1);
		else
			handle_player(game, game->player_x + 1, game->player_y);
	}
}

void	handle_dual_keys(t_game *game, int *alternate)
{
	if ((game->keys.w && game->keys.a) || (game->keys.w && game->keys.d))
		handle_wa_wd(game, alternate);
	else if ((game->keys.s && game->keys.a) || (game->keys.s && game->keys.d))
		handle_sa_sd(game, alternate);
	(*alternate)++;
}
