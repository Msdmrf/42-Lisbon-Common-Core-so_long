/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:19:09 by migusant          #+#    #+#             */
/*   Updated: 2025/06/12 19:34:40 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"

// Window Settings
# define TILE_SIZE 32
# define MAX_MAP_WIDTH 60		// 1920px / 32px = 60 tiles exactly
# define MAX_MAP_HEIGHT 33		// 1080px / 32px = 33.75 tiles (33 rounded down)
# define WINDOW_TITLE "so_long"

// Key Codes
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

// Game Elements
# define WALL '1'
# define EMPTY '0'
# define PLAYER 'P'
# define COLLECTIBLE 'C'
# define EXIT 'E'

// Movement Speed
# define MOVEMENT_SPEED 12500

// Key State Structure
typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
}	t_keys;

// Game Structure
typedef struct s_game
{
	void	*mlx;				// MLX connection pointer
	void	*win;				// Window pointer
	char	**map;				// 2D array storing the map layout
	int		map_width;			// Width of the map in tiles
	int		map_height;			// Height of the map in tiles
	int		player_x;			// Player's X position on map
	int		player_y;			// Player's Y position on map
	int		collectibles;		// Total number of collectibles
	int		collected;			// Number of collected items
	int		moves;				// Number of player moves
	void	*wall_img;			// Wall texture image
	void	*floor_img;			// Floor texture image
	void	*player_img;		// Player texture image
	void	*collectible_img;	// Collectible texture image
	void	*exit_img;			// Exit texture image
	int		img_width;			// Width of loaded textures
	int		img_height;			// Height of loaded textures
	t_keys	keys;				// Currently pressed keys
	int		move_counter;		// Simple counter for movement timing
}	t_game;

// Game Lifecycle Functions
void	init_game(t_game *game);
int		load_map(t_game *game, char *filename);
int		init_window(t_game *game);
void	free_map(char **map);
int		close_game(t_game *game);

// Map Validation Functions
int		check_file_extension(char *filename);
int		check_rectangular(t_game *game);
int		check_map_size(t_game *game);
int		check_walls(t_game *game);
int		check_invalid_chars(t_game *game);
int		check_player(t_game *game);
int		check_collectibles(t_game *game);
int		check_exit(t_game *game);
int		check_path(t_game *game);
int		validate_map(t_game *game, char *filename);

// Handle Functions
void	handle_tiles(t_game *game, int new_x, int new_y);
void	handle_player(t_game *game, int new_x, int new_y);
void	handle_movement(t_game *game, int *alternate);
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		game_loop(t_game *game);

// Rendering Functions
int		render_images(t_game *game);
void	render_tiles(t_game *game, int x, int y);
void	render_map(t_game *game);

#endif