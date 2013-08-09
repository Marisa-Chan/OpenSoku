#ifndef FXTRANSFORM_HPP_INCLUDED
#define FXTRANSFORM_HPP_INCLUDED

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>





namespace sf
{

class fxTransform
{
public :

    fxTransform();
    fxTransform(float a00, float a01, float a02,
                float a10, float a11, float a12,
                float a20, float a21, float a22);

    fxTransform(float a00, float a01, float a02, float a03,
                float a10, float a11, float a12, float a13,
                float a20, float a21, float a22, float a23,
                float a30, float a31, float a32, float a33);

    const float* getMatrix() const;

    fxTransform getInverse() const;

    Vector2f transformPoint(float x, float y) const;

    Vector2f transformPoint(const Vector2f& point) const;

    FloatRect transformRect(const FloatRect& rectangle) const;

    fxTransform& combine(const fxTransform& transform);

    fxTransform& translate(float x, float y);

    fxTransform& translate(const Vector2f& offset);

    fxTransform& rotate(float angle);

    fxTransform& rotate(float angle, float centerX, float centerY);

    fxTransform& rotate(float angle, const Vector2f& center);

    fxTransform& scale(float scaleX, float scaleY);

    fxTransform& scale(float scaleX, float scaleY, float centerX, float centerY);

    fxTransform& scale(const Vector2f& factors);

    fxTransform& scale(const Vector2f& factors, const Vector2f& center);

    static const fxTransform Identity; ///< The identity transform (does nothing)

private:

    float m_matrix[16]; ///< 4x4 matrix defining the transformation
};
fxTransform operator *(const fxTransform& left, const fxTransform& right);

fxTransform& operator *=(fxTransform& left, const fxTransform& right);
Vector2f operator *(const fxTransform& left, const Vector2f& right);

} // namespace sf


#endif // FXTRANSFORM_HPP_INCLUDED
