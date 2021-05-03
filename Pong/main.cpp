#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

bool AABB(sf::RectangleShape &a, sf::RectangleShape &b);
void drawField(sf::RenderWindow &window);
void reset(sf::RectangleShape &leftPlayer, sf::RectangleShape &ball, sf::RectangleShape &rightPlayer);
void rgb(sf::RectangleShape &obj, float i);
const int WINDOW_MAX_X = 1000;
const int WINDOW_MAX_Y = 500;

bool menu(sf::RenderWindow &menu);

int main(){

    sf::RenderWindow window(sf::VideoMode(WINDOW_MAX_X, WINDOW_MAX_Y), "Pong!", sf::Style::Titlebar | sf::Style::Close);
    sf::RectangleShape ball({20, 20});
    sf::RectangleShape leftPlayer({20, 100});
    sf::RectangleShape rightPlayer({20, 100});

    while(menu(window));

    leftPlayer.setPosition({20, (WINDOW_MAX_Y - 100) /2});
    leftPlayer.setFillColor(sf::Color::White);

    rightPlayer.setPosition({WINDOW_MAX_X - 40, (WINDOW_MAX_Y - 100) / 2});
    rightPlayer.setFillColor(sf::Color::White);

    ball.setPosition({(WINDOW_MAX_X - 20) / 2, (WINDOW_MAX_Y - 20) / 2});
    ball.setFillColor(sf::Color::White);

    sf::Clock current;
    float deltaTime;
    float speed = 200;
    float ballSpeed = 200;
    float delay = 0;
    float index = 0;
    int gameState = 0; //0 Pause //1 Run //2 Game Over only if one reach the score 10
    sf::Vector2f ballVec(1, 0);

    while (window.isOpen())
    {
        deltaTime = current.restart().asSeconds();
        sf::Event event;

        if(index < (2*3.64)){
            index += 1;
        }else{
            index = 0;
        }
        if(ballSpeed >= 200.1){
            ballSpeed -= deltaTime;
        }
        if(delay > 0){
            delay -= deltaTime;
        }
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        switch(gameState){
        case 0:
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && delay <= 0){
                gameState = 1;
                delay = 0.1;
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
                window.close();
            }
            break;
        case 2:
            break;
        case 1:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && delay <= 0){
                        gameState = 0;
                        delay = 0.1;
                }
                if( sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPlayer.getPosition().y > 20 ){
                    leftPlayer.move(0.0, -speed * deltaTime);
                }else if( sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPlayer.getPosition().y < WINDOW_MAX_Y - 120 ){
                    leftPlayer.move(0.0, speed * deltaTime);
                }

                if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPlayer.getPosition().y > 20 ){
                    rightPlayer.move(0.0, -speed * deltaTime);
                }else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPlayer.getPosition().y < WINDOW_MAX_Y - 120 ){
                    rightPlayer.move(0.0, speed * deltaTime);
                }

                if(AABB(leftPlayer, ball)){
                    if(ball.getPosition().y >= leftPlayer.getPosition().y + 66){
                        ballVec.y = 1;
                    }else if (ball.getPosition().y <= leftPlayer.getPosition().y + 33){
                        ballVec.y = -1;
                    }
                    ballVec.x *= -1;
                    ball.setPosition(ball.getPosition().x + ballVec.x, ball.getPosition().y);
                    ballSpeed = 250;
                }else if(AABB(rightPlayer, ball)){
                    if(ball.getPosition().y >= rightPlayer.getPosition().y + 66){
                        ballVec.y = 1;
                    }else if (ball.getPosition().y <= rightPlayer.getPosition().y + 33){
                        ballVec.y = -1;
                    }
                    ballVec.x *= -1;
                    ball.setPosition(ball.getPosition().x + ballVec.x, ball.getPosition().y);
                    ballSpeed = 250;
                }
                if(ball.getPosition().y < 20 || ball.getPosition().y > WINDOW_MAX_Y - 40){
                    ballVec.y *= -1;
                    ball.setPosition(ball.getPosition().x, ball.getPosition().y + ballVec.y);
                }else if(ball.getPosition().x < 20 || ball.getPosition().x > WINDOW_MAX_X - 40){
                    reset(leftPlayer, ball, rightPlayer);
                    ballVec.x *= -1;
                    ballVec.y = 0;
                }
                //rgb(ball, index);
                ball.move((ballVec.x * ballSpeed) * deltaTime, (ballVec.y * ballSpeed) * deltaTime);

                std::cout << "First Player[ Y: " << leftPlayer.getPosition().y << " ] "
                          << "Second Player[ Y: " << rightPlayer.getPosition().y << " ]"
                          << "BallVec: [ X: " << ballVec.x << " Y: " << ballVec.y << " Speed: " << ballSpeed <<std::endl;




            break;
            }
        window.clear();
        drawField(window);
        window.draw(ball);
        window.draw(leftPlayer);
        window.draw(rightPlayer);
        window.display();
    }
    return 0;
}

