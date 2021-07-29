#include <string>

namespace GoumzAndStuff {

class Input;

namespace Rendering {
class Font;
class Text;
class World;
}  // namespace Rendering

struct File {
  size_t size;
  unsigned char* data;
};

class Game {
 private:
  // Resources

  // Default font
  Rendering::Font* _default_font{nullptr};

  Rendering::Text* _frame_time_label{nullptr};

  Rendering::Text* _dummy_text1{nullptr};
  Rendering::Text* _dummy_text2{nullptr};
  Rendering::Text* _dummy_text3{nullptr};
  Rendering::Text* _dummy_text4{nullptr};
  Rendering::Text* _dummy_text5{nullptr};
  Rendering::Text* _dummy_text6{nullptr};

  Rendering::World* _world{nullptr};

  unsigned int _screen_width{0};
  unsigned int _screen_height{0};

  float _frame{0.0f};

  unsigned long _last_time{0};
  float _frame_time{0.0f};

  Input* _input_manager{nullptr};

 public:
  Game(/* args */);
  ~Game();

  File read_file(const std::string& path);

  void create();
  void reload();
  void draw_frame();
  void exit();

  float frame_time();

  unsigned int screen_width();
  unsigned int screen_height();

  Input* input_manager();
};

}  // namespace GoumzAndStuff