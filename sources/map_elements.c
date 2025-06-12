/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:54:15 by migusant          #+#    #+#             */
/*   Updated: 2025/06/12 19:34:53 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_width)
	{
		if (game->map[0][i] != WALL
			|| game->map[game->map_height - 1][i] != WALL)
		{
			ft_putendl_fd("Error\nMap must be surrounded by walls.", 2);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][0] != WALL
			|| game->map[i][game->map_width - 1] != WALL)
		{
			ft_putendl_fd("Error\nMap must be surrounded by walls.", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_invalid_chars(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] != WALL && game->map[i][j] != EMPTY
				&& game->map[i][j] != PLAYER && game->map[i][j] != COLLECTIBLE
				&& game->map[i][j] != EXIT)
			{
				ft_putendl_fd("Error\nInvalid character in map.", 2);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_player(t_game *game)
{
	int	i;
	int	j;
	int	players;

	players = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == PLAYER)
			{
				players++;
				game->player_x = j;
				game->player_y = i;
			}
			j++;
		}
		i++;
	}
	if (players != 1)
		return (ft_putendl_fd("Error\nMap must only have one player.", 2), 0);
	return (1);
}

int	check_collectibles(t_game *game)
{
	int	i;
	int	j;
	int	collectibles;

	collectibles = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == COLLECTIBLE)
				collectibles++;
			j++;
		}
		i++;
	}
	game->collectibles = collectibles;
	if (collectibles < 1)
	{
		ft_putendl_fd("Error\nMap must have at least one collectible.", 2);
		return (0);
	}
	return (1);
}

int	check_exit(t_game *game)
{
	int	i;
	int	j;
	int	exits;

	exits = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == EXIT)
				exits++;
			j++;
		}
		i++;
	}
	if (exits != 1)
	{
		ft_putendl_fd("Error\nMap must only have one exit.", 2);
		return (0);
	}
	return (1);
}
