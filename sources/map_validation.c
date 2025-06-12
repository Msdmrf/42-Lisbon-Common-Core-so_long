/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:20:00 by migusant          #+#    #+#             */
/*   Updated: 2025/06/12 19:35:05 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_file_extension(char *filename)
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

int	check_rectangular(t_game *game)
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

int	check_map_size(t_game *game)
{
	if ((game->map_width < 3 || game->map_height < 5)
		&& (game->map_width < 5 || game->map_height < 3))
	{
		ft_putendl_fd("Error\nMap too small (minimum 3x5 or 5x3).", 2);
		return (0);
	}
	if (game->map_width > MAX_MAP_WIDTH || game->map_height > MAX_MAP_HEIGHT)
	{
		ft_printf("Error\nMap too large (maximum %dx%d).\n",
			MAX_MAP_WIDTH, MAX_MAP_HEIGHT);
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game, char *filename)
{
	if (!check_file_extension(filename))
		return (0);
	if (!check_rectangular(game))
		return (0);
	if (!check_map_size(game))
		return (0);
	if (!check_walls(game))
		return (0);
	if (!check_invalid_chars(game))
		return (0);
	if (!check_player(game))
		return (0);
	if (!check_collectibles(game))
		return (0);
	if (!check_exit(game))
		return (0);
	if (!check_path(game))
		return (0);
	ft_printf("Map validation successful!\n");
	ft_printf("Map size: %dx%d\n", game->map_width, game->map_height);
	ft_printf("Player at: (%d, %d)\n", game->player_x, game->player_y);
	ft_printf("Collectibles: %d\n", game->collectibles);
	return (1);
}
