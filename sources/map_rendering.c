/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:40:33 by migusant          #+#    #+#             */
/*   Updated: 2025/06/12 19:35:02 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	render_image(t_game *game, void **img, char *path)
{
	*img = mlx_xpm_file_to_image(game->mlx, path,
			&game->img_width, &game->img_height);
	if (!*img)
	{
		ft_printf("Error\nCould not load image: %s\n", path);
		return (0);
	}
	return (1);
}

int	render_images(t_game *game)
{
	if (!render_image(game, &game->wall_img, "assets/wall.xpm"))
		return (0);
	if (!render_image(game, &game->floor_img, "assets/floor.xpm"))
		return (0);
	if (!render_image(game, &game->player_img, "assets/player.xpm"))
		return (0);
	if (!render_image(game, &game->collectible_img, "assets/collectible.xpm"))
		return (0);
	if (!render_image(game, &game->exit_img, "assets/exit.xpm"))
		return (0);
	return (1);
}

static void	render_tile(t_game *game, int x, int y, void *img)
{
	mlx_put_image_to_window(game->mlx, game->win, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	render_tiles(t_game *game, int x, int y)
{
	render_tile(game, x, y, game->floor_img);
	if (game->map[y][x] == WALL)
		render_tile(game, x, y, game->wall_img);
	else if (game->map[y][x] == COLLECTIBLE)
		render_tile(game, x, y, game->collectible_img);
	else if (game->map[y][x] == EXIT)
		render_tile(game, x, y, game->exit_img);
	if (game->player_x == x && game->player_y == y)
		render_tile(game, x, y, game->player_img);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_tiles(game, x, y);
			x++;
		}
		y++;
	}
}
