#include <SFML/Graphics.hpp>

class Figura : public sf::Drawable
{
    public:
        sf::Sprite sprite;
        sf::Texture texture;
    private:
        Figura(const std::string& caminhoImagem)
        {
            texture.loadFromFile(caminhoImagem);
            sprite.setTexture(texture);
        }
        ~Figura()
        {

        }
};
