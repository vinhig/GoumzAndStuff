#include <string>
#include <unordered_map>

typedef struct FT_FaceRec_ *FT_Face;
typedef struct FT_LibraryRec_ *FT_Library;

namespace GoumzAndStuff {
class Game;

namespace Rendering {
struct Character {
  unsigned int texture{0};
  unsigned int width{0};
  unsigned int height{0};
  int bearing_x{0};
  int bearing_y{0};
  int advance{0};
};

class Font {
 private:
  std::unordered_map<wchar_t, Character> _characters;

  unsigned int _text_shader{0};
  unsigned int _div_shader{0};
  unsigned int _dummy_vao{0};
  unsigned int _quad{0};

  FT_Library _font_library{nullptr};
  FT_Face _font_face{nullptr};

 public:
  Font(GoumzAndStuff::Game* _game, const std::string& font_path);
  ~Font();

  const std::unordered_map<wchar_t, Character>& characters();

  const Character& character(wchar_t c);

  unsigned int text_shader() const;
  unsigned int div_shader() const;
  unsigned int quad() const;
};
}  // namespace Rendering
}  // namespace GoumzAndStuff