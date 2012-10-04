#include "fxTransformable.hpp"
#include <cmath>


namespace sf
{

fxTransformable::fxTransformable() :
    m_origin                    (0, 0),
    m_position                  (0, 0),
    m_rotation_x                (0),
    m_rotation_y                (0),
    m_rotation_z                (0),
    m_scale                     (1, 1),
    m_transform                 (),
    m_transformNeedUpdate       (true),
    m_inverseTransform          (),
    m_inverseTransformNeedUpdate(true)
{
}

fxTransformable::~fxTransformable()
{
}

void fxTransformable::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
    m_transformNeedUpdate = true;
    m_inverseTransformNeedUpdate = true;
}


void fxTransformable::setPosition(const Vector2f& position)
{
    setPosition(position.x, position.y);
}

void fxTransformable::setRotation(float angle_x,float angle_y,float angle_z)
{
    m_rotation_x = static_cast<float>(fmod(angle_x, 360));
    if (m_rotation_x < 0)
        m_rotation_x += 360.f;

    m_rotation_y = static_cast<float>(fmod(angle_y, 360));
    if (m_rotation_y < 0)
        m_rotation_y += 360.f;

    m_rotation_z = static_cast<float>(fmod(angle_z, 360));
    if (m_rotation_z < 0)
        m_rotation_z += 360.f;

    m_transformNeedUpdate = true;
    m_inverseTransformNeedUpdate = true;
}

void fxTransformable::setRotationX(float angle)
{
    m_rotation_x = static_cast<float>(fmod(angle, 360));
    if (m_rotation_x < 0)
        m_rotation_x += 360.f;

    m_transformNeedUpdate = true;
    m_inverseTransformNeedUpdate = true;
}

void fxTransformable::setRotationY(float angle)
{
    m_rotation_y = static_cast<float>(fmod(angle, 360));
    if (m_rotation_y < 0)
        m_rotation_y += 360.f;

    m_transformNeedUpdate = true;
    m_inverseTransformNeedUpdate = true;
}

void fxTransformable::setRotationZ(float angle)
{
    m_rotation_z = static_cast<float>(fmod(angle, 360));
    if (m_rotation_z < 0)
        m_rotation_z += 360.f;

    m_transformNeedUpdate = true;
    m_inverseTransformNeedUpdate = true;
}


void fxTransformable::setScale(float factorX, float factorY)
{
    m_scale.x = factorX;
    m_scale.y = factorY;
    m_transformNeedUpdate = true;
    m_inverseTransformNeedUpdate = true;
}

void fxTransformable::setScale(const Vector2f& factors)
{
    setScale(factors.x, factors.y);
}


void fxTransformable::setOrigin(float x, float y)
{
    m_origin.x = x;
    m_origin.y = y;
    m_transformNeedUpdate = true;
    m_inverseTransformNeedUpdate = true;
}

void fxTransformable::setOrigin(const Vector2f& origin)
{
    setOrigin(origin.x, origin.y);
}


const Vector2f& fxTransformable::getPosition() const
{
    return m_position;
}


float fxTransformable::getRotation() const
{
    return m_rotation_z;
}

const Vector2f& fxTransformable::getScale() const
{
    return m_scale;
}

const Vector2f& fxTransformable::getOrigin() const
{
    return m_origin;
}

void fxTransformable::move(float offsetX, float offsetY)
{
    setPosition(m_position.x + offsetX, m_position.y + offsetY);
}

void fxTransformable::move(const Vector2f& offset)
{
    setPosition(m_position.x + offset.x, m_position.y + offset.y);
}

void fxTransformable::rotate(float angle)
{
    setRotationZ(m_rotation_z + angle);
}

void fxTransformable::scale(float factorX, float factorY)
{
    setScale(m_scale.x * factorX, m_scale.y * factorY);
}

void fxTransformable::scale(const Vector2f& factor)
{
    setScale(m_scale.x * factor.x, m_scale.y * factor.y);
}

const fxTransform& fxTransformable::getTransform() const
{
    if (m_transformNeedUpdate)
    {
        /*float angle  = -m_rotation_x * 3.141592654f / 180.f;
        float cosine = static_cast<float>(std::cos(angle));
        float sine   = static_cast<float>(std::sin(angle));

        m_transform = fxTransform(m_scale.x,              0.f,    0.f, m_position.x,
                                        0.f, m_scale.y*cosine,   sine, m_position.y,
                                        0.f,            -sine, cosine,            0,
                                        0.f,              0.f,    0.f,          1.f);


        angle  = -m_rotation_y * 3.141592654f / 180.f;
        cosine = static_cast<float>(std::cos(angle));
        sine   = static_cast<float>(std::sin(angle));

        m_transform.combine(fxTransform( cosine, 0.f,  -sine,   0,
                                            0.f, 1.f,    0.f,   0,
                                           sine, 0.f, cosine,   0,
                                            0.f, 0.f,    0.f, 1.f));

        angle  = -m_rotation_z * 3.141592654f / 180.f;
        cosine = static_cast<float>(std::cos(angle));
        sine   = static_cast<float>(std::sin(angle));

        m_transform.combine(fxTransform( cosine, sine, 0.f, 0,
                                        -sine, cosine, 0.f, 0,
                                         0.f, 0.f, 1.f, 0,
                                         0.f, 0.f, 0.f, 1.f));

        m_transform.combine(fxTransform( 1.f, 0.f, 0.f, -m_origin.x,
                                   0.f, 1.f, 0.f, -m_origin.y,
                                   0.f, 0.f, 1.f, 0,
                                   0.f, 0.f, 0.f, 1.f));
        */

        float angle  = -m_rotation_x * 3.141592654f / 180.f;
        float cx = static_cast<float>(std::cos(angle));
        float sx   = static_cast<float>(std::sin(angle));

        angle  = -m_rotation_y * 3.141592654f / 180.f;
        float cy = static_cast<float>(std::cos(angle));
        float sy   = static_cast<float>(std::sin(angle));

        angle  = -m_rotation_z * 3.141592654f / 180.f;
        float cz = static_cast<float>(std::cos(angle));
        float sz   = static_cast<float>(std::sin(angle));

        m_transform = fxTransform(
                          m_scale.x*cy*cz,
                          m_scale.x*cy*sz,
                          m_scale.x*(-sy),
                          m_scale.x*cy*cz*(-m_origin.x) + m_scale.x*cy*sz*(-m_origin.y) + m_position.x,
                          sx*sy*cz + m_scale.y*cx*(-sz),
                          sx*sy*sz + m_scale.y*cx*cz,
                          sx*cy,
                          (sx*sy*cz+m_scale.y*cx*-sz)*(-m_origin.x) + (sx*sy*sz+m_scale.y*cx*cz)*(-m_origin.y) + m_position.y,
                          cx*sy*cz + sx*sz,
                          cx*sy*sz + (-sx)*cz,
                          cx*cy,
                          (cx*sy*cz+sx*sz)*(-m_origin.x) + (cx*sy*sz+(-sx)*cz)*(-m_origin.y),
                          0,0,0,1);



        m_transformNeedUpdate = false;
    }

    return m_transform;
}

const fxTransform& fxTransformable::getInverseTransform() const
{
    // Recompute the inverse transform if needed
    if (m_inverseTransformNeedUpdate)
    {
        m_inverseTransform = getTransform().getInverse();
        m_inverseTransformNeedUpdate = false;
    }

    return m_inverseTransform;
}

}
