/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:31:28 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:23:29 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	is_valid_player_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_width
		|| new_y < 0 || new_y >= game->map_height)
		return (0);
	if (game->map[new_y][new_x] == WALL)
		return (0);
	return (1);
}

static void	update_player_position(t_game *game, int new_x, int new_y)
{
	int	old_x;
	int	old_y;

	old_x = game->player.x;
	old_y = game->player.y;
	game->player.x = new_x;
	game->player.y = new_y;
	game->player.moves++;
	handle_tiles(game, new_x, new_y);
	render_tiles(game, old_x, old_y);
	render_tiles(game, new_x, new_y);
	display_move_counter(game);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (!is_valid_player_move(game, new_x, new_y))
		return ;
	update_player_position(game, new_x, new_y);
}

static int	handle_single_key(t_game *game)
{
	if (game->keys.w)
	{
		move_player(game, game->player.x, game->player.y - 1);
		set_player_animation(game, ANIM_WALK_UP);
		return (1);
	}
	else if (game->keys.s)
	{
		move_player(game, game->player.x, game->player.y + 1);
		set_player_animation(game, ANIM_WALK_DOWN);
		return (1);
	}
	else if (game->keys.a)
	{
		move_player(game, game->player.x - 1, game->player.y);
		set_player_animation(game, ANIM_WALK_LEFT);
		return (1);
	}
	else if (game->keys.d)
	{
		move_player(game, game->player.x + 1, game->player.y);
		set_player_animation(game, ANIM_WALK_RIGHT);
		return (1);
	}
	return (0);
}

void	handle_movement(t_game *game, int *alternate)
{
	int	moving;

	moving = 0;
	if ((game->keys.w && game->keys.s) || (game->keys.a && game->keys.d))
	{
		*alternate = 0;
		return ;
	}
	if ((game->keys.w && game->keys.a) || (game->keys.w && game->keys.d)
		|| (game->keys.s && game->keys.a) || (game->keys.s && game->keys.d))
	{
		handle_dual_keys(game, alternate);
		moving = 1;
	}
	else
		moving = handle_single_key(game);
	if (!moving)
		*alternate = 0;
	if (!moving && game->player.state == PLAYER_STATE_MOVING)
		set_player_static(game);
}
