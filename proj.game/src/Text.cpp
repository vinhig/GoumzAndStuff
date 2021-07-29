#include "Text.hpp"

#include <GLES3/gl3.h>

#include <cmath>

#include "Font.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "Math.hpp"

namespace GoumzAndStuff {
namespace Rendering {

Text::Text(Game* _used_game, Font* _used_font, const std::wstring& _used_text) {
  _game = _used_game;
  _text = _used_text;
  _font = _used_font;

  Math::ortho_proj(0.0f, (float)_game->screen_height(), 0.0f,
                   (float)_game->screen_width(), 0.0f, 1.0f, _projection);

  _rotation[0][0] = 1.0f;
  _rotation[0][1] = 0.0f;
  _rotation[1][0] = 0.0f;
  _rotation[1][1] = 1.0f;

  _scale_uniform = glGetUniformLocation(_font->text_shader(), "scale");
  _pos_uniform = glGetUniformLocation(_font->text_shader(), "pos");
  _projection_uniform =
      glGetUniformLocation(_font->text_shader(), "projection");
  _color_uniform = glGetUniformLocation(_font->text_shader(), "color");

  _div_pos_uniform = glGetUniformLocation(_font->div_shader(), "pos");
  _div_scale_uniform = glGetUniformLocation(_font->div_shader(), "scale");
  _div_projection_uniform =
      glGetUniformLocation(_font->div_shader(), "projection");
  _div_rotation_uniform = glGetUniformLocation(_font->div_shader(), "rotation");
}

Text::~Text() {
  glDeleteFramebuffers(1, &_framebuffer);
  glDeleteTextures(1, &_pre_drawn);
}

void Text::draw() {
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  
  glBindVertexArray(_font->quad());
  glUseProgram(_font->div_shader());
  glBindTexture(GL_TEXTURE_2D, _pre_drawn);

  _rotation[0][0] = cos(_angle);
  _rotation[0][1] = -sin(_angle);
  _rotation[1][0] = sin(_angle);
  _rotation[1][1] = cos(_angle);

  // prepare uniform
  float pos[2] = {static_cast<float>(_x), static_cast<float>(_y)};
  float scale[2] = {static_cast<float>(_width), static_cast<float>(_height)};

  glUniform2fv(_div_pos_uniform, 1, &pos[0]);
  glUniform2fv(_div_scale_uniform, 1, &scale[0]);
  glUniformMatrix4fv(_div_projection_uniform, 1, false, &_projection[0][0]);
  glUniformMatrix2fv(_div_rotation_uniform, 1, false, &_rotation[0][0]);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Text::pre_draw() {
  auto total_width = 0;
  auto height = 0;

  for (const auto& c : _text) {
    auto caca = _font;
    auto character = _font->character(c);
    auto character_height = character.height + character.bearing_y;

    total_width += character.advance;

    if (character_height > height) {
      height = character_height;
    }
  }

  auto chacal = total_width;

  if (total_width > _width || height > _height) {
    _height = height;
    _width = total_width;
    // new text won't fit
    // delete previous resources
    if (_framebuffer != 0) {
      glDeleteFramebuffers(1, &_framebuffer);
    }
    if (_pre_drawn != 0) {
      glDeleteTextures(1, &_pre_drawn);
    }

    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

    glGenTextures(1, &_pre_drawn);
    glBindTexture(GL_TEXTURE_2D, _pre_drawn);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           _pre_drawn, 0);

    GLenum attachments[1] = {GL_COLOR_ATTACHMENT0};

    glDrawBuffers(1, attachments);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // draw text
  glUseProgram(_font->text_shader());

  glBindVertexArray(_font->quad());

  float total_advance = 0.0f;

  glUniformMatrix4fv(_projection_uniform, 1, false, &_projection[0][0]);

  glUniform4fv(_color_uniform, 1, &_color[0]);

  for (auto const& c : _text) {
    auto character = _font->character((unsigned char)c);

    // prepare uniforms
    float scale[2] = {(float)character.width, (float)character.height};
    float pos[2] = {
        (total_advance + (float)character.bearing_x),
        ((float)(character.height) - (float)character.bearing_y) * -1.0f +
            64.0f};

    total_advance += character.advance;

    glUniform2f(_scale_uniform, scale[0], scale[1]);
    glUniform2f(_pos_uniform, pos[0], pos[1]);

    glBindTexture(GL_TEXTURE_2D, character.texture);

    glDrawArrays(GL_TRIANGLES, 0, 6);
  }

  _dirty = false;
}

bool Text::dirty() { return _dirty; }

void Text::set_rotation(float angle) { _angle = angle; }

void Text::set_position(unsigned int x, unsigned int y) {
  _x = x;
  _y = y;
}

void Text::set_color(float r, float g, float b, float a) {
  _color[0] = r;
  _color[1] = g;
  _color[2] = b;
  _color[3] = a;

  _dirty = true;
}

void Text::set_text(const std::wstring& text) {
  _text = text;
  _dirty = true;
}

}  // namespace Rendering
}  // namespace GoumzAndStuff
