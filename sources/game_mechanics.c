/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mechanics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:07:29 by migusant          #+#    #+#             */
/*   Updated: 2025/06/12 19:34:46 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

static void	handle_dual_keys(t_game *game, int *alternate)
{
	if ((game->keys.w && game->keys.a) || (game->keys.w && game->keys.d))
		handle_wa_wd(game, alternate);
	else if ((game->keys.s && game->keys.a) || (game->keys.s && game->keys.d))
		handle_sa_sd(game, alternate);
	(*alternate)++;
}

void	handle_movement(t_game *game, int *alternate)
{
	if ((game->keys.w && game->keys.s) || (game->keys.a && game->keys.d))
	{
		*alternate = 0;
		return ;
	}
	if ((game->keys.w && game->keys.a) || (game->keys.w && game->keys.d)
		|| (game->keys.s && game->keys.a) || (game->keys.s && game->keys.d))
		handle_dual_keys(game, alternate);
	else if (game->keys.w)
		handle_player(game, game->player_x, game->player_y - 1);
	else if (game->keys.s)
		handle_player(game, game->player_x, game->player_y + 1);
	else if (game->keys.a)
		handle_player(game, game->player_x - 1, game->player_y);
	else if (game->keys.d)
		handle_player(game, game->player_x + 1, game->player_y);
	else
		*alternate = 0;
}
