#include "Vector2.hpp"

#include <cmath>

Vector2 Vector2::operator+(const Vector2& rhs) {
  return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator*(const Vector2& rhs) {
  return Vector2(x * rhs.x, y * rhs.y);
}

Vector2 Vector2::normalize() const {
  float v_length = length();
  return Vector2(x / v_length, y / v_length);
}

float Vector2::length() const { return sqrt(x * x + y * y); }

// multiply two matrices with NEON optimization
float multiply_mat4_mat4_NEON(float a[4][4], float b[4][4]) {
  float r[4][4];
  __asm__ __volatile__(
      // Load a
      "vld1.32 {d0-d1}, [%[a]] \n\t"
      "vld1.32 {d2-d3}, [%[a] + 4] \n\t"
      "vld1.32 {d4-d5}, [%[a] + 8] \n\t"
      "vld1.32 {d6-d7}, [%[a] + 12] \n\t"
      "vld1.32 {d8-d9}, [%[a] + 16] \n\t"
      "vld1.32 {d10-d11}, [%[a] + 20] \n\t"
      "vld1.32 {d12-d13}, [%[a] + 24] \n\t"
      "vld1.32 {d14-d15}, [%[a] + 28] \n\t"
      "vld1.32 {d16-d17}, [%[a] + 32] \n\t"
      "vld1.32 {d18-d19}, [%[a] + 36] \n\t"
      "vld1.32 {d20-d21}, [%[a] + 40] \n\t"
      "vld1.32 {d22-d23}, [%[a] + 44] \n\t"
      "vld1.32 {d24-d25}, [%[a] + 48] \n\t"
      "vld1.32 {d26-d27}, [%[a] + 52] \n\t"
      "vld1.32 {d28-d29}, [%[a] + 56] \n\t"
      "vld1.32 {d30-d31}, [%[a] + 60] \n\t"
      // Load b
      "vld1.32 {d0-d1}, [%[b]] \n\t"
      "vld1.32 {d2-d3}, [%[b] + 4] \n\t"
      "vld1.32 {d4-d5}, [%[b] + 8] \n\t"
      "vld1.32 {d6-d7}, [%[b] + 12] \n\t"
      "vld1.32 {d8-d9}, [%[b] + 16] \n\t"
      "vld1.32 {d10-d11}, [%[b] + 20] \n\t"
      "vld1.32 {d12-d13}, [%[b] + 24] \n\t"
      "vld1.32 {d14-d15}, [%[b] + 28] \n\t"
      "vld1.32 {d16-d17}, [%[b] + 32] \n\t"
      "vld1.32 {d18-d19}, [%[b] + 36] \n\t"
      "vld1.32 {d20-d21}, [%[b] + 40] \n\t"
      "vld1.32 {d22-d23}, [%[b] + 44] \n\t"
      "vld1.32 {d24-d25}, [%[b] + 48] \n\t"
      "vld1.32 {d26-d27}, [%[b] + 52] \n\t"
      "vld1.32 {d28-d29}, [%[b] + 56] \n\t"
      "vld1.32 {d30-d31}, [%[b] + 60] \n\t"
      // Multiply
      "vmul.f32 q0, q0, q1 \n\t"
      "vmul.f32 q2, q2, q3 \n\t"
      "vmul.f32 q4, q4, q5 \n\t"
      "vmul.f32 q6, q6, q7 \n\t"
      "vmul.f32 q8, q8, q9 \n\t"
      "vmul.f32 q10, q10, q11 \n\t"
      "vmul.f32 q12, q12, q13 \n\t"
      "vmul.f32 q14, q14, q15 \n\t"
      "vmul.f32 q16, q16, q17 \n\t"
      "vmul.f32 q18, q18, q19 \n\t"
      "vmul.f32 q20, q20, q21 \n\t"
      "vmul.f32 q22, q22, q23 \n\t"
      "vmul.f32 q24, q24, q25 \n\t"
      "vmul.f32 q26, q26, q27 \n\t"
      "vmul.f32 q28, q28, q29 \n\t"
      "vmul.f32 q30, q30, q31 \n\t"
      // Add
      "vadd.f32 q0, q0, q2 \n\t"
      "vadd.f32 q4, q4, q6 \n\t"
      "vadd.f32 q8, q8, q10 \n\t"
      "vadd.f32 q12, q12, q14 \n\t"
      "vadd.f32 q16, q16, q18 \n\t"
      "vadd.f32 q20, q20, q22 \n\t"
      "vadd.f32 q24, q24, q26 \n\t"
      "vadd.f32 q28, q28, q30 \n\t"
      // Store
      "vst1.32 {d0-d1}, [%[r]] \n\t"
      "vst1.32 {d2-d3}, [%[r] + 4] \n\t"
      "vst1.32 {d4-d5}, [%[r] + 8] \n\t"
      "vst1.32 {d6-d7}, [%[r] + 12] \n\t"
      "vst1.32 {d8-d9}, [%[r] + 16] \n\t"
      "vst1.32 {d10-d11}, [%[r] + 20] \n\t"
      "vst1.32 {d12-d13}, [%[r] + 24] \n\t"
      "vst1.32 {d14-d15}, [%[r] + 28] \n\t"
      "vst1.32 {d16-d17}, [%[r] + 32] \n\t"
      "vst1.32 {d18-d19}, [%[r] + 36] \n\t"
      "vst1.32 {d20-d21}, [%[r] + 40] \n\t"
      "vst1.32 {d22-d23}, [%[r] + 44] \n\t"
      "vst1.32 {d24-d25}, [%[r] + 48] \n\t"
      "vst1.32 {d26-d27}, [%[r] + 52] \n\t"
      "vst1.32 {d28-d29}, [%[r] + 56] \n\t"
      "vst1.32 {d30-d31}, [%[r] + 60] \n\t"
      : [r] "+r"(r)
      : [a] "r"(a), [b] "r"(b)
      : "cc", "memory", "q0", "q1", "q2", "q3", "q4", "q5", "q6", "q7", "q8",
        "q9", "q10", "q11", "q12", "q13", "q14", "q15", "q16", "q17", "q18",
        "q19", "q20", "q21", "q22", "q23", "q24", "q25", "q26", "q27", "q28",
        "q29", "q30", "q31");
}
