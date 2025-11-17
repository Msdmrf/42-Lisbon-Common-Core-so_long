/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:28 by migusant          #+#    #+#             */
/*   Updated: 2025/11/07 12:30:24 by migusant         ###   ########.fr       */
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

static void	cleanup_and_exit(t_game *game, int exit_code)
{
	if (game->enemies.enemy)
		free(game->enemies.enemy);
	if (game->map)
	{
		free_map(game->map);
		game->map = NULL;
	}
	destroy_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(exit_code);
}

int	close_game(t_game *game)
{
	cleanup_and_exit(game, 0);
	return (0);
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

int	main(int argc, char **argv)
{
	static t_game	game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file.ber>\n", argv[0]);
		return (1);
	}
	if (!load_map(&game, argv[1]))
		return (cleanup_and_exit(&game, 1), 1);
	if (!init_window(&game))
		return (cleanup_and_exit(&game, 1), 1);
	if (!load_sprites(&game))
		return (cleanup_and_exit(&game, 1), 1);
	if (!init_enemies(&game))
		return (cleanup_and_exit(&game, 1), 1);
	render_map(&game);
	ft_printf("Game initialized successfully!\n");
	ft_printf("Hold WASD to move continuously, ESC or [X] to quit.\n");
	ft_printf("Avoid enemies or you'll lose the game!\n");
	mlx_hook(game.win, DestroyNotify, NoEventMask, close_game, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, handle_keypress, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, handle_keyrelease, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
