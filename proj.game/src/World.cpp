#include "World.hpp"

#include <GLES3/gl3.h>

#include <cstring>
#include <glm/gtx/transform.hpp>

#include "Game.hpp"
#include "Input.hpp"
#include "Log.hpp"
#include "Math.hpp"
#include "OpenGLUtils.hpp"

namespace GoumzAndStuff {
namespace Rendering {

World::World(Game* _used_game) {
  _game = _used_game;

  _half_width = static_cast<float>(_game->screen_width()) / 2.0f;
  _half_height = static_cast<float>(_game->screen_height()) / 2.0f;

  /*_projection =
      glm::ortho(-half_width / 100.0f, half_width / 100.0f,
                 -half_height / 100.0f, half_height / 100.0f, -100.0f, 100.0f) *
      glm::lookAt(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, -1.0f, 0.0f));*/
  auto a = glm::ortho(-_half_width / 100.0f, _half_width / 100.0f,
                      -_half_height / 100.0f, _half_height / 100.0f, -100.0f,
                      100.0f);
  auto b =
      glm::lookAt(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, -1.0f, 0.0f));

  Math::matrix_multiply(&a[0][0], &b[0][0], &_projection[0][0]);

  int f = 2;
  {
    auto vertex_shader_source =
        _game->read_file("shaders/tile_shader.vert.glsl");
    auto fragment_shader_source =
        _game->read_file("shaders/tile_shader.frag.glsl");

    auto vertex_shader =
        compile_shader((const char*)vertex_shader_source.data,
                       vertex_shader_source.size, GL_VERTEX_SHADER);
    auto fragment_shader =
        compile_shader((const char*)fragment_shader_source.data,
                       fragment_shader_source.size, GL_FRAGMENT_SHADER);

    _tile_shader = glCreateProgram();
    glAttachShader(_tile_shader, vertex_shader);
    glAttachShader(_tile_shader, fragment_shader);
    glLinkProgram(_tile_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    delete vertex_shader_source.data;
    delete fragment_shader_source.data;
  }

  _zoom_uniform = glGetUniformLocation(_tile_shader, "zoom");
  _offset_uniform = glGetUniformLocation(_tile_shader, "offset");
  _pos_uniform = glGetUniformLocation(_tile_shader, "pos");
  _projection_uniform = glGetUniformLocation(_tile_shader, "projection");
  // _view_uniform = glGetUniformLocation(_tile_shader, "view");

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

  memset(_tiles, TILE_GRASS, 16 * 16);

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
  /*float vertices[] = {
    -64.0f, 64.0f, 0.0f, 0.0f,
    64.0f, 64.0f, 1.0f, 0.0f,
    -64.0f, -64.0f, 0.0f, 1.0f,
    64.0f, 64.0f, 1.0f, 0.0f,
    64.0f, -64.0f, 1.0f, 1.0f,
    -64.0f, -64.0f, 0.0f, 1.0f,
  };*/
  float vertices[] = {
    -1.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 1.0f,
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

  /*_move_camera_handler = new InputHandler();

  _move_camera_handler->handle_zoom();
  _move_camera_handler->set_zoom_callback([this](ZoomState state, float zoom) {
    if (state == ZOOM_STOP) {
      _last_zoom *= zoom;
    } else if (state == ZOOM_MIDDLE) {
      auto a = glm::ortho(-_half_width / 100.0f * _last_zoom * zoom,
                          _half_width / 100.0f * _last_zoom * zoom,
                          -_half_height / 100.0f * _last_zoom * zoom,
                          _half_height / 100.0f * _last_zoom * zoom, -100.0f,
                          100.0f);
      auto b =
          glm::lookAt(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                      glm::vec3(0.0f, -1.0f, 0.0f));

      Math::matrix_multiply(&a[0][0], &b[0][0], &_projection[0][0]);
    }
  });
  _move_camera_handler->handle_drag();
  _move_camera_handler->set_touch_callback(
      [this](TouchState state, float x, float y) {

      });
  // _used_game->input_manager()->register_handler(_move_camera_handler);
  */
}

World::~World() {
  // delete all tile textures
  glDeleteTextures(9, _tile_textures);
}

void World::pre_draw() {
  glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(_tile_shader);
  glBindVertexArray(_vao);

  // glUniform1f(_zoom_uniform, _last_zoom);
  glUniform2f(_offset_uniform, _last_x, _last_y);
  glUniformMatrix4fv(_projection_uniform, 1, false, &_projection[0][0]);

  float pos[2] = {-8.0f * 2.1f, -8.0f * 2.1f};

  for (auto x = 0; x < 16; x++) {
    for (auto y = 0; y < 16; y++) {
      glBindTexture(GL_TEXTURE_2D, _tile_textures[_tiles[x][y]]);

      glUniform2fv(_pos_uniform, 1, &pos[0]);

      glDrawArrays(GL_TRIANGLES, 0, 6);

      pos[1] += 2.1f;
    }

    pos[1] = -8.0f * 2.1f;
    pos[0] += 2.1f;
  }
}

void World::draw() {
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, _framebuffer);

  glBlitFramebuffer(0, 0, _game->screen_width(), _game->screen_height(), 0, 0,
                    _game->screen_width(), _game->screen_height(),
                    GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void World::set_tile(unsigned int x, unsigned y, TileType new_type) {
  _tiles[x][y] = new_type;
}

void World::set_zoom(float new_zoom) {
  _last_zoom = new_zoom;

  compute_projection();
}

void World::set_position(float x, float y) {
  _last_x = x;
  _last_y = y;
}

void World::compute_projection() {
  auto a = glm::ortho(-_half_width / 100.0f * _last_zoom,
                      _half_width / 100.0f * _last_zoom,
                      -_half_height / 100.0f * _last_zoom,
                      _half_height / 100.0f * _last_zoom, -100.0f, 100.0f);
  auto b =
      glm::lookAt(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, -1.0f, 0.0f));

  Math::matrix_multiply(&a[0][0], &b[0][0], &_projection[0][0]);
}

}  // namespace Rendering
}  // namespace GoumzAndStuff