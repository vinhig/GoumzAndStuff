
#include <glm/mat4x4.hpp>

namespace GoumzAndStuff {

class Game;
class InputHandler;

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
 private:
  TileType _tiles[16][16];

  float _half_width;
  float _half_height;

  unsigned int _tile_textures[9];

  unsigned int _framebuffer;
  unsigned int _pre_drawn;
  unsigned int _vao;
  unsigned int _quad;

  // glm::mat4 _projection;
  float _projection[4][4];
  // float _isometric_view[2][2];

  unsigned int _projection_uniform;
  unsigned int _view_uniform;
  unsigned int _pos_uniform;

  unsigned int _tile_shader;

  Game* _game;
  InputHandler* _move_camera_handler;

  float _last_zoom{1.0f};

 public:
  World(Game* _used_game);
  ~World();

  void pre_draw();
  void draw();

  void set_tile(unsigned int x, unsigned int y, TileType new_type);
};

}  // namespace Rendering

}  // namespace GoumzAndStuff