/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:19:09 by migusant          #+#    #+#             */
/*   Updated: 2025/11/07 12:28:17 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <X11/X.h>
# include <X11/keysym.h>
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

// Player Animation
# define ANIM_IDLE_DOWN 0
# define ANIM_IDLE_UP 1
# define ANIM_IDLE_LEFT 2
# define ANIM_IDLE_RIGHT 3
# define ANIM_WALK_DOWN 4
# define ANIM_WALK_UP 5
# define ANIM_WALK_LEFT 6
# define ANIM_WALK_RIGHT 7

// Enemies Animation
# define ENEMY_ANIM_IDLE_DOWN 0
# define ENEMY_ANIM_WALK_DOWN 1
# define ENEMY_ANIM_WALK_UP 2
# define ENEMY_ANIM_WALK_LEFT 3
# define ENEMY_ANIM_WALK_RIGHT 4

// Player States
# define PLAYER_STATE_STATIC 0
# define PLAYER_STATE_MOVING 1
# define PLAYER_STATE_IDLE 2

// Enemy States
# define ENEMY_STATE_STATIC 0
# define ENEMY_STATE_MOVING 1

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
	int		curr_frame;
	int		anim_timer;
	void	*sprites[ANIMATION_FRAMES];
}		t_collectible;

typedef struct s_player
{
	int		x;
	int		y;
	int		moves;
	int		state;
	int		curr_anim;
	int		curr_frame;
	int		last_direction;
	int		move_timer;
	int		anim_timer;
	int		idle_timer;
	void	*sprites[PLAYER_ANIMATIONS][ANIMATION_FRAMES];
	void	*static_sprites[DIRECTION_COUNT];
	void	*exit_sprites[PLAYER_ANIMATIONS][ANIMATION_FRAMES];
	void	*exit_static_sprites[DIRECTION_COUNT];
}		t_player;

typedef struct s_enemy
{
	int		x;
	int		y;
	char	type;
	int		state;
	int		direction;
	int		curr_anim;
	int		curr_frame;
	int		static_frame;
	int		static_timer;
}		t_enemy;

typedef struct s_enemy_manager
{
	t_enemy	*enemy;
	int		count;
	int		move_timer;
	int		anim_timer;
	void	*sprites[ENEMY_ANIMATIONS][ANIMATION_FRAMES];
	void	*static_sprites[DIRECTION_COUNT];
}		t_enemy_manager;

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
	t_enemy_manager	enemies;
	int				exit_x;
	int				exit_y;
}		t_game;

// Map Loading (map_loading.c) (4 / 4)
int		load_map(t_game *game, char *filename);

// Map Validation Core (map_validation_core.c) (5 / 5)
int		validate_map(t_game *game, char *filename);

// Map Validation Elements (map_validation_elements.c) (5 / 5)
int		check_walls(t_game *game);
int		check_player(t_game *game);
int		check_collectibles(t_game *game);
int		check_enemies(t_game *game);
int		check_exit(t_game *game);

// Map Pathfinding (map_pathfinding.c) (4 / 4)
int		check_path(t_game *game);

// Game Lifecycle (main.c) (1 / 3)
int		init_window(t_game *game);

// Sprite Loading (sprites_manager.c) (3 / 5)
int		load_sprites(t_game *game);

// Player Sprites (sprites_player.c) (5 / 5)
int		load_player_sprites(t_game *game);

// Collectible Sprites (sprites_collectible.c) (1 / 1)
int		load_collectible_sprites(t_game *game);

// Enemy Sprites (sprites_enemy.c) (3 / 3)
int		load_enemy_sprites(t_game *game);

// Enemy System (enemy_system.c) (2 / 5)
int		init_enemies(t_game *game);

// Game Loop (game_loop.c) (1 / 1)
int		game_loop(t_game *game);

// Enemy Actions (enemy_actions.c) (5 / 5)
void	update_enemy(t_game *game);

// Enemy System (enemy_system.c) (5 / 5)
void	update_enemy_states(t_game *game);
void	set_enemy_animation(t_enemy *enemy);
void	set_enemy_static_frame(t_enemy *enemy);

// Player System (player_system.c) (2 / 4)
int		handle_keypress(int keysym, t_game *game);
int		handle_keyrelease(int keysym, t_game *game);

// Input Handling (player_diagonal.c) (5 / 5)
void	handle_dual_keys(t_game *game, int *alternate);

// Player Actions (player_actions.c) (5 / 5)
void	handle_movement(t_game *game, int *alternate);
void	move_player(t_game *game, int new_x, int new_y);

// Player System (player_system.c) (4 / 4)
void	set_player_static(t_game *game);
void	set_player_animation(t_game *game, int direction);

// Game Interactions (game_interactions.c) (5 / 5)
void	handle_tiles(t_game *game, int new_x, int new_y);
void	handle_enemy_collision(t_game *game);

// Animation Updates (update_animations.c) (5 / 5)
void	update_collectible_sprites(t_game *game);
void	update_enemy_sprites(t_game *game);
void	update_player_sprites(t_game *game);

// Map Rendering (render_map.c) (3 / 3)
void	render_map(t_game *game);
void	render_tiles(t_game *game, int x, int y);

// Entity Rendering (render_entities.c) (5 / 5)
void	render_enemy_frame(t_game *game, t_enemy *enemy, int x, int y);
void	render_collectible_frame(t_game *game, int x, int y);
void	render_player_frame(t_game *game, int x, int y);

// UI Rendering (render_ui.c) (2 / 2)
void	display_move_counter(t_game *game);

// Game Lifecycle (main.c) (2 / 3)
int		close_game(t_game *game);

// Sprite Loading (sprites_manager.c) (5 / 5)
void	destroy_images(t_game *game);

// Map Loading (main.c) (3 / 3)
void	free_map(char **map);

#endif