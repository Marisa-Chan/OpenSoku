#include "fxTransform.hpp"
#include <cmath>


namespace sf
{
const fxTransform fxTransform::Identity;

fxTransform::fxTransform()
{
    m_matrix[0] = 1.f;
    m_matrix[4] = 0.f;
    m_matrix[8]  = 0.f;
    m_matrix[12] = 0.f;
    m_matrix[1] = 0.f;
    m_matrix[5] = 1.f;
    m_matrix[9]  = 0.f;
    m_matrix[13] = 0.f;
    m_matrix[2] = 0.f;
    m_matrix[6] = 0.f;
    m_matrix[10] = 1.f;
    m_matrix[14] = 0.f;
    m_matrix[3] = 0.f;
    m_matrix[7] = 0.f;
    m_matrix[11] = 0.f;
    m_matrix[15] = 1.f;
}


fxTransform::fxTransform(float a00, float a01, float a02,
                         float a10, float a11, float a12,
                         float a20, float a21, float a22)
{
    m_matrix[0] = a00;
    m_matrix[4] = a01;
    m_matrix[8]  = 0.f;
    m_matrix[12] = a02;
    m_matrix[1] = a10;
    m_matrix[5] = a11;
    m_matrix[9]  = 0.f;
    m_matrix[13] = a12;
    m_matrix[2] = 0.f;
    m_matrix[6] = 0.f;
    m_matrix[10] = 1.f;
    m_matrix[14] = 0.f;
    m_matrix[3] = a20;
    m_matrix[7] = a21;
    m_matrix[11] = 0.f;
    m_matrix[15] = a22;
}
fxTransform::fxTransform(float a00, float a01, float a02, float a03,
                         float a10, float a11, float a12, float a13,
                         float a20, float a21, float a22, float a23,
                         float a30, float a31, float a32, float a33)
{
    m_matrix[0] = a00;
    m_matrix[4] = a01;
    m_matrix[8]  = a02;
    m_matrix[12] = a03;
    m_matrix[1] = a10;
    m_matrix[5] = a11;
    m_matrix[9]  = a12;
    m_matrix[13] = a13;
    m_matrix[2] = a20;
    m_matrix[6] = a21;
    m_matrix[10] = a22;
    m_matrix[14] = a23;
    m_matrix[3] = a30;
    m_matrix[7] = a31;
    m_matrix[11] = a32;
    m_matrix[15] = a33;
}

const float* fxTransform::getMatrix() const
{
    return m_matrix;
}

fxTransform fxTransform::getInverse() const
{
    float det = m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
                m_matrix[1] * (m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) +
                m_matrix[3] * (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]);

    if (det != 0.f)
    {
        return fxTransform( (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) / det,
                            -(m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) / det,
                            (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) / det,
                            -(m_matrix[15] * m_matrix[1] - m_matrix[3] * m_matrix[13]) / det,
                            (m_matrix[15] * m_matrix[0] - m_matrix[3] * m_matrix[12]) / det,
                            -(m_matrix[13] * m_matrix[0] - m_matrix[1] * m_matrix[12]) / det,
                            (m_matrix[7]  * m_matrix[1] - m_matrix[3] * m_matrix[5])  / det,
                            -(m_matrix[7]  * m_matrix[0] - m_matrix[3] * m_matrix[4])  / det,
                            (m_matrix[5]  * m_matrix[0] - m_matrix[1] * m_matrix[4])  / det);
    }
    else
    {
        return Identity;
    }
}

Vector2f fxTransform::transformPoint(float x, float y) const
{
    return Vector2f(m_matrix[0] * x + m_matrix[4] * y + m_matrix[12],
                    m_matrix[1] * x + m_matrix[5] * y + m_matrix[13]);
}

Vector2f fxTransform::transformPoint(const Vector2f& point) const
{
    return transformPoint(point.x, point.y);
}

