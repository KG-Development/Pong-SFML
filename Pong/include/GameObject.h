#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject
{
    public:
        GameObject();
        GameObject(sf::Vector2f size, sf::Vector2f position = {0, 0}, sf::Color color = sf::Color::White);
        virtual ~GameObject();

        sf::RectangleShape getGameObject();

        void setPosition(sf::Vector2f newPosition);
        void setSize(sf::Vector2f newSize);
        void setColor(sf::Color newColor);

        void draw(sf::RenderWindow &window);

    protected:

    private:
        sf::RectangleShape obj;
};

#endif // GAMEOBJECT_H
