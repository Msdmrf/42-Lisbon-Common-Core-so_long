/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:19:09 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:22:52 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"

// Window Settings
# define TILE_SIZE 32
# define WINDOW_TITLE "so_long"
// # define RESOLUTION_QHD

// Window Resolution
# ifdef RESOLUTION_QHD
#  define WINDOW_WIDTH 2560
#  define WINDOW_HEIGHT 1440
#  define MAX_MAP_WIDTH 80
#  define MAX_MAP_HEIGHT 45
# else 
#  define WINDOW_WIDTH 1920
#  define WINDOW_HEIGHT 1080
#  define MAX_MAP_WIDTH 60
#  define MAX_MAP_HEIGHT 33
# endif

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
# define ENEMY_STATIC 'S'
# define ENEMY_HORIZONTAL 'H'
# define ENEMY_VERTICAL 'V'
# define EXIT 'E'

// Animation Settings
# define PLAYER_TIMER 3000
# define ENEMY_TIMER 4500
# define COLLECTIBLE_TIMER 4500
# define ANIMATION_FRAMES 8
# define ENEMY_ANIMATIONS 5
# define ENEMY_STATIC_DELAY 12000
# define PLAYER_ANIMATIONS 8
# define PLAYER_IDLE_DELAY 60000

// Animation States
# define ANIM_IDLE_DOWN 0
# define ANIM_IDLE_UP 1
# define ANIM_IDLE_LEFT 2
# define ANIM_IDLE_RIGHT 3
# define ANIM_WALK_DOWN 4
# define ANIM_WALK_UP 5
# define ANIM_WALK_LEFT 6
# define ANIM_WALK_RIGHT 7

// Player States
# define PLAYER_STATE_IDLE 0
# define PLAYER_STATE_STATIC 1
# define PLAYER_STATE_MOVING 2

// Enemy States
# define ENEMY_STATE_MOVING 0
# define ENEMY_STATE_STATIC 1

// Static Direction Constants
# define DIRECTION_DOWN 0
# define DIRECTION_UP 1
# define DIRECTION_LEFT 2
# define DIRECTION_RIGHT 3
# define DIRECTION_COUNT 4

// Structures
typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
}		t_keys;

typedef struct s_collectible
{
	int		count;
	int		collected;
	void	*sprites[ANIMATION_FRAMES];
	int		frame;
	int		timer;
}		t_collectible;

typedef struct s_player
{
	int		x;
	int		y;
	int		moves;
	int		timer;
	int		anim_timer;
	int		idle_timer;
	int		current_anim;
	int		last_direction;
	int		frame;
	int		state;
	void	*sprites[PLAYER_ANIMATIONS][ANIMATION_FRAMES];
	void	*static_sprites[DIRECTION_COUNT];
	void	*exit_sprites[PLAYER_ANIMATIONS][ANIMATION_FRAMES];
	void	*exit_static_sprites[DIRECTION_COUNT];
}		t_player;

typedef struct s_enemy
{
	int		start_x;
	int		start_y;
	int		x;
	int		y;
	char	type;
	int		direction;
	int		current_anim;
	int		frame;
	int		state;
	int		static_frame;
	int		static_timer;
}		t_enemy;

typedef struct s_enemy_patrol
{
	t_enemy	*patrol;
	int		count;
	int		timer;
	int		anim_timer;
	void	*sprites[ENEMY_ANIMATIONS][ANIMATION_FRAMES];
	void	*static_sprites[DIRECTION_COUNT];
}		t_enemy_patrol;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	char			**map;
	int				map_width;
	int				map_height;
	void			*wall_img;
	void			*floor_img;
	void			*exit_img;
	int				img_width;
	int				img_height;
	t_keys			keys;
	t_player		player;
	t_collectible	collectible;
	t_enemy_patrol	enemy;
	int				exit_x;
	int				exit_y;
}		t_game;

