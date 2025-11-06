/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_animations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:32:59 by migusant          #+#    #+#             */
/*   Updated: 2025/11/05 18:57:28 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	render_all_by_type(t_game *game, char type)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (type == COLLECTIBLE && game->map[y][x] == COLLECTIBLE)
				render_tiles(game, x, y);
			else if ((type == ENEMY_STATIC || type == ENEMY_HORIZONTAL
					|| type == ENEMY_VERTICAL)
				&& (game->map[y][x] == ENEMY_STATIC
				|| game->map[y][x] == ENEMY_HORIZONTAL
				|| game->map[y][x] == ENEMY_VERTICAL))
				render_tiles(game, x, y);
			x++;
		}
		y++;
	}
}

void	update_collectible_sprites(t_game *game)
{
	game->collectible.anim_timer++;
	if (game->collectible.anim_timer >= COLLECTIBLE_TIMER)
	{
		game->collectible.anim_timer = 0;
		game->collectible.curr_frame = (game->collectible.curr_frame + 1)
			% ANIMATION_FRAMES;
		render_all_by_type(game, COLLECTIBLE);
	}
}

void	update_enemy_sprites(t_game *game)
{
	int	i;

	game->enemies.anim_timer++;
	if (game->enemies.anim_timer >= ENEMY_TIMER)
	{
		game->enemies.anim_timer = 0;
		i = 0;
		while (i < game->enemies.count)
		{
			game->enemies.enemy[i].curr_frame
				= (game->enemies.enemy[i].curr_frame + 1) % ANIMATION_FRAMES;
			i++;
		}
		render_all_by_type(game, ENEMY_STATIC);
	}
}

static void	handle_static_to_idle_transition(t_game *game)
{
	game->player.idle_timer++;
	if (game->player.idle_timer >= PLAYER_IDLE_DELAY)
	{
		game->player.state = PLAYER_STATE_IDLE;
		game->player.curr_frame = 0;
		game->player.anim_timer = 0;
		if (game->player.last_direction == DIRECTION_DOWN)
			game->player.curr_anim = ANIM_IDLE_DOWN;
		else if (game->player.last_direction == DIRECTION_UP)
			game->player.curr_anim = ANIM_IDLE_UP;
		else if (game->player.last_direction == DIRECTION_LEFT)
			game->player.curr_anim = ANIM_IDLE_LEFT;
		else if (game->player.last_direction == DIRECTION_RIGHT)
			game->player.curr_anim = ANIM_IDLE_RIGHT;
	}
}

void	update_player_sprites(t_game *game)
{
	if (game->player.state == PLAYER_STATE_STATIC)
		handle_static_to_idle_transition(game);
	else if (game->player.state == PLAYER_STATE_IDLE)
	{
		game->player.anim_timer++;
		if (game->player.anim_timer >= PLAYER_TIMER)
		{
			game->player.anim_timer = 0;
			game->player.curr_frame = (game->player.curr_frame + 1)
				% ANIMATION_FRAMES;
			render_tiles(game, game->player.x, game->player.y);
		}
	}
	else if (game->player.state == PLAYER_STATE_MOVING)
	{
		game->player.anim_timer++;
		if (game->player.anim_timer >= PLAYER_TIMER)
		{
			game->player.anim_timer = 0;
			game->player.curr_frame = (game->player.curr_frame + 1)
				% ANIMATION_FRAMES;
			render_tiles(game, game->player.x, game->player.y);
		}
	}
}
