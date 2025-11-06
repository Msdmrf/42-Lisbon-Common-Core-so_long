/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pathfinding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:35:14 by migusant          #+#    #+#             */
/*   Updated: 2025/11/05 18:56:51 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		if (!map_copy[i])
		{
			free_map(map_copy);
			map_copy = NULL;
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

static int	flood_fill(t_game *game, char **map, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height
		|| map[y][x] == WALL || map[y][x] == ENEMY_STATIC
		|| map[y][x] == ENEMY_HORIZONTAL || map[y][x] == ENEMY_VERTICAL
		|| map[y][x] == 'V')
		return (0);
	map[y][x] = 'V';
	flood_fill(game, map, x + 1, y);
	flood_fill(game, map, x - 1, y);
	flood_fill(game, map, x, y + 1);
	flood_fill(game, map, x, y - 1);
	return (1);
}

static int	is_reachable(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if ((game->map[i][j] == COLLECTIBLE || game->map[i][j] == EXIT)
				&& map[i][j] != 'V')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_path(t_game *game)
{
	char	**map_copy;

	map_copy = copy_map(game);
	if (!map_copy)
	{
		ft_putendl_fd("Error\nMemory allocation failed.", 2);
		return (0);
	}
	flood_fill(game, map_copy, game->player.x, game->player.y);
	if (!is_reachable(game, map_copy))
	{
		free_map(map_copy);
		map_copy = NULL;
		ft_putendl_fd("Error\nNo valid path to all collectibles and exit.", 2);
		return (0);
	}
	free_map(map_copy);
	map_copy = NULL;
	return (1);
}
