#include <string>

namespace GoumzAndStuff {

namespace Rendering {
class Font;
class Text;
class World;
}

struct File {
  size_t size;
  unsigned char* data;
};

class Game {
 private:
  // Resources

  // Default font
  Rendering::Font* _default_font{nullptr};

  Rendering::Text* _dummy_text1{nullptr};
  Rendering::Text* _dummy_text2{nullptr};
  Rendering::Text* _dummy_text3{nullptr};
  Rendering::Text* _dummy_text4{nullptr};
  Rendering::Text* _dummy_text5{nullptr};
  Rendering::Text* _dummy_text6{nullptr};

  Rendering::World* _world;

  unsigned int _screen_width{0};
  unsigned int _screen_height{0};

  float _frame{0.0f};

 public:
  Game(/* args */);
  ~Game();

  File read_file(const std::string& path);

  void create();
  void reload();
  void draw_frame();
  void exit();

  unsigned int screen_width();
  unsigned int screen_height();
};

}  // namespace GoumzAndStuff