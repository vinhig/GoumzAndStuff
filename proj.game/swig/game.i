%module GoumzAndStuff
%nspace GoumzAndStuff;
%nspace GoumzAndStuff::Rendering;

%{

#include "Log.hpp"

namespace GoumzAndStuff {
enum TouchState : char {
  TOUCH_PRESSED = 0,
  TOUCH_JUST_PRESSED = 1,
  TOUCH_JUST_RELEASED = 2,
};

enum ZoomState : char {
  ZOOM_START,
  ZOOM_MIDDLE,
  ZOOM_STOP,
};

enum DragState : char {
  DRAG_START,
  DRAG_MIDDLE,
  DRAG_STOP,
};

namespace Rendering {
enum TileType : char {
  TILE_GRASS = 0,
  TILE_DIRT = 1,
  TILE_PATH_2WAY_LEFT = 2,
  TILE_PATH_2WAY_UP = 3,
  TILE_PATH_3WAY_LEFT = 4,
  TILE_PATH_3WAY_RIGHT = 5,
  TILE_PATH_3WAY_UP = 6,
  TILE_PATH_3WAY_DOWN = 7,
  TILE_PATH_4WAY = 8,
};

class World {
 public:
  void set_tile(unsigned int x, unsigned int y, TileType tile_type);
  void set_zoom(float new_zoom);
  void set_position(float x, float y);
};

}  // namespace Rendering

class Game {
 public:
  Rendering::World* get_world();
};

}  // namespace GoumzAndStuff

GoumzAndStuff::Game* get_game();

void print_error(const char* message) {
  GoumzAndStuff::Log::error(std::string(message));
}
void print(const char* message) {
  GoumzAndStuff::Log::debug(std::string(message));
}

%}

namespace GoumzAndStuff {
enum TouchState : char {
  TOUCH_PRESSED = 0,
  TOUCH_JUST_PRESSED = 1,
  TOUCH_JUST_RELEASED = 2,
};

enum ZoomState : char {
  ZOOM_START,
  ZOOM_MIDDLE,
  ZOOM_STOP,
};

enum DragState : char {
  DRAG_START,
  DRAG_MIDDLE,
  DRAG_STOP,
};

namespace Rendering {
enum TileType : char {
  TILE_GRASS = 0,
  TILE_DIRT = 1,
  TILE_PATH_2WAY_LEFT = 2,
  TILE_PATH_2WAY_UP = 3,
  TILE_PATH_3WAY_LEFT = 4,
  TILE_PATH_3WAY_RIGHT = 5,
  TILE_PATH_3WAY_UP = 6,
  TILE_PATH_3WAY_DOWN = 7,
  TILE_PATH_4WAY = 8,
};

class World {
 public:
  void set_tile(unsigned int x, unsigned int y, TileType tile_type);
  void set_zoom(float new_zoom);
  void set_position(float x, float y);
};

}  // namespace Rendering

class Game {
 public:
  Rendering::World* get_world();
};

}  // namespace GoumzAndStuff

GoumzAndStuff::Game* get_game();

void print_error(const char* message);
void print(const char* message);