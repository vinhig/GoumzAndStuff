#include "Font.hpp"

#include <GLES3/gl3.h>
#include <ft2build.h>

#include "Game.hpp"
#include "Log.hpp"
#include "OpenGLUtils.hpp"
#include FT_FREETYPE_H

namespace GoumzAndStuff {
namespace Rendering {

Font::Font(GoumzAndStuff::Game* _game, const std::string& font_path) {
  if (FT_Init_FreeType(&_font_library)) {
    GoumzAndStuff::Log::error("Couldn't init freetype.");
  }

  GoumzAndStuff::File font_file = _game->read_file("chubby.ttf");

  if (FT_New_Memory_Face(_font_library,
                         static_cast<const FT_Byte*>(font_file.data),
                         font_file.size, 0, &_font_face)) {
    Log::error("Something went wrong when parsing font file.");
  }

  FT_Set_Pixel_Sizes(_font_face, 0, 128);

  glGetError();

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  std::wstring alphabet =
      L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzéè?!=+-/"
      L"0123456789;:.,_*ñûîôéèêâàá\"'() ïüëö";

  for (auto const& c : alphabet) {
    if (!FT_Load_Char(_font_face, c, FT_LOAD_RENDER)) {
      GLuint texture = 0;
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, _font_face->glyph->bitmap.width,
                   _font_face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                   _font_face->glyph->bitmap.buffer);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      if (glGetError() != GL_NO_ERROR) {
        Log::error("Someeeething wronnnnggg");
      }

      _characters.insert(
          {c,
           {texture, _font_face->glyph->bitmap.width,
            _font_face->glyph->bitmap.rows, _font_face->glyph->bitmap_left,
            _font_face->glyph->bitmap_top,
            static_cast<int>(_font_face->glyph->advance.x >> 6)}});
    }
  }

  FT_Done_Face(_font_face);
  FT_Done_FreeType(_font_library);

  glBindBuffer(GL_UNIFORM_BUFFER, -1);

  // clang-format off
  float vertices[] = {
    0.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
  };
  // clang-format on

  glGenBuffers(1, &_quad);
  glBindBuffer(GL_ARRAY_BUFFER, _quad);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenVertexArrays(1, &_dummy_vao);
  glBindVertexArray(_dummy_vao);

  // POSITION
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, _quad);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * 4, (const void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // TEXCOORD
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, _quad);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * 4, (const void*)(2 * 4));
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  {
    auto vertex_shader_source =
        _game->read_file("shaders/text_shader.vert.glsl");
    auto fragment_shader_source =
        _game->read_file("shaders/text_shader.frag.glsl");

    auto vertex_shader =
        compile_shader((const char*)vertex_shader_source.data,
                       vertex_shader_source.size, GL_VERTEX_SHADER);
    auto fragment_shader =
        compile_shader((const char*)fragment_shader_source.data,
                       fragment_shader_source.size, GL_FRAGMENT_SHADER);

    _text_shader = glCreateProgram();
    glAttachShader(_text_shader, vertex_shader);
    glAttachShader(_text_shader, fragment_shader);
    glLinkProgram(_text_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    delete vertex_shader_source.data;
    delete fragment_shader_source.data;
  }
  {
    auto vertex_shader_source =
        _game->read_file("shaders/div_shader.vert.glsl");
    auto fragment_shader_source =
        _game->read_file("shaders/div_shader.frag.glsl");

    auto vertex_shader =
        compile_shader((const char*)vertex_shader_source.data,
                       vertex_shader_source.size, GL_VERTEX_SHADER);
    auto fragment_shader =
        compile_shader((const char*)fragment_shader_source.data,
                       fragment_shader_source.size, GL_FRAGMENT_SHADER);

    _div_shader = glCreateProgram();
    glAttachShader(_div_shader, vertex_shader);
    glAttachShader(_div_shader, fragment_shader);
    glLinkProgram(_div_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    delete vertex_shader_source.data;
    delete fragment_shader_source.data;
  }
}

Font::~Font() {}

const std::unordered_map<wchar_t, Character>& Font::characters() {
  return _characters;
}

const Character& Font::character(wchar_t c) {
  auto found = _characters.find(c);

  if (found == _characters.end()) {
    // not yet computed ?
    return _characters.find('?')->second;
  }
  return found->second;
}

unsigned int Font::text_shader() const { return _text_shader; }

unsigned int Font::div_shader() const { return _div_shader; }

unsigned int Font::quad() const { return _dummy_vao; }
}  // namespace Rendering
}  // namespace GoumzAndStuff