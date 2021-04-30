#include <SFML/Graphics.hpp>
#include <iostream>
int main(){

    const int WINDOW_MAX_X = 1000;
    const int WINDOW_MAX_Y = 500;

    sf::RenderWindow window(sf::VideoMode(WINDOW_MAX_X, WINDOW_MAX_Y), "Pong!");
    sf::RectangleShape shape({20, 20});
    sf::RectangleShape leftPlayer({20, 100});
    sf::RectangleShape rightPlayer({20, 100});

    leftPlayer.setPosition({20, (WINDOW_MAX_Y - 100) /2});
    leftPlayer.setFillColor(sf::Color::White);

    rightPlayer.setPosition({WINDOW_MAX_X - 40, (WINDOW_MAX_Y - 100) / 2});
    rightPlayer.setFillColor(sf::Color::White);

    shape.setPosition({(WINDOW_MAX_X - 20) / 2, (WINDOW_MAX_Y - 20) / 2});
    shape.setFillColor(sf::Color::White);

    sf::Clock current;
    float deltaTime;
    float speed = 200;
    while (window.isOpen())
    {
        deltaTime = current.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPlayer.getPosition().y > 0.0 ){
            leftPlayer.move(0.0, -speed * deltaTime);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPlayer.getPosition().y < WINDOW_MAX_Y - 100){
            leftPlayer.move(0.0, speed * deltaTime);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPlayer.getPosition().y > 0.0 ){
            rightPlayer.move(0.0, -speed * deltaTime);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPlayer.getPosition().y < WINDOW_MAX_Y - 100){
            rightPlayer.move(0.0, speed * deltaTime);
        }

        std::cout << "First Player[ Y: " << leftPlayer.getPosition().y << " ] "
        << "Second Player[ Y: " << rightPlayer.getPosition().y << " ]"<< std::endl;
        window.clear();
        window.draw(shape);
        window.draw(leftPlayer);
        window.draw(rightPlayer);
        window.display();
    }
    return 0;
}