// Game Lifecycle (main.c)
int		init_window(t_game *game);
void	free_map(char **map);
int		close_game(t_game *game);

// Map Loading (map_loading.c)
int		load_map(t_game *game, char *filename);
int		count_lines(char *filename);
char	**allocate_map(int lines);
int		read_map_lines(t_game *game, char *filename);

// Map Validation Core (map_validation_core.c)
int		validate_map(t_game *game, char *filename);
int		check_file_extension(char *filename);
int		check_rectangular(t_game *game);
int		check_map_size(t_game *game);
int		check_invalid_chars(t_game *game);

// Map Validation Elements (map_validation_elements.c)
int		check_walls(t_game *game);
int		check_player(t_game *game);
int		check_collectibles(t_game *game);
int		check_enemies(t_game *game);
int		check_exit(t_game *game);

// Map Pathfinding (map_pathfinding.c)
int		check_path(t_game *game);
char	**copy_map(t_game *game);
int		flood_fill(char **map, int x, int y, t_game *game);
int		is_reachable(t_game *game, char **map_copy);

// Sprite Loading (sprites_manager.c)
int		load_sprites(t_game *game);
int		load_basic_sprites(t_game *game);
int		load_animation_sprites(t_game *game);
void	destroy_images(t_game *game);
void	destroy_sprite_arrays(t_game *game);

// Collectible Sprites (sprites_collectible.c)
int		load_collectible_sprites(t_game *game);

// Player Sprites (sprites_player.c)
int		load_player_sprites(t_game *game);

// Enemy Sprites (sprites_enemy.c)
int		load_enemy_sprites(t_game *game);

// Map Rendering (render_map.c)
void	render_map(t_game *game);
void	render_tile(t_game *game, int x, int y, void *img);
void	render_tiles(t_game *game, int x, int y);

// Entity Rendering (render_entities.c)
void	render_collectible_frame(t_game *game, int x, int y);
void	render_player_frame(t_game *game, int x, int y);
void	render_enemy_frame(t_game *game, int x, int y, t_enemy *enemy);

// UI Rendering (render_ui.c)
void	display_move_counter(t_game *game);
void	render_move_text(t_game *game, char *moves_str);

// Animation Updates (update_animations.c)
void	update_collectible_sprites(t_game *game);
void	update_player_sprites(t_game *game);
void	update_enemy_sprites(t_game *game);

// Player System (player_system.c)
void	init_player_animation(t_game *game);
void	set_player_static(t_game *game);
void	set_player_animation(t_game *game, int direction);
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);

// Player Actions (player_actions.c)
void	move_player(t_game *game, int new_x, int new_y);
void	handle_movement(t_game *game, int *alternate);

// Input Handling (player_diagonal.c)
void	handle_dual_keys(t_game *game, int *alternate);

// Enemy System (enemy_system.c)
void	init_enemy(t_enemy *enemy, int x, int y, char type);
void	init_enemy_patrol(t_game *game);
void	update_enemy_states(t_game *game);
void	set_enemy_static_frame(t_enemy *enemy);
void	set_enemy_animation(t_enemy *enemy);

// Enemy Actions (enemy_actions.c)
void	update_enemy(t_game *game);
void	move_enemy(t_game *game, t_enemy *enemy);
void	calculate_new_position(t_enemy *enemy, int *new_x, int *new_y);
void	update_enemy_position(t_game *game, t_enemy *enemy,
			int new_x, int new_y);
int		is_valid_enemy_move(t_game *game, int x, int y, t_enemy *moving_enemy);

// Game Loop (game_loop.c)
int		game_loop(t_game *game);

// Game Interactions (game_interactions.c)
void	handle_collectible(t_game *game, int new_x, int new_y);
void	handle_enemy_collision(t_game *game);
void	handle_exit(t_game *game);
void	handle_tiles(t_game *game, int new_x, int new_y);
void	unlock_exit(t_game *game);

#endif