void rgb(sf::RectangleShape &obj, float i){
    float index = (float) sin((double) i);
    obj.setFillColor(sf::Color(index, index, index));
}

void reset(sf::RectangleShape &leftPlayer, sf::RectangleShape &ball, sf::RectangleShape &rightPlayer){
    leftPlayer.setPosition({20, (WINDOW_MAX_Y - 100) /2});
    rightPlayer.setPosition({WINDOW_MAX_X - 40, (WINDOW_MAX_Y - 100) / 2});
    ball.setPosition({(WINDOW_MAX_X - 20) / 2, (WINDOW_MAX_Y - 20) / 2});
}

void drawField(sf::RenderWindow &window){

    float y = 20;
    sf::RectangleShape shapes[12];
    sf::RectangleShape lines[2];

    for(int i = 0; i < 12; i++){
        shapes[i].setFillColor(sf::Color(115, 115, 115));
        shapes[i].setSize({20, 20});
        shapes[i].setPosition({(1000 - 20) / 2, y});
        y += 40;
        window.draw(shapes[i]);
        if(i < 2){
            lines[i].setSize({1000, 20});
            lines[i].setFillColor(sf::Color(115, 115, 115));
            lines[i].setPosition({0, (float)(500 - 20) * i});
            window.draw(lines[i]);
        }

    }
}

bool AABB(sf::RectangleShape &a, sf::RectangleShape &b){
    if((a.getPosition().x < b.getPosition().x + b.getSize().x) &&
       (a.getPosition().x + a.getSize().x > b.getPosition().x) &&
       (a.getPosition().y < b.getPosition().y + b.getSize().y) &&
       (a.getPosition().y + a.getSize().y > b.getPosition().y)) return true;
        return false;
}


bool menu(sf::RenderWindow &menu) {
    sf::Event event;

    while (menu.isOpen()) {
        sf::Font font;
        font.loadFromFile(".\\assets\\fonts\\origa___.ttf");

        sf::Text textWelcome("Welcome to Pong!", font);
        sf::Text textChoice("Press left click to continue!", font);

        textWelcome.setCharacterSize(70);
        textWelcome.setStyle(sf::Text::Bold);
        textWelcome.setFillColor(sf::Color::White);

        textChoice.setCharacterSize(30);
        textChoice.setStyle(sf::Text::Bold);
        textChoice.setFillColor(sf::Color::White);


        sf::FloatRect textRect = textWelcome.getLocalBounds();
        textWelcome.setOrigin(textRect.width / 2, 0);
        textWelcome.setPosition(WINDOW_MAX_X / 2.0, WINDOW_MAX_Y / 3.0);

        textRect = textChoice.getLocalBounds();
        textChoice.setOrigin(textRect.width / 2, 0);
        textChoice.setPosition(WINDOW_MAX_X / 2.0, WINDOW_MAX_Y / 2.0);

        while (menu.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                menu.close();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) return false;
        }
        menu.clear(sf::Color(0, 0, 0));
        menu.draw(textWelcome);
        menu.draw(textChoice);
        menu.display();
    }
    return false;
}
