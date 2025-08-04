/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:46:54 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:23:02 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_enemy(t_enemy *enemy, int x, int y, char type)
{
	enemy->x = x;
	enemy->y = y;
	enemy->start_x = x;
	enemy->start_y = y;
	enemy->type = type;
	enemy->direction = 0;
	enemy->current_anim = ANIM_IDLE_DOWN;
	enemy->frame = 0;
	enemy->state = ENEMY_STATE_MOVING;
	enemy->static_frame = DIRECTION_DOWN;
	enemy->static_timer = 0;
	if (type != ENEMY_STATIC)
		enemy->direction = 1;
}

void	init_enemy_patrol(t_game *game)
{
	int	i;
	int	x;
	int	y;

	game->enemy.patrol = malloc(sizeof(t_enemy) * game->enemy.count);
	if (!game->enemy.patrol)
		return ;
	i = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == ENEMY_STATIC
				|| game->map[y][x] == ENEMY_HORIZONTAL
				|| game->map[y][x] == ENEMY_VERTICAL)
				init_enemy(&game->enemy.patrol[i++], x, y, game->map[y][x]);
			x++;
		}
		y++;
	}
}

void	update_enemy_states(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy.count)
	{
		if (game->enemy.patrol[i].state == ENEMY_STATE_STATIC)
		{
			game->enemy.patrol[i].static_timer++;
			if (game->enemy.patrol[i].static_timer >= ENEMY_STATIC_DELAY)
			{
				game->enemy.patrol[i].state = ENEMY_STATE_MOVING;
				game->enemy.patrol[i].static_timer = 0;
			}
		}
		i++;
	}
}

void	set_enemy_static_frame(t_enemy *enemy)
{
	if (enemy->type == ENEMY_HORIZONTAL)
	{
		if (enemy->direction > 0)
			enemy->static_frame = DIRECTION_DOWN;
		else
			enemy->static_frame = DIRECTION_UP;
	}
	else if (enemy->type == ENEMY_VERTICAL)
	{
		if (enemy->direction > 0)
			enemy->static_frame = DIRECTION_RIGHT;
		else
			enemy->static_frame = DIRECTION_LEFT;
	}
}

void	set_enemy_animation(t_enemy *enemy)
{
	if (enemy->type == ENEMY_HORIZONTAL)
	{
		if (enemy->direction > 0)
			enemy->current_anim = 4;
		else
			enemy->current_anim = 3;
	}
	else if (enemy->type == ENEMY_VERTICAL)
	{
		if (enemy->direction > 0)
			enemy->current_anim = 1;
		else
			enemy->current_anim = 2;
	}
}