FloatRect fxTransform::transformRect(const FloatRect& rectangle) const
{
    const Vector2f points[] =
    {
        transformPoint(rectangle.left, rectangle.top),
        transformPoint(rectangle.left, rectangle.top + rectangle.height),
        transformPoint(rectangle.left + rectangle.width, rectangle.top),
        transformPoint(rectangle.left + rectangle.width, rectangle.top + rectangle.height)
    };

    float left = points[0].x;
    float top = points[0].y;
    float right = points[0].x;
    float bottom = points[0].y;
    for (int i = 1; i < 4; ++i)
    {
        if      (points[i].x < left)   left = points[i].x;
        else if (points[i].x > right)  right = points[i].x;
        if      (points[i].y < top)    top = points[i].y;
        else if (points[i].y > bottom) bottom = points[i].y;
    }

    return FloatRect(left, top, right - left, bottom - top);
}

fxTransform& fxTransform::combine(const fxTransform& transform)
{
    const float* a = m_matrix;
    const float* b = transform.m_matrix;

    *this = fxTransform(a[0] * b[0]  + a[4] * b[1]  + a[8] * b[2] + a[12] * b[3],
                        a[0] * b[4]  + a[4] * b[5]  + a[8] * b[6] + a[12] * b[7],
                        a[0] * b[8]  + a[4] * b[9]  + a[8] * b[10]+ a[12] * b[11],
                        a[0] * b[12] + a[4] * b[13] + a[8] * b[14]+ a[12] * b[15],
                        a[1] * b[0]  + a[5] * b[1]  + a[9] * b[2] + a[13] * b[3],
                        a[1] * b[4]  + a[5] * b[5]  + a[9] * b[6] + a[13] * b[7],
                        a[1] * b[8]  + a[5] * b[9]  + a[9] * b[10]+ a[13] * b[11],
                        a[1] * b[12] + a[5] * b[13] + a[9] * b[14]+ a[13] * b[15],
                        a[2] * b[0]  + a[6] * b[1]  + a[10] * b[2] + a[14] * b[3],
                        a[2] * b[4]  + a[6] * b[5]  + a[10] * b[6] + a[14] * b[7],
                        a[2] * b[8]  + a[6] * b[9]  + a[10] * b[10]+ a[14] * b[11],
                        a[2] * b[12] + a[6] * b[13] + a[10] * b[14]+ a[14] * b[15],
                        a[3] * b[0]  + a[7] * b[1]  + a[11] * b[2] + a[15] * b[3],
                        a[3] * b[4]  + a[7] * b[5]  + a[11] * b[6] + a[15] * b[7],
                        a[3] * b[8]  + a[7] * b[9]  + a[11] * b[10]+ a[15] * b[11],
                        a[3] * b[12] + a[7] * b[13] + a[11] * b[14]+ a[15] * b[15]);

    return *this;
}

fxTransform& fxTransform::rcombine(const fxTransform& transform)
{
    const float* b = m_matrix;
    const float* a = transform.m_matrix;

    *this = fxTransform(a[0] * b[0]  + a[4] * b[1]  + a[8] * b[2] + a[12] * b[3],
                        a[0] * b[4]  + a[4] * b[5]  + a[8] * b[6] + a[12] * b[7],
                        a[0] * b[8]  + a[4] * b[9]  + a[8] * b[10]+ a[12] * b[11],
                        a[0] * b[12] + a[4] * b[13] + a[8] * b[14]+ a[12] * b[15],
                        a[1] * b[0]  + a[5] * b[1]  + a[9] * b[2] + a[13] * b[3],
                        a[1] * b[4]  + a[5] * b[5]  + a[9] * b[6] + a[13] * b[7],
                        a[1] * b[8]  + a[5] * b[9]  + a[9] * b[10]+ a[13] * b[11],
                        a[1] * b[12] + a[5] * b[13] + a[9] * b[14]+ a[13] * b[15],
                        a[2] * b[0]  + a[6] * b[1]  + a[10] * b[2] + a[14] * b[3],
                        a[2] * b[4]  + a[6] * b[5]  + a[10] * b[6] + a[14] * b[7],
                        a[2] * b[8]  + a[6] * b[9]  + a[10] * b[10]+ a[14] * b[11],
                        a[2] * b[12] + a[6] * b[13] + a[10] * b[14]+ a[14] * b[15],
                        a[3] * b[0]  + a[7] * b[1]  + a[11] * b[2] + a[15] * b[3],
                        a[3] * b[4]  + a[7] * b[5]  + a[11] * b[6] + a[15] * b[7],
                        a[3] * b[8]  + a[7] * b[9]  + a[11] * b[10]+ a[15] * b[11],
                        a[3] * b[12] + a[7] * b[13] + a[11] * b[14]+ a[15] * b[15]);

    return *this;
}

