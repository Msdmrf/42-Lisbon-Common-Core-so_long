/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_core.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:20:00 by migusant          #+#    #+#             */
/*   Updated: 2025/11/05 19:23:25 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
	{
		ft_putendl_fd("Error\nMap file must have .ber extension.", 2);
		return (0);
	}
	if (!ft_strnstr(filename + len - 4, ".ber", 4))
	{
		ft_putendl_fd("Error\nMap file must have .ber extension.", 2);
		return (0);
	}
	return (1);
}

static int	check_rectangular(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		if ((int)ft_strlen(game->map[i]) != game->map_width)
		{
			ft_putendl_fd("Error\nMap must be rectangular.", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_map_size(t_game *game)
{
	if ((game->map_width < 3 || game->map_height < 5)
		&& (game->map_width < 5 || game->map_height < 3))
	{
		ft_putendl_fd("Error\nMap too small (minimum 3x5 or 5x3).", 2);
		return (0);
	}
	if (game->map_width > MAX_MAP_WIDTH || game->map_height > MAX_MAP_HEIGHT)
	{
		ft_printf("Error\nMap too large (maximum %dx%d).",
			MAX_MAP_WIDTH, MAX_MAP_HEIGHT);
		return (0);
	}
	return (1);
}

static int	check_invalid_chars(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] != WALL && game->map[y][x] != EMPTY
				&& game->map[y][x] != PLAYER && game->map[y][x] != COLLECTIBLE
				&& game->map[y][x] != EXIT && game->map[y][x] != ENEMY_STATIC
				&& game->map[y][x] != ENEMY_HORIZONTAL
				&& game->map[y][x] != ENEMY_VERTICAL)
			{
				ft_putendl_fd("Error\nInvalid character in map.", 2);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_game *game, char *filename)
{
	if (!check_file_extension(filename)
		|| !check_rectangular(game)
		|| !check_map_size(game)
		|| !check_invalid_chars(game)
		|| !check_walls(game)
		|| !check_player(game)
		|| !check_collectibles(game)
		|| !check_enemies(game)
		|| !check_path(game)
		|| !check_exit(game))
		return (0);
	ft_printf("Map validation successful!\n");
	ft_printf("Map size: %dx%d\n", game->map_width, game->map_height);
	ft_printf("Player at: (%d, %d)\n", game->player.x, game->player.y);
	ft_printf("Collectibles: %d\n", game->collectible.count);
	ft_printf("Enemies: %d\n", game->enemies.count);
	return (1);
}
