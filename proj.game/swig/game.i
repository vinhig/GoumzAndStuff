%module GoumzAndStuff
%nspace GoumzAndStuff;
%nspace GoumzAndStuff::Rendering;

%{

namespace GoumzAndStuff {
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
};

}  // namespace Rendering

class Game {
 public:
  Rendering::World* get_world();
};

}  // namespace GoumzAndStuff

GoumzAndStuff::Game* get_game();

%}

namespace GoumzAndStuff {
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
};

}  // namespace Rendering

class Game {
 public:
  Rendering::World* get_world();
};

}  // namespace GoumzAndStuff

GoumzAndStuff::Game* get_game();