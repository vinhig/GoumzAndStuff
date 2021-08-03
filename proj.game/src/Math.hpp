namespace GoumzAndStuff {
namespace Math {

void ortho_proj(const float &b, const float &t, const float &l, const float &r,
                const float &n, const float &f, float matrix[4][4]);

/**
 * @brief Construct 2D rotation matrix from given angle.
 * @param angle Rotation angle in radians.
 * @param matrix Output matrix.
 * @return None.
 */
void rotation_matrix(const float &angle, float matrix[4][4]);

/**
 * @brief Multiply two matrices with cross-platform instruction set.
 * @param a First matrix.
 * @param b Second matrix.
 * @param matrix Output matrix.
 */
void matrix_multiply(const float *a, const float *b, float* matrix);

}  // namespace Math

}  // namespace GoumzAndStuff