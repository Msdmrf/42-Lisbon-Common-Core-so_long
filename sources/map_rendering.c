/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:40:33 by migusant          #+#    #+#             */
/*   Updated: 2025/06/17 16:51:18 by migusant         ###   ########.fr       */
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
	if (!render_image(game, &game->wall_img, "textures/wall.xpm"))
		return (0);
	if (!render_image(game, &game->floor_img, "textures/floor.xpm"))
		return (0);
	if (!render_image(game, &game->player_img, "textures/player.xpm"))
		return (0);
	if (!render_image(game, &game->collectible_img, "textures/collectible.xpm"))
		return (0);
	if (!render_image(game, &game->enemy_img, "textures/enemy.xpm"))
		return (0);
	if (!render_image(game, &game->exit_img, "textures/exit_locked.xpm"))
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
	else if (game->map[y][x] == ENEMY_STATIC
			|| game->map[y][x] == ENEMY_HORIZONTAL
			|| game->map[y][x] == ENEMY_VERTICAL)
		render_tile(game, x, y, game->enemy_img);
	else if (game->map[y][x] == COLLECTIBLE)
		render_tile(game, x, y, game->collectible_img);
	else if (game->map[y][x] == EXIT)
		render_tile(game, x, y, game->exit_img);
	if (game->player_x == x && game->player_y == y)
		render_tile(game, x, y, game->player_img);
}

void	display_move_counter(t_game *game)
{
	char	*moves_str;
	char	*moves_num;

	moves_num = ft_itoa(game->player_moves);
	if (!moves_num)
		return ;
	moves_str = ft_strjoin("Moves: ", moves_num);
	free(moves_num);
	if (!moves_str)
		return ;
	mlx_put_image_to_window(game->mlx, game->win, game->wall_img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->wall_img, 32, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->wall_img, 64, 0);
	mlx_string_put(game->mlx, game->win, 9, 19, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 10, 19, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 11, 19, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 9, 20, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 11, 20, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 9, 21, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 10, 21, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 11, 21, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, moves_str);
	free(moves_str);
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
	display_move_counter(game);
}
