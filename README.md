*This project has been created as part of the 42 curriculum by migusant.*

# So Long

A **2D tile-based game** built with MiniLibX where the player navigates a map, collects items, avoids enemies, and reaches the exit. This project demonstrates window management, event handling, sprite animation, and basic game engine architecture in C.

## Description

The So Long project is a top-down 2D game rendered using the **MiniLibX** graphical library on X11. The player moves through a tile-based map loaded from `.ber` files, collecting all collectibles before the exit unlocks. The game features a full animation system with 8-frame sprite cycles for the player, enemies, and collectibles, three enemy types with distinct movement behaviors, diagonal movement support through alternating key handling, and an on-screen HUD displaying the move counter.

### Key Features

- **Tile-based rendering** with 32x32 pixel XPM sprites for all game elements
- **8-frame sprite animations** for player (8 animation sets: 4 walk + 4 idle), enemies (5 animation sets), and collectibles
- **Three player states** with smooth transitions: static, moving, and idle (idle animation triggers after inactivity delay)
- **Directional player sprites** tracking the last facing direction for static and idle poses
- **Three enemy types (bonus):** static (`S`), horizontal patrol (`H`), and vertical patrol (`V`) with direction reversal on collision
- **Diagonal movement (bonus)** by holding two keys simultaneously, alternating between axes each frame
- **Continuous movement** using key press/release state tracking (hold WASD to move)
- **On-screen move counter (bonus)** rendered with outlined text using MiniLibX's `mlx_string_put()`
- **Flood-fill pathfinding** to validate that all collectibles and the exit are reachable from the player's starting position
- **Comprehensive map validation** checking file extension, rectangular shape, wall enclosure, valid characters, element counts, map size limits, and valid paths
- **Multi-resolution support** with configurable window dimensions for FHD (1920x1080) and QHD (2560x1440)
- **Custom XPM compositor tool** for compositing foreground sprites onto background tiles with transparency support
- **Dynamic exit unlocking** with sprite swap when all collectibles are gathered
- **Uses libft** as the authorized utility library including ft_printf and get_next_line

### Project Structure

```
├── includes/
│   └── so_long.h                  # Main header with all structures, macros, and prototypes
├── sources/
│   ├── main.c                     # Entry point, window initialization, cleanup, and event hooks
│   ├── map_loading.c              # Map file reading with get_next_line
│   ├── map_validation_core.c      # File extension, rectangular, size, and character validation
│   ├── map_validation_elements.c  # Walls, player, collectibles, enemies, and exit validation
│   ├── map_pathfinding.c          # Flood-fill algorithm for path reachability
│   ├── sprites_manager.c          # Static tile sprite loading and image cleanup
│   ├── sprites_player.c           # Player animation sprite loading (walk, idle, exit variants)
│   ├── sprites_collectible.c      # Collectible animation sprite loading
│   ├── sprites_enemy.c            # Enemy animation sprite loading (walk + static directions)
│   ├── render_map.c               # Full map rendering and per-tile render dispatch
│   ├── render_entities.c          # Player, enemy, and collectible frame rendering
│   ├── render_ui.c                # On-screen move counter with outlined text
│   ├── update_animations.c        # Timer-based animation frame cycling for all entities
│   ├── player_system.c            # Key press/release handlers and animation state management
│   ├── player_actions.c           # Movement logic, position validation, and move counting
│   ├── player_diagonal.c          # Dual-key diagonal movement with alternating axes
│   ├── enemy_system.c             # Enemy initialization, state machine, and animation mapping
│   ├── enemy_actions.c            # Enemy patrol movement, collision detection, and direction reversal
│   ├── game_loop.c                # Main loop with timer-based movement and animation updates
│   └── game_interactions.c        # Collectible pickup, exit handling, and enemy collision (game over)
├── sprites/
│   ├── xpm_compositor.c           # XPM sprite compositing tool (merges foreground + background)
│   ├── xpm_compositor.h           # Compositor structures and prototypes
│   ├── player/                    # Player sprite source files
│   ├── enemies/                   # Enemy sprite source files
│   ├── collectibles/              # Collectible sprite source files
│   └── static/                    # Static tile source files
├── textures/                      # Compiled XPM textures used at runtime
│   ├── player/                    # Player walk/idle/exit XPM sprites
│   ├── enemies/                   # Enemy walk/static XPM sprites
│   ├── collectibles/              # Collectible animation XPM sprites
│   └── static/                    # Wall, floor, exit (locked/unlocked) XPM sprites
├── maps/
│   ├── FHD/                       # Maps sized for 1920x1080 resolution (valid + invalid test maps)
│   └── QHD/                       # Maps sized for 2560x1440 resolution
├── old_textures/                  # Archived previous texture versions
├── libft/                         # Custom C utility library (libft, ft_printf, get_next_line)
├── minilibx-linux.tgz             # MiniLibX source archive
└── Makefile
```

