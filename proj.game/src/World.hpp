namespace GoumzAndStuff {

class Game;

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
 private:
  TileType _tiles[16][16];

  unsigned int _tile_textures[9];

  unsigned int _framebuffer;
  unsigned int _pre_drawn;
  unsigned int _vao;
  unsigned int _quad;

  float _projection[4][4];
  float _view[4][4];

  unsigned int _projection_uniform;
  unsigned int _view_uniform;
  unsigned int _pos_uniform;

  unsigned int _tile_shader;

  Game* _game;

 public:
  World(Game* _used_game);
  ~World();

  void pre_draw();
  void draw();

  void set_tile(unsigned int x, unsigned int y, TileType new_type);
};

}  // namespace Rendering

}  // namespace GoumzAndStuff