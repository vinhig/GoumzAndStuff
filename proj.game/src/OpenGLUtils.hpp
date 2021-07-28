typedef unsigned int GLenum;

namespace GoumzAndStuff {
namespace Rendering {

unsigned int compile_shader(const char* source, GLenum shaderType);

/**
 * Load image with stb_image and create corresponding texture.
 * @param data Content of file.
 */
unsigned int load_image(const unsigned char* data, unsigned int file_size);

}  // namespace Rendering
}  // namespace GoumzAndStuff