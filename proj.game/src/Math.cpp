#if defined(__ARM_NEON)
#include <arm_neon.h>
#else
#include <immintrin.h>
#endif

#include <cmath>
#include <cstring>

#include "Log.hpp"

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

void rotation_matrix(const float &angle, float matrix[4][4]) {
  float c = cos(angle);
  float s = sin(angle);
  matrix[0][0] = c;
  matrix[0][1] = -s;
  matrix[1][0] = s;
  matrix[1][1] = c;
  matrix[2][2] = 1;
  matrix[3][3] = 1;
}

#if defined(__ARM_NEON)
/**
 * @brief Multiply two matrices with NEON instructions.
 * @param a First matrix.
 * @param b Second matrix.
 * @param result Output matrix.
 * @return None.
 */
void matrix_multiply_NEON(const float *a, const float *b, float *result) {
  float32x4_t a0 = vld1q_f32(a);
  float32x4_t a1 = vld1q_f32(a + 4);
  float32x4_t a2 = vld1q_f32(a + 8);
  float32x4_t a3 = vld1q_f32(a + 12);

  float32x4_t b0 = vld1q_f32(b);
  float32x4_t b1 = vld1q_f32(b + 4);
  float32x4_t b2 = vld1q_f32(b + 8);
  float32x4_t b3 = vld1q_f32(b + 12);

  float32x4_t r0 = vmovq_n_f32(0);
  float32x4_t r1 = vmovq_n_f32(0);
  float32x4_t r2 = vmovq_n_f32(0);
  float32x4_t r3 = vmovq_n_f32(0);

  r0 = vmlaq_f32(r0, a0, b0);
  r0 = vmlaq_f32(r0, a1, b0);
  r0 = vmlaq_f32(r0, a2, b0);
  r0 = vmlaq_f32(r0, a3, b0);
  vst1q_f32(result, r0);

  r1 = vmlaq_f32(r1, a0, b1);
  r1 = vmlaq_f32(r1, a1, b1);
  r1 = vmlaq_f32(r1, a2, b1);
  r1 = vmlaq_f32(r1, a3, b1);
  vst1q_f32(result + 4, r1);

  r2 = vmlaq_f32(r2, a0, b2);
  r2 = vmlaq_f32(r2, a1, b2);
  r2 = vmlaq_f32(r2, a2, b2);
  r2 = vmlaq_f32(r2, a3, b2);
  vst1q_f32(result + 8, r2);

  r3 = vmlaq_f32(r3, a0, b3);
  r3 = vmlaq_f32(r3, a1, b3);
  r3 = vmlaq_f32(r3, a2, b3);
  r3 = vmlaq_f32(r3, a3, b3);
  vst1q_f32(result + 12, r3);
}
#else
/**
 * @brief Multiply two matrices with SSE instructions.
 * @param a First matrix.
 * @param b Second matrix.
 * @param result Output matrix.
 * @return None.
 */
void matrix_multiply_SSE(const float *a, const float *b, float *result) {
  Log::error("no implemented!");
  /*__m128 a0 = _mm_loadu_ps(&a[0][0]);
  __m128 a1 = _mm_loadu_ps(&a[1][0]);
  __m128 a2 = _mm_loadu_ps(&a[2][0]);
  __m128 a3 = _mm_loadu_ps(&a[3][0]);
  __m128 b0 = _mm_loadu_ps(&b[0][0]);
  __m128 b1 = _mm_loadu_ps(&b[1][0]);
  __m128 b2 = _mm_loadu_ps(&b[2][0]);
  __m128 b3 = _mm_loadu_ps(&b[3][0]);
  __m128 r0 = _mm_mul_ps(a0, b0);
  __m128 r1 = _mm_mul_ps(a1, b1);
  __m128 r2 = _mm_mul_ps(a2, b2);
  __m128 r3 = _mm_mul_ps(a3, b3);
  _mm_storeu_ps(&result[0][0], r0);
  _mm_storeu_ps(&result[1][0], r1);
  _mm_storeu_ps(&result[2][0], r2);
  _mm_storeu_ps(&result[3][0], r3);*/
}
#endif

/**
 * @brief Multiply two matrices with cross-platform instruction set.
 * @param a First matrix.
 * @param b Second matrix.
 * @param matrix Output matrix.
 */
void matrix_multiply(const float *a, const float *b, float *matrix) {
#if defined(__ARM_NEON)
  matrix_multiply_NEON(a, b, matrix);
#else
  matrix_multiply_SSE(a, b, matrix);
#endif
}

}  // namespace Math
}  // namespace GoumzAndStuff