fxTransform& fxTransform::translate(float x, float y)
{
    fxTransform translation(1, 0, x,
                            0, 1, y,
                            0, 0, 1);

    return combine(translation);
}

fxTransform& fxTransform::translate3(float x, float y, float z)
{
    fxTransform translation(1, 0, 0, x,
                            0, 1, 0, y,
                            0, 0, 1, z,
                            0, 0, 0, 1);

    return combine(translation);
}

fxTransform& fxTransform::translate(const Vector2f& offset)
{
    return translate(offset.x, offset.y);
}

fxTransform& fxTransform::rotate(float angle)
{
    float rad = angle * 3.141592654f / 180.f;
    float cos = std::cos(rad);
    float sin = std::sin(rad);

    fxTransform rotation(cos, -sin, 0,
                         sin,  cos, 0,
                         0,    0,   1);

    return combine(rotation);
}

fxTransform& fxTransform::rotate3(float x, float y, float z)
{
    /*float rad = x * 3.141592654f / 180.f;
    float cos = std::cos(rad);
    float sin = std::sin(rad);

    fxTransform rotationX(  1,   0,   0,   0,
                            0, cos,-sin,   0,
                            0, sin, cos,   0,
                            0,   0,   0,   1);

    rad = y * 3.141592654f / 180.f;
    cos = std::cos(rad);
    sin = std::sin(rad);

    fxTransform rotationY(cos,   0, sin,   0,
                            0,   1,   0,   0,
                         -sin,   0, cos,   0,
                            0,   0,   0,   1);

    rad = z * 3.141592654f / 180.f;
    cos = std::cos(rad);
    sin = std::sin(rad);

    fxTransform rotationZ(cos, -sin,  0,   0,
                          sin,  cos,  0,   0,
                            0,    0,  1,   0,
                            0,    0,  0,   1);

    combine(rotationX);
    combine(rotationY);
    return combine(rotationZ);*/


    float rad = x * 3.141592654f / 180.f;
    float cx = std::cos(rad);
    float sx = std::sin(rad);
    rad = y * 3.141592654f / 180.f;
    float cy = std::cos(rad);
    float sy = std::sin(rad);
    rad = z * 3.141592654f / 180.f;
    float cz = std::cos(rad);
    float sz = std::sin(rad);

    fxTransform rotation(        cy*cz,           -cy*sz,      sy,    0,
                        sx*sy*cz+cx*sz,  -sx*sy*sz+cx*cz,  -sx*cy,    0,
                       -cx*sy*cz+sx*sz,   cx*sy*sz+sx*cz,   cx*cy,    0,
                                     0,                0,       0,    1);


    return combine(rotation);

}

