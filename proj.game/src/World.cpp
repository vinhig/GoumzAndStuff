#include "World.hpp"

#include <GLES3/gl3.h>

#include <cstring>

#include "Game.hpp"
#include "Math.hpp"
#include "OpenGLUtils.hpp"

namespace GoumzAndStuff {
namespace Rendering {

World::World(Game* _used_game) {
  _game = _used_game;

  float half_width = static_cast<float>(_game->screen_width()) / 2.0f;
  float half_height = static_cast<float>(_game->screen_height()) / 2.0f;

  Math::ortho_proj(-half_height, half_height, -half_width, half_width, 0.0f,
                   1.0f, _projection);

  float eye[3] = {1.0f, 1.0f, 1.0f};
  float target[3] = {0.0f, 0.0f, 0.0f};
  float up[3] = {0.0f, 1.0f, 0.0f};
  Math::look_at(eye, target, up, _view);

  {
    auto vertex_shader_source =
        (char*)(_used_game->read_file("shaders/tile_shader.vert.glsl").data);
    auto fragment_shader_source =
        (char*)(_used_game->read_file("shaders/tile_shader.frag.glsl").data);

    auto vertex_shader = compile_shader(vertex_shader_source, GL_VERTEX_SHADER);
    auto fragment_shader =
        compile_shader(fragment_shader_source, GL_FRAGMENT_SHADER);

    _tile_shader = glCreateProgram();
    glAttachShader(_tile_shader, vertex_shader);
    glAttachShader(_tile_shader, fragment_shader);
    glLinkProgram(_tile_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    delete vertex_shader_source;
    delete fragment_shader_source;
  }

  _pos_uniform = glGetUniformLocation(_tile_shader, "pos");
  _projection_uniform = glGetUniformLocation(_tile_shader, "projection");
  _view_uniform = glGetUniformLocation(_tile_shader, "view");

  glGenFramebuffers(1, &_framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

  glGenTextures(1, &_pre_drawn);
  glBindTexture(GL_TEXTURE_2D, _pre_drawn);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _used_game->screen_width(),
               _used_game->screen_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         _pre_drawn, 0);

  GLenum attachments[1] = {GL_COLOR_ATTACHMENT0};

  glDrawBuffers(1, attachments);

  memset(_tiles, DIRT, 16 * 16);

  // load shitton of textures
  File current_texture = _used_game->read_file("textures/world/grass.png");
  _tile_textures[0] = load_image(current_texture.data, current_texture.size);
  delete current_texture.data;

  current_texture = _used_game->read_file("textures/world/dirt.png");
  _tile_textures[1] = load_image(current_texture.data, current_texture.size);
  delete current_texture.data;

  current_texture = _used_game->read_file("textures/world/path_2way_left.png");
  _tile_textures[2] = load_image(current_texture.data, current_texture.size);
  delete current_texture.data;

  current_texture = _used_game->read_file("textures/world/path_2way_up.png");
  _tile_textures[3] = load_image(current_texture.data, current_texture.size);
  delete current_texture.data;

  current_texture = _used_game->read_file("textures/world/path_3way_left.png");
  _tile_textures[4] = load_image(current_texture.data, current_texture.size);
  delete current_texture.data;

  current_texture = _used_game->read_file("textures/world/path_3way_right.png");
  _tile_textures[5] = load_image(current_texture.data, current_texture.size);
  delete current_texture.data;

  current_texture = _used_game->read_file("textures/world/path_3way_up.png");
  _tile_textures[6] = load_image(current_texture.data, current_texture.size);
  delete current_texture.data;

  current_texture = _used_game->read_file("textures/world/path_3way_down.png");
  _tile_textures[7] = load_image(current_texture.data, current_texture.size);
  delete current_texture.data;

  current_texture = _used_game->read_file("textures/world/path_4way.png");
  _tile_textures[8] = load_image(current_texture.data, current_texture.size);
  delete current_texture.data;

  // clang-format off
  float vertices[] = {
    -64.0f, 64.0f, 0.0f, 0.0f,
    64.0f, 64.0f, 1.0f, 0.0f,
    -64.0f, -64.0f, 0.0f, 1.0f,
    64.0f, 64.0f, 1.0f, 0.0f,
    64.0f, -64.0f, 1.0f, 1.0f,
    -64.0f, -64.0f, 0.0f, 1.0f,
  };
  // clang-format on

  glGenBuffers(1, &_quad);
  glBindBuffer(GL_ARRAY_BUFFER, _quad);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);

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
}

World::~World() {}

void World::pre_draw() {
  glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(_tile_shader);
  glBindVertexArray(_vao);

  glUniformMatrix4fv(_projection_uniform, 1, false, &_projection[0][0]);
  glUniformMatrix4fv(_view_uniform, 1, false, &_view[0][0]);

  float pos[2] = {-8.0f * 128.0f, -8.0f * 128.0f};

  for (unsigned int x = 0; x < 16; x++) {
    for (unsigned int y = 0; y < 16; y++) {
      glBindTexture(GL_TEXTURE_2D, _tile_textures[_tiles[x][y]]);

      glUniform2fv(_pos_uniform, 1, &pos[0]);

      glDrawArrays(GL_TRIANGLES, 0, 6);

      pos[1] += 128.0f;
    }

    pos[1] = -8.0f * 128.0f;
    pos[0] += 128.0f;
  }
}

void World::draw() {}

void World::set_tile(unsigned int x, unsigned y, TileType new_type) {
  _tiles[x][y] = new_type;
}

}  // namespace Rendering
}  // namespace GoumzAndStuff