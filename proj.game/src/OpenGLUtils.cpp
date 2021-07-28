#include "OpenGLUtils.hpp"

#include <GLES3/gl3.h>
#include <stb/stb_image.h>

#include <string>

#include "Log.hpp"

namespace GoumzAndStuff {
namespace Rendering {

unsigned int compile_shader(const char* source, GLenum shaderType) {
  // Compile shader
  unsigned int shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  // Check result
  int result = GL_FALSE;
  int info_length;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length);
  if (info_length > 0) {
    char* error_msg = new char[info_length + 1];
    glGetShaderInfoLog(shader, info_length, nullptr, &error_msg[0]);
    Log::debug(std::string(source));
    Log::error(std::string(error_msg));
    delete[] error_msg;
    return 0;
  }

  return shader;
}

unsigned int load_image(const unsigned char* content, unsigned int file_size) {
  int width, height, nr_channels;
  stbi_info_from_memory(content, file_size, &width, &height, &nr_channels);

  stbi_set_flip_vertically_on_load(true);

  unsigned char* data;
  if (nr_channels == 3) {
    data = stbi_load_from_memory(content, file_size, &width, &height,
                                 &nr_channels, 4);
    nr_channels = 4;
  } else {
    data = stbi_load_from_memory(content, file_size, &width, &height,
                                 &nr_channels, 4);
  }

  unsigned int texture;

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);

  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);

  return texture;
}

}  // namespace Rendering
}  // namespace GoumzAndStuff