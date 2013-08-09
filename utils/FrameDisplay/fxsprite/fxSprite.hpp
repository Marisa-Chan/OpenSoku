#ifndef FXSPRITE_HPP_INCLUDED
#define FXSPRITE_HPP_INCLUDED

#include <SFML/Graphics/Drawable.hpp>
#include "fxTransformable.hpp"
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Rect.hpp>


namespace sf
{
class Texture;

class fxSprite : public Drawable, public fxTransformable
{
public :

    fxSprite();

    explicit fxSprite(const Texture& texture);

    fxSprite(const Texture& texture, const IntRect& rectangle);

    void setTexture(const Texture& texture, bool resetRect = false);

    void setTextureRect(const IntRect& rectangle);

    void setColor(const Color& color);

    const Texture* getTexture() const;

    const IntRect& getTextureRect() const;

    const Color& getColor() const;

    FloatRect getLocalBounds() const;

    FloatRect getGlobalBounds() const;

private :

    virtual void draw(RenderTarget& target, RenderStates states) const;

    void updatePositions();

    void updateTexCoords();

    Vertex         m_vertices[4]; ///< Vertices defining the sprite's geometry
    const Texture* m_texture;     ///< Texture of the sprite
    IntRect        m_textureRect; ///< Rectangle defining the area of the source texture to display
};

}


#endif
