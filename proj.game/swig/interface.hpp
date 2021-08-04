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