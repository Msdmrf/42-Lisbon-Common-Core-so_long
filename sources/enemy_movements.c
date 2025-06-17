/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:46:54 by migusant          #+#    #+#             */
/*   Updated: 2025/06/17 17:09:27 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	is_enemy(char c)
{
	return (c == ENEMY_STATIC || c == ENEMY_HORIZONTAL || c == ENEMY_VERTICAL);
}

static int	is_valid_move(t_game *game, int x, int y, t_enemy *moving_enemy)
{
	int	i;

	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (0);
	if (game->map[y][x] == WALL || game->map[y][x] == COLLECTIBLE
		|| game->map[y][x] == EXIT || is_enemy(game->map[y][x]))
		return (0);
	if (moving_enemy != NULL)
	{
		i = 0;
		while (i < game->enemy_count)
		{
			if (&game->enemy_patrol[i] != moving_enemy
				&& game->enemy_patrol[i].x == x
				&& game->enemy_patrol[i].y == y)
				return (0);
			i++;
		}
	}
	return (1);
}

void	init_enemy(t_enemy *enemy, int x, int y, char type)
{
	enemy->x = x;
	enemy->y = y;
	enemy->start_x = x;
	enemy->start_y = y;
	enemy->type = type;
	enemy->direction = 0;
	if (type != ENEMY_STATIC)
		enemy->direction = 1;
}

void	init_enemy_patrol(t_game *game)
{
	int	i;
	int	x;
	int	y;

	game->enemy_patrol = malloc(sizeof(t_enemy) * game->enemy_count);
	if (!game->enemy_patrol)
		return ;
	i = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (is_enemy(game->map[y][x]))
				init_enemy(&game->enemy_patrol[i++], x, y, game->map[y][x]);
			x++;
		}
		y++;
	}
}

void	move_enemy(t_game *game, t_enemy *enemy)
{
	int	new_x;
	int	new_y;

	if (enemy->type == ENEMY_STATIC)
		return ;
	new_x = enemy->x;
	new_y = enemy->y;
	if (enemy->type == ENEMY_HORIZONTAL)
		new_x += enemy->direction;
	else if (enemy->type == ENEMY_VERTICAL)
		new_y += enemy->direction;
	if (!is_valid_move(game, new_x, new_y, enemy))
	{
		enemy->direction *= -1;
		return ;
	}
	game->map[enemy->y][enemy->x] = EMPTY;
	render_tiles(game, enemy->x, enemy->y);
	enemy->x = new_x;
	enemy->y = new_y;
	game->map[enemy->y][enemy->x] = enemy->type;
	render_tiles(game, enemy->x, enemy->y);
	if (game->player_x == enemy->x && game->player_y == enemy->y)
		handle_enemy(game);
}

void	update_enemy(t_game *game)
{
	int	i;

	game->enemy_timer++;
	if (game->enemy_timer < ENEMY_TIMER)
		return ;
	game->enemy_timer = 0;
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemy_patrol[i].direction != 0)
			move_enemy(game, &game->enemy_patrol[i]);
		i++;
	}
}
