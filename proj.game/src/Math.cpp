#include <cstring>
#include <glm/gtx/transform.hpp>

namespace GoumzAndStuff {
namespace Math {

void ortho_proj(const float &b, const float &t, const float &l, const float &r,
                const float &n, const float &f, float matrix[4][4]) {
  matrix[0][0] = 2 / (r - l);
  matrix[0][1] = 0;
  matrix[0][2] = 0;
  matrix[0][3] = 0;

  matrix[1][0] = 0;
  matrix[1][1] = 2 / (t - b);
  matrix[1][2] = 0;
  matrix[1][3] = 0;

  matrix[2][0] = 0;
  matrix[2][1] = 0;
  matrix[2][2] = -2 / (f - n);
  matrix[2][3] = 0;

  matrix[3][0] = -(r + l) / (r - l);
  matrix[3][1] = -(t + b) / (t - b);
  matrix[3][2] = -(f + n) / (f - n);
  matrix[3][3] = 1;
}

void look_at(const float eye[3], const float target[3], const float up[3],
             float matrix[4][4]) {
  // TODO: temporary solution, we shouldn't rely on glm
  auto view = glm::lookAt(glm::vec3(eye[0], eye[1], eye[2]),
                          glm::vec3(target[0], target[1], target[2]),
                          glm::vec3(up[0], up[1], up[2]));

  memcpy(&matrix[0][0], &view[0][0], 4 * 4 * sizeof(float));
}

}  // namespace Math
}  // namespace GoumzAndStuff