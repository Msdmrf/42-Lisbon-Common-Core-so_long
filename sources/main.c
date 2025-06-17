/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:28 by migusant          #+#    #+#             */
/*   Updated: 2025/06/17 16:46:00 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putendl_fd("Error: MLX initialization failed.", 2);
		return (0);
	}
	game->win = mlx_new_window(game->mlx,
			game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, WINDOW_TITLE);
	if (!game->win)
	{
		ft_putendl_fd("Error: Window creation failed.", 2);
		return (0);
	}
	return (1);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	close_game(t_game *game)
{
	if (game->enemy_patrol)
		free(game->enemy_patrol);
	if (game->map)
		free_map(game->map);
	if (game->mlx)
	{
		if (game->wall_img)
			mlx_destroy_image(game->mlx, game->wall_img);
		if (game->floor_img)
			mlx_destroy_image(game->mlx, game->floor_img);
		if (game->player_img)
			mlx_destroy_image(game->mlx, game->player_img);
		if (game->collectible_img)
			mlx_destroy_image(game->mlx, game->collectible_img);
		if (game->exit_img)
			mlx_destroy_image(game->mlx, game->exit_img);
		if (game->enemy_img)
			mlx_destroy_image(game->mlx, game->enemy_img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	static t_game	game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file.ber>\n", argv[0]);
		return (1);
	}
	if (!load_map(&game, argv[1]))
		return (close_game(&game), 1);
	if (!init_window(&game))
		return (close_game(&game), 1);
	if (!render_images(&game))
		return (close_game(&game), 1);
	init_enemy_patrol(&game);
	render_map(&game);
	ft_printf("Game initialized successfully!\n");
	ft_printf("Hold WASD to move continuously, ESC or [X] to quit.\n");
	ft_printf("Avoid enemies or you'll lose the game!\n");
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 3, 1L << 1, handle_keyrelease, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
