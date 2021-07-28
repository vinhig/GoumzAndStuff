#ifdef __ANDROID__

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <jni.h>

#endif

#include <GLES3/gl32.h>

#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>

#include "Font.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "Text.hpp"
#include "World.hpp"

#ifdef __ANDROID__

static GoumzAndStuff::Game g_Game;
static AAssetManager *g_AssetManager;

extern "C" JNIEXPORT void JNICALL
Java_be_wholesome_goumzandstuff_MyGLRenderer_onSurfaceCreated(
    JNIEnv *env, jobject /* this */) {
  g_Game.create();
}

extern "C" JNIEXPORT void JNICALL
Java_be_wholesome_goumzandstuff_MyGLRenderer_onSurfaceChanged(
    JNIEnv *env, jobject /* this */) {
  g_Game.reload();
}

extern "C" JNIEXPORT void JNICALL
Java_be_wholesome_goumzandstuff_MyGLRenderer_onDrawFrame(JNIEnv *env,
                                                         jobject /* this */) {
  g_Game.draw_frame();
}

extern "C" JNIEXPORT void JNICALL
Java_be_wholesome_goumzandstuff_MainActivity_setAssetManager(
    JNIEnv *env, jobject thiz, jobject asset_manager) {
  g_AssetManager = AAssetManager_fromJava(env, asset_manager);
}
#endif

static void debug_output(GLenum source, GLenum type, GLuint id, GLenum severity,
                         GLsizei length, const GLchar *message,
                         const void *userParam) {
  GoumzAndStuff::Log::error(std::string(message));
}

namespace GoumzAndStuff {

File Game::read_file(const std::string &path) {
#if __ANDROID__
  // Open file
  AAsset *file =
      AAssetManager_open(g_AssetManager, path.c_str(), AASSET_MODE_BUFFER);
  if (!file) {
    Log::error("Unable to open file. '" + path + "'");
    return {0, nullptr};
  }
  // Read file
  size_t file_length = AAsset_getLength(file);
  auto file_content = new unsigned char[file_length];
  AAsset_read(file, file_content, file_length);

  return {file_length, file_content};

#endif
}

Game::Game(/* args */) {}

Game::~Game() {}

void Game::create() {
  // ex
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  _screen_width = viewport[2];
  _screen_height = viewport[3];

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(debug_output, NULL);

  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL,
                        GL_TRUE);
  // Dummy font loading
  _default_font = new Rendering::Font(this, "chubby.ttf");

  _dummy_text1 = new Rendering::Text(this, _default_font,
                                     L"Salut tout le monde, poudre aux yeux?!");

  _dummy_text1->set_position(400, 500);
  _dummy_text1->set_color(1.0f, 0.8f, 0.3f, 1.0f);

  _dummy_text2 =
      new Rendering::Text(this, _default_font, L"Zéphyr sous un ciel étoilé");
  _dummy_text2->set_position(800, 100);
  _dummy_text2->set_color(1.0f, 0.0f, 0.0f, 1.0f);

  _dummy_text3 =
      new Rendering::Text(this, _default_font, L"Je regarde Rome brûler");
  _dummy_text3->set_position(900, 50);
  _dummy_text3->set_color(1.0f, 0.0f, 1.0f, 1.0f);

  _dummy_text4 = new Rendering::Text(this, _default_font, L"Text::pre_draw();");
  _dummy_text4->set_position(20, 150);
  _dummy_text4->set_color(1.0f, 0.5f, 0.0f, 1.0f);

  _dummy_text5 = new Rendering::Text(this, _default_font, L"(1+2)/3*4");
  _dummy_text5->set_position(1200, 400);
  _dummy_text5->set_color(0.2f, 0.4f, 0.5f, 1.0f);

  _dummy_text6 = new Rendering::Text(
      this, _default_font, L"GoumzAndStuff, disponible sur le Play Store");
  _dummy_text6->set_position(1200, 100);
  _dummy_text6->set_color(0.0f, 0.3f, 0.7f, 1.0f);

  _world = new Rendering::World(this);
}

void Game::reload() {}

void Game::draw_frame() {
  if (_dummy_text1->dirty()) {
    _dummy_text1->pre_draw();
  }
  if (_dummy_text2->dirty()) {
    _dummy_text2->pre_draw();
  }
  if (_dummy_text3->dirty()) {
    _dummy_text3->pre_draw();
  }
  if (_dummy_text4->dirty()) {
    _dummy_text4->pre_draw();
  }
  if (_dummy_text5->dirty()) {
    _dummy_text5->pre_draw();
  }
  if (_dummy_text6->dirty()) {
    _dummy_text6->pre_draw();
  }

  _world->pre_draw();
  _world->draw();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  _dummy_text5->set_color(abs(sin(_frame)), abs(cos(_frame)),
                          1.0f - abs(sin(_frame)), 1.0f);

  _dummy_text1->set_rotation(_frame);
  _frame += 0.03;
  _dummy_text1->draw();

  _dummy_text2->set_rotation(_frame / 2.0f);
  _dummy_text2->draw();

  _dummy_text3->set_rotation(_frame / 2.0f * -1.0f);
  _dummy_text3->draw();

  _dummy_text4->set_rotation(_frame + 5.0f);
  _dummy_text4->draw();

  _dummy_text5->set_rotation(_frame * -1.0f);
  _dummy_text5->draw();

  _dummy_text6->set_rotation(_frame * 3.0f);
  _dummy_text6->draw();

  for (auto const &el : _default_font->characters()) {
    glBindTexture(GL_TEXTURE_2D, el.second.texture);
  }

  glFinish();
}

void Game::exit() {}

unsigned int Game::screen_width() { return _screen_width; }

unsigned int Game::screen_height() { return _screen_height; }

}  // namespace GoumzAndStuff