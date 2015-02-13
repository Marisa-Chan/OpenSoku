#include "fxSprite.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>


namespace sf
{

fxSprite::fxSprite() :
    m_texture    (NULL),
    m_textureRect()
{
}

fxSprite::fxSprite(const Texture& texture) :
    m_texture    (NULL),
    m_textureRect()
{
    setTexture(texture);
}

fxSprite::fxSprite(const Texture& texture, const IntRect& rectangle) :
    m_texture    (NULL),
    m_textureRect()
{
    setTexture(texture);
    setTextureRect(rectangle);
}

void fxSprite::setTexture(const Texture& texture, bool resetRect)
{
    // Recompute the texture area if requested, or if there was no valid texture & rect before
    if (resetRect || (!m_texture && (m_textureRect == sf::IntRect())))
        setTextureRect(IntRect(0, 0, texture.getSize().x, texture.getSize().y));

    // Assign the new texture
    m_texture = &texture;
}

void fxSprite::setTextureRect(const IntRect& rectangle)
{
    if (rectangle != m_textureRect)
    {
        m_textureRect = rectangle;
        updatePositions();
        updateTexCoords();
    }
}


////////////////////////////////////////////////////////////
void fxSprite::setColor(const Color& color)
{
    // Update the vertices' color
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    m_vertices[3].color = color;
}


////////////////////////////////////////////////////////////
const Texture* fxSprite::getTexture() const
{
    return m_texture;
}


////////////////////////////////////////////////////////////
const IntRect& fxSprite::getTextureRect() const
{
    return m_textureRect;
}


////////////////////////////////////////////////////////////
const Color& fxSprite::getColor() const
{
    return m_vertices[0].color;
}


////////////////////////////////////////////////////////////
FloatRect fxSprite::getLocalBounds() const
{
    float width = static_cast<float>(std::abs(m_textureRect.width));
    float height = static_cast<float>(std::abs(m_textureRect.height));

    return FloatRect(0.f, 0.f, width, height);
}


////////////////////////////////////////////////////////////
FloatRect fxSprite::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}


////////////////////////////////////////////////////////////
void fxSprite::draw(RenderTarget& target, RenderStates states) const
{
    if (m_texture)
    {
        Vertex         vt[4];
        fxTransform  tf = getTransform();
        for (int i=0; i<4; i++)
        {
            vt[i].position = tf*m_vertices[i].position;
            vt[i].color = m_vertices[i].color;
            vt[i].texCoords = m_vertices[i].texCoords;
        }

        states.texture = m_texture;
        target.draw(vt, 4, Quads, states);
    }
}


////////////////////////////////////////////////////////////
void fxSprite::updatePositions()
{
    FloatRect bounds = getLocalBounds();

    m_vertices[0].position = Vector2f(0, 0);
    m_vertices[1].position = Vector2f(0, bounds.height);
    m_vertices[2].position = Vector2f(bounds.width, bounds.height);
    m_vertices[3].position = Vector2f(bounds.width, 0);
}


////////////////////////////////////////////////////////////
void fxSprite::updateTexCoords()
{
    float left   = static_cast<float>(m_textureRect.left);
    float right  = left + m_textureRect.width;
    float top    = static_cast<float>(m_textureRect.top);
    float bottom = top + m_textureRect.height;

    m_vertices[0].texCoords = Vector2f(left, top);
    m_vertices[1].texCoords = Vector2f(left, bottom);
    m_vertices[2].texCoords = Vector2f(right, bottom);
    m_vertices[3].texCoords = Vector2f(right, top);
}

} // namespace sf
