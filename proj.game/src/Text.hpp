#include <string>

namespace GoumzAndStuff {

class Game;

namespace Rendering {

class Font;

class Text {
 private:
  unsigned int _framebuffer{0};
  unsigned int _pre_drawn{0};

  unsigned int _x{0};
  unsigned int _y{0};
  unsigned int _width{0};
  unsigned int _height{0};
  float _angle{0};
  float _projection[4][4];
  float _rotation[2][2];
  float _color[4]{1.0f, 0.0f, 1.0f, 1.0f};

  unsigned int _scale_uniform{0};
  unsigned int _pos_uniform{0};
  unsigned int _projection_uniform{0};
  unsigned int _color_uniform{0};
  unsigned int _div_pos_uniform{0};
  unsigned int _div_scale_uniform{0};
  unsigned int _div_projection_uniform{0};
  unsigned int _div_rotation_uniform{0};

  Game* _game{nullptr};

  Font* _font{nullptr};
  bool _dirty{true};

  std::wstring _text;

 public:
  Text(Game* _used_game, Font* _used_font, const std::wstring& _text);
  ~Text();

  void draw();

  /**
   * Pre-draw letters to a texture to decrease resource bindings.
   */
  void pre_draw();

  bool dirty();

  void set_rotation(float angle);
  void set_position(unsigned int x, unsigned int y);
  void set_color(float r, float g, float b, float a);
  void set_text(const std::wstring& text);
};

}  // namespace Rendering
}  // namespace GoumzAndStuff
