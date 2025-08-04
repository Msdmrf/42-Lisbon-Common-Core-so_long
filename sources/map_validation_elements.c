/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_elements.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:54:15 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:23:21 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_walls(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map_width)
	{
		if (game->map[0][x] != WALL
			|| game->map[game->map_height - 1][x] != WALL)
			return (ft_putendl_fd("Error\nMap must be surrounded by walls.", 2),
				0);
		x++;
	}
	y = 0;
	while (y < game->map_height)
	{
		if (game->map[y][0] != WALL
			|| game->map[y][game->map_width - 1] != WALL)
			return (ft_putendl_fd("Error\nMap must be surrounded by walls.", 2),
				0);
		y++;
	}
	return (1);
}

int	check_player(t_game *game)
{
	int	x;
	int	y;
	int	players;

	players = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == PLAYER)
			{
				players++;
				game->player.x = x;
				game->player.y = y;
			}
			x++;
		}
		y++;
	}
	if (players != 1)
		return (ft_putendl_fd("Error\nMap must only have one player.", 2), 0);
	return (1);
}

int	check_collectibles(t_game *game)
{
	int	x;
	int	y;
	int	collectibles;

	collectibles = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == COLLECTIBLE)
				collectibles++;
			x++;
		}
		y++;
	}
	game->collectible.count = collectibles;
	if (collectibles < 1)
	{
		ft_putendl_fd("Error\nMap must have at least one collectible.", 2);
		return (0);
	}
	return (1);
}

int	check_enemies(t_game *game)
{
	int	x;
	int	y;
	int	enemies;

	enemies = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == ENEMY_STATIC
				|| game->map[y][x] == ENEMY_HORIZONTAL
				|| game->map[y][x] == ENEMY_VERTICAL)
				enemies++;
			x++;
		}
		y++;
	}
	game->enemy.count = enemies;
	return (1);
}

int	check_exit(t_game *game)
{
	int	x;
	int	y;
	int	exits;

	exits = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == EXIT)
			{
				exits++;
				game->exit_x = x;
				game->exit_y = y;
			}
			x++;
		}
		y++;
	}
	if (exits != 1)
		return (ft_putendl_fd("Error\nMap must only have one exit.", 2), 0);
	return (1);
}
