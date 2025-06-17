/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:19:09 by migusant          #+#    #+#             */
/*   Updated: 2025/06/17 17:01:57 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include "../libft/includes/libft.h"
#include "../minilibx-linux/mlx.h"

// Window Settings
#define TILE_SIZE 32
#define MAX_MAP_WIDTH 60  // 1920px / 32px = 60 tiles exactly
#define MAX_MAP_HEIGHT 33 // 1080px / 32px = 33.75 tiles (33 rounded down)
#define WINDOW_TITLE "so_long"

// Key Codes
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

// Game Elements
#define WALL '1'
#define EMPTY '0'
#define PLAYER 'P'
#define COLLECTIBLE 'C'
#define ENEMY_STATIC 'S'
#define ENEMY_HORIZONTAL 'H'
#define ENEMY_VERTICAL 'V'
#define EXIT 'E'

// Movement Speed
#define PLAYER_TIMER 7000
#define ENEMY_TIMER 14000

// Key State Structure
typedef struct s_keys
{
	int w;
	int a;
	int s;
	int d;
} t_keys;

// Enemy Structure
typedef struct s_enemy
{
	int start_x;   // Enemy's starting X position on map
	int start_y;   // Enemy's starting Y position on map
	int x;		   // Enemy's X position on map
	int y;		   // Enemy's Y position on map
	char type;	   // Enemy type (S, H, or V)
	int direction; // 1 = right/down, -1 = left/up
} t_enemy;

typedef struct s_game
{
	void *mlx;			   // MLX connection pointer
	void *win;			   // Window pointer
	char **map;			   // 2D array storing the map layout
	int map_width;		   // Width of the map in tiles
	int map_height;		   // Height of the map in tiles
	void *wall_img;		   // Wall texture image
	void *floor_img;	   // Floor texture image
	void *player_img;	   // Player texture image
	void *collectible_img; // Collectible texture image
	void *enemy_img;	   // Enemy texture image
	void *exit_img;		   // Exit texture image
	int img_width;		   // Width of loaded textures
	int img_height;		   // Height of loaded textures
	t_keys keys;		   // WASD movement key states
	int player_x;		   // Player's X position on map
	int player_y;		   // Player's Y position on map
	int player_moves;	   // Number of player moves
	int player_timer;	   // Timer for player movement updates
	int collectibles;	   // Total number of collectibles
	int collected;		   // Number of collected items
	t_enemy *enemy_patrol; // Array of structs with enemy data
	int enemy_count;	   // Total number of enemies
	int enemy_timer;	   // Timer for enemy movement updates
	int exit_x;			   // Exit's X position on map
	int exit_y;			   // Exit's Y position on map
} t_game;

// Game Lifecycle Functions (main.c & map_loading.c)
int load_map(t_game *game, char *filename);
void free_map(char **map);
int close_game(t_game *game);

// Map Validation Functions (map_elements.c & map_pathfinding.c)
int check_walls(t_game *game);
int check_invalid_chars(t_game *game);
int check_player(t_game *game);
int check_collectibles(t_game *game);
int check_enemies(t_game *game);
int check_exit(t_game *game);
int check_path(t_game *game);

// Map Validation Functions (map_validations.c)
int check_file_extension(char *filename);
int check_rectangular(t_game *game);
int check_map_size(t_game *game);
int validate_map(t_game *game, char *filename);

// Game Interaction Functions (game_interactions.c)
void handle_collectible(t_game *game, int new_x, int new_y);
void handle_exit(t_game *game);
void handle_enemy(t_game *game);
void handle_tiles(t_game *game, int new_x, int new_y);

// Game Input Functions (game_inputs.c)
int handle_keypress(int keycode, t_game *game);
int handle_keyrelease(int keycode, t_game *game);
void handle_dual_keys(t_game *game, int *alternate);

// Player Movement Functions (player_movements.c)
void handle_movement(t_game *game, int *alternate);
void handle_player(t_game *game, int new_x, int new_y);
int game_loop(t_game *game);

// Enemy Functions (enemy_movements.c)
void init_enemy(t_enemy *enemy, int x, int y, char type);
void init_enemy_patrol(t_game *game);
void move_enemy(t_game *game, t_enemy *enemy);
void update_enemy(t_game *game);

// Rendering Functions (map_rendering.c)
int render_images(t_game *game);
void render_tiles(t_game *game, int x, int y);
void display_move_counter(t_game *game);
void render_map(t_game *game);

#endif