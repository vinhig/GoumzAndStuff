namespace GoumzAndStuff {
namespace Math {

void ortho_proj(const float &b, const float &t, const float &l, const float &r,
                const float &n, const float &f, float matrix[4][4]);

void look_at(const float eye[3], const float target[3], const float up[3],
             float matrix[4][4]);

}  // namespace Math

}  // namespace GoumzAndStuff