## Instructions

### Compilation

```bash
make        # Compile the project (builds libft, MiniLibX, then so_long)
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile from scratch
```

This produces the `so_long` executable.

### Execution

```bash
./so_long <map_file.ber>
```

**Arguments:**
- `map_file.ber`: Path to a map description file with the `.ber` extension

**Examples:**

```bash
# Play a valid map
./so_long maps/FHD/valid_0.ber

# Play a map with enemies
./so_long maps/FHD/valid_enemy_0.ber
```

### Controls

| Key | Action |
|-----|--------|
| `W` | Move up |
| `A` | Move left |
| `S` | Move down |
| `D` | Move right |
| `W+A`, `W+D`, `S+A`, `S+D` | Diagonal movement (alternating) |
| `ESC` | Quit the game |

Hold keys for continuous movement. The move counter updates on each step.

### Map Format

Maps are `.ber` text files using these characters:

| Character | Element |
|-----------|---------|
| `0` | Empty space |
| `1` | Wall |
| `P` | Player starting position (exactly 1) |
| `E` | Exit (exactly 1) |
| `C` | Collectible (at least 1) |
| `S` | Static enemy (bonus) |
| `H` | Horizontal patrol enemy (bonus) |
| `V` | Vertical patrol enemy (bonus) |

**Example map:**
```
1111111111
1P00000C01
100S110001
10C0110C01
1000000001
1000H000E1
1111111111
```

**Map rules:**
- Must be rectangular and enclosed by walls (`1`)
- Must contain exactly 1 player (`P`) and 1 exit (`E`), and at least 1 collectible (`C`)
- All collectibles and the exit must be reachable from the player position
- Maximum size: 60x33 tiles (FHD) or 80x45 tiles (QHD)
- Minimum size: 5x3 or 3x5

## Technical Implementation

### Game Architecture

**Central structure:** A single `t_game` struct holds all game state: MLX pointers, the map grid, player state, enemy manager, collectible tracker, and all sprite images.

**Game loop (`mlx_loop_hook`):** Called repeatedly by MiniLibX, it:
1. Increments the player move timer
2. Updates enemy movement and state transitions
3. Cycles animation frames for collectibles, enemies, and the player
4. Processes player input when the move timer reaches the threshold (`PLAYER_TIMER = 3000`)

### Animation System

**Timer-based frame cycling:** Each entity type has an independent timer and 8-frame animation cycle:
- **Player:** 8 animation sets (idle down/up/left/right + walk down/up/left/right), each with 8 frames. Transitions: moving -> static (on key release) -> idle (after `PLAYER_IDLE_DELAY = 60000` ticks)
- **Enemies:** 5 animation sets (idle down + walk in 4 directions) with static direction frames for paused state
- **Collectibles:** Single 8-frame looping animation

**Exit-specific player sprites:** Separate sprite arrays (`exit_sprites`, `exit_static_sprites`) render the player differently when standing on the exit tile.

### Enemy AI (Bonus)

Three enemy types with a shared state machine:
- **Static (`S`):** Remains in place, cycles through directional static frames
- **Horizontal (`H`):** Patrols left/right, reverses direction on wall or obstacle collision, pauses briefly in static state before resuming (`ENEMY_STATIC_DELAY = 12000`)
- **Vertical (`V`):** Patrols up/down with the same reversal and pause behavior

