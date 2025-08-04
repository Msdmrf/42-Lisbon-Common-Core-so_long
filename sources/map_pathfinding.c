/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pathfinding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:35:14 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:23:16 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_path(t_game *game)
{
	char	**map_copy;

	map_copy = copy_map(game);
	if (!map_copy)
	{
		ft_putendl_fd("Error\nMemory allocation failed.", 2);
		return (0);
	}
	flood_fill(map_copy, game->player.x, game->player.y, game);
	if (!is_reachable(game, map_copy))
	{
		free_map(map_copy);
		ft_putendl_fd("Error\nNo valid path to all collectibles and exit.", 2);
		return (0);
	}
	free_map(map_copy);
	return (1);
}

char	**copy_map(t_game *game)
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
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

int	flood_fill(char **map, int x, int y, t_game *game)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height
		|| map[y][x] == WALL || map[y][x] == ENEMY_STATIC
		|| map[y][x] == ENEMY_HORIZONTAL || map[y][x] == ENEMY_VERTICAL
		|| map[y][x] == 'V')
		return (0);
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
	return (1);
}

int	is_reachable(t_game *game, char **map_copy)
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
				&& map_copy[i][j] != 'V')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
