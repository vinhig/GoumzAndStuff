namespace GoumzAndStuff {
namespace Rendering {
enum TileType : char {
  GRASS = 0,
  DIRT = 1,
  PATH_2WAY_LEFT = 2,
  PATH_2WAY_UP = 3,
  PATH_3WAY_LEFT = 4,
  PATH_3WAY_RIGHT = 5,
  PATH_3WAY_UP = 6,
  PATH_3WAY_DOWN = 7,
  PATH_4WAY = 8,
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