Enemies cannot pass through walls, collectibles, the exit, or other enemies. Collision with the player triggers immediate game over.

### Input System

**Key state tracking:** Uses `t_keys` struct with press/release flags for WASD, enabling:
- **Continuous movement:** Holding a key moves the player at the timer rate
- **Diagonal movement:** When two non-opposing keys are held, movement alternates between axes each frame using a modulo counter
- **Opposing key cancellation:** Pressing W+S or A+D simultaneously results in no movement

### Map Validation Pipeline

The `validate_map()` function runs a chain of 10 validation checks in order:
1. File extension (`.ber`)
2. Rectangular shape (all rows equal length)
3. Size limits (min 3x5 / max 60x33 for FHD)
4. Invalid characters
5. Wall enclosure (first/last row and column all `1`)
6. Exactly 1 player
7. At least 1 collectible
8. Valid enemy types only
9. **Flood-fill path validation** (all collectibles and exit reachable from player)
10. Exactly 1 exit

### XPM Compositor Tool

A standalone utility (`sprites/xpm_compositor.c`) for building final textures:
- Parses XPM files, resolves color character conflicts between layers
- Composites foreground sprites onto background tiles respecting transparency
- Generates the runtime-ready XPM files in the `textures/` directory

## Resources

### MiniLibX

- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Unofficial documentation
- `mlx_init`, `mlx_new_window`, `mlx_loop`, `mlx_hook`, `mlx_loop_hook` - Core MiniLibX functions
- `mlx_xpm_file_to_image` - Loading XPM sprite files
- `mlx_put_image_to_window` - Rendering images at tile positions
- `mlx_string_put` - On-screen text rendering
- `mlx_destroy_image`, `mlx_destroy_window`, `mlx_destroy_display` - Resource cleanup

### X11 Events

- `<X11/X.h>` - X11 event types (`KeyPress`, `KeyRelease`, `DestroyNotify`)
- `<X11/keysym.h>` - Key symbol constants (`XK_w`, `XK_a`, `XK_s`, `XK_d`, `XK_Escape`)

### Game Development Concepts

- [Tile-based Game Tutorial](https://www.redblobgames.com/grids/rectangles/) - Grid-based game design
- [Wikipedia: Flood Fill](https://en.wikipedia.org/wiki/Flood_fill) - Recursive flood fill algorithm
- [Game Programming Patterns](https://gameprogrammingpatterns.com/game-loop.html) - Game loop architecture

### Debugging Tools

- `man valgrind(1)` - Valgrind command-line options
- [Valgrind Manual](https://valgrind.org/docs/manual/manual.html) - Memory error detection

### AI Usage

AI tools (GitHub Copilot, ChatGPT) were used as a **thinking partner and debugging assistant** to discuss problems and approaches, but all final code, architecture decisions, and bug fixes were produced by the student after understanding the underlying concepts.

**Documentation & Understanding:**
- Explaining MiniLibX event hook system and X11 event masks
- Clarifying XPM file format structure for sprite creation and compositing
- Understanding timer-based animation systems and frame cycling in game loops
- Discussing tile-based rendering patterns and entity state machines
- Refining and structuring README.md documentation to accurately represent technical implementations

**Code Review:**
- Identifying potential memory leaks in sprite loading error paths
- Reviewing proper MiniLibX resource cleanup order (images before window before display)
- Verifying flood-fill correctness with enemy tiles as obstacles

**Learning Resources:**
- Providing reference for X11 event types and key symbol mappings
- Clarifying MiniLibX `mlx_hook` vs `mlx_loop_hook` behavior
- Explaining sprite compositing with transparency handling

**Testing Assistance & Debugging:**
- Helping design invalid map test cases for validation edge scenarios
- Debugging animation timer tuning for smooth sprite transitions
- Identifying rendering order issues with overlapping entities

## License

This project is part of the 42 Common Core curriculum. See [LICENSE](LICENSE) for details.