fxTransform& fxTransform::rotate3(float x, float y, float z, float cX, float cY, float cZ)
{
    /*translate(cX,cY,cZ);
    rotate3(x,y,z);
    return translate(-cX,-cY,-cZ);*/

    float rad = x * 3.141592654f / 180.f;
    float cx = std::cos(rad);
    float sx = std::sin(rad);
    rad = y * 3.141592654f / 180.f;
    float cy = std::cos(rad);
    float sy = std::sin(rad);
    rad = z * 3.141592654f / 180.f;
    float cz = std::cos(rad);
    float sz = std::sin(rad);


    fxTransform rotation(        cy*cz,           -cy*sz,      sy,                             (1-cy*cz)*cX+cy*sz*cY-sy*cZ,
                        sx*sy*cz+cx*sz,  -sx*sy*sz+cx*cz,  -sx*cy,     -(sx*sy*cz+cx*sz)*cX+(1+sx*sy*sz-cx*cz)*cY+sx*cy*cZ,
                       -cx*sy*cz+sx*sz,   cx*sy*sz+sx*cz,   cx*cy,  -(-cx*sy*cz+sx*sz)*cX-(cx*sy*sz+sx*cz)*cY+(1-cx*cy)*cZ,
                                     0,                0,       0,                                                       1);


    return combine(rotation);
}

fxTransform& fxTransform::rotate(float angle, float centerX, float centerY)
{
    float rad = angle * 3.141592654f / 180.f;
    float cos = std::cos(rad);
    float sin = std::sin(rad);

    fxTransform rotation(cos, -sin, centerX * (1 - cos) + centerY * sin,
                         sin,  cos, centerY * (1 - cos) - centerX * sin,
                         0,    0,   1);

    return combine(rotation);
}

fxTransform& fxTransform::rotate(float angle, const Vector2f& center)
{
    return rotate(angle, center.x, center.y);
}

fxTransform& fxTransform::scale(float scaleX, float scaleY)
{
    fxTransform scaling(scaleX, 0,      0,
                        0,      scaleY, 0,
                        0,      0,      1);

    return combine(scaling);
}

fxTransform& fxTransform::scale3(float scaleX, float scaleY, float scaleZ)
{
    fxTransform scaling(scaleX, 0,      0,     0,
                        0,      scaleY, 0,     0,
                        0,      0, scaleZ,     0,
                        0,      0,      0,     1);

    return combine(scaling);
}

fxTransform& fxTransform::scale3(float scaleX, float scaleY, float scaleZ, float cX, float cY, float cZ)
{
    /*translate(cX, cY, cZ);
    scale3(scaleX,scaleY,scaleZ);

    return translate(-cX,-cY,-cZ);*/
    fxTransform scaling(scaleX,      0,      0,  (1.0-scaleX)*cX,
                             0, scaleY,      0,  (1.0-scaleY)*cY,
                             0,      0,	scaleZ,  (1.0-scaleZ)*cZ,
                             0,      0,      0,                1);
    return combine(scaling);
}

fxTransform& fxTransform::scale(float scaleX, float scaleY, float centerX, float centerY)
{
    fxTransform scaling(scaleX, 0,      centerX * (1 - scaleX),
                        0,      scaleY, centerY * (1 - scaleY),
                        0,      0,      1);

    return combine(scaling);
}

fxTransform& fxTransform::scale(const Vector2f& factors)
{
    return scale(factors.x, factors.y);
}

fxTransform& fxTransform::scale(const Vector2f& factors, const Vector2f& center)
{
    return scale(factors.x, factors.y, center.x, center.y);
}

fxTransform& fxTransform::reset()
{
    *this = fxTransform(1.0,  0.0,  0.0,  0.0,
                        0.0,  1.0,  0.0,  0.0,
                        0.0,  0.0,  1.0,  0.0,
                        0.0,  0.0,  0.0,  1.0);

    return *this;
}

fxTransform operator *(const fxTransform& left, const fxTransform& right)
{
    return fxTransform(left).combine(right);
}

fxTransform& operator *=(fxTransform& left, const fxTransform& right)
{
    return left.combine(right);
}

Vector2f operator *(const fxTransform& left, const Vector2f& right)
{
    return left.transformPoint(right);
}

} // namespace sf
