/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_diagonal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:25:36 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:23:32 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	handle_w_a_movement(t_game *game, int *alternate)
{
	if (*alternate % 2 == 0)
	{
		move_player(game, game->player.x, game->player.y - 1);
		set_player_animation(game, ANIM_WALK_UP);
	}
	else
	{
		move_player(game, game->player.x - 1, game->player.y);
		set_player_animation(game, ANIM_WALK_LEFT);
	}
}

static void	handle_w_d_movement(t_game *game, int *alternate)
{
	if (*alternate % 2 == 0)
	{
		move_player(game, game->player.x, game->player.y - 1);
		set_player_animation(game, ANIM_WALK_UP);
	}
	else
	{
		move_player(game, game->player.x + 1, game->player.y);
		set_player_animation(game, ANIM_WALK_RIGHT);
	}
}

static void	handle_s_a_movement(t_game *game, int *alternate)
{
	if (*alternate % 2 == 0)
	{
		move_player(game, game->player.x, game->player.y + 1);
		set_player_animation(game, ANIM_WALK_DOWN);
	}
	else
	{
		move_player(game, game->player.x - 1, game->player.y);
		set_player_animation(game, ANIM_WALK_LEFT);
	}
}

static void	handle_s_d_movement(t_game *game, int *alternate)
{
	if (*alternate % 2 == 0)
	{
		move_player(game, game->player.x, game->player.y + 1);
		set_player_animation(game, ANIM_WALK_DOWN);
	}
	else
	{
		move_player(game, game->player.x + 1, game->player.y);
		set_player_animation(game, ANIM_WALK_RIGHT);
	}
}

void	handle_dual_keys(t_game *game, int *alternate)
{
	if (game->keys.w && game->keys.a)
		handle_w_a_movement(game, alternate);
	else if (game->keys.w && game->keys.d)
		handle_w_d_movement(game, alternate);
	else if (game->keys.s && game->keys.a)
		handle_s_a_movement(game, alternate);
	else if (game->keys.s && game->keys.d)
		handle_s_d_movement(game, alternate);
	(*alternate)++;
}
