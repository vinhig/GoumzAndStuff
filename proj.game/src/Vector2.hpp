class Vector2 {
 private:
  // coordinates of this vector
  float x, y;

 public:
  Vector2(float x, float y);
  ~Vector2();

  /**
   * @brief Add a vector.
   * @param rhs The vector to add.
   * @return A new vector that is the sum of this and the given vector.
   */
  Vector2 operator+(const Vector2& rhs);

  /**
   * @brief Substract a vector.
   * @param rhs The vector to substract.
   * @return A new vector that is the difference of this and the given vector.
   */
  Vector2 operator-(const Vector2& rhs);

  /**
   * @brief Substract a vector.
   * @param rhs The vector to substract.
   * @return A new vector that is the difference of this and the given vector.
   */
  Vector2 operator*(const Vector2& rhs);
  Vector2 operator/(const Vector2& rhs);

  Vector2 normalize() const;

  float length() const;
};