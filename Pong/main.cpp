#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>
#include <cmath>
#include <string>

bool AABB(sf::RectangleShape &a, sf::RectangleShape &b);
void drawField(sf::RenderWindow &window);
void reset(sf::RectangleShape &leftPlayer, sf::RectangleShape &ball, sf::RectangleShape &rightPlayer);
void rgb(sf::RectangleShape &obj, float i);
void setTextOriginAndPosition(sf::Text &text, float startPosition = 3.0, float offset = 0.0);
void setTextOriginAndPosition(sf::Text &text, float startPosition, float offset, float offSetX);

const int WINDOW_MAX_X = 1500;
const int WINDOW_MAX_Y = 820;

bool menu(sf::RenderWindow &menu, sf::Font &font);

int main(){
    sf::RenderWindow window(sf::VideoMode(WINDOW_MAX_X, WINDOW_MAX_Y), "Pong!", sf::Style::Titlebar | sf::Style::Close);
    sf::RectangleShape ball({20, 20});
    sf::RectangleShape leftPlayer({20, 100});
    sf::RectangleShape rightPlayer({20, 100});

    sf::Font font;
    font.loadFromFile(".\\assets\\fonts\\origa___.ttf");

    while(menu(window, font));

    leftPlayer.setPosition({20, (WINDOW_MAX_Y - 100) /2});
    leftPlayer.setFillColor(sf::Color::White);

    rightPlayer.setPosition({WINDOW_MAX_X - 40, (WINDOW_MAX_Y - 100) / 2});
    rightPlayer.setFillColor(sf::Color::White);

    ball.setPosition({(WINDOW_MAX_X - 20) / 2, (WINDOW_MAX_Y - 100) / 2});
    ball.setFillColor(sf::Color::White);

    sf::Clock current;
    float deltaTime;
    float speed = 200;
    float ballSpeed = 200;
    float delay = 0;
    float index = 0;
    int gameState = 0; //0 Pause //1 Run //2 Game Over only if one reaches the score 10
    sf::Text scoreLeft("0 ", font), scoreRight(" 0", font);
    std::string scoreL = "0  ", scoreR = "  0";
    sf::Text gameOver("Game Over!", font), gameOver2("Press Escape to exit.", font), pause("The game is currently paused 'ESC'", font);
    sf::Vector2f ballVec(1, 0);

    //setting all the text up ready for drawing
    scoreLeft.setCharacterSize(45);
    scoreRight.setCharacterSize(45);
    pause.setCharacterSize(50);

    scoreLeft.setStyle(sf::Text::Bold);
    scoreRight.setStyle(sf::Text::Bold);
    pause.setStyle(sf::Text::Bold);

    scoreLeft.setFillColor(sf::Color::White);
    scoreRight.setFillColor(sf::Color::White);
    pause.setFillColor(sf::Color::White);

    sf::FloatRect textRect;

    //the pause text is always the same, so it is defined before the actual game loop
    setTextOriginAndPosition(pause);
    /*textRect = pause.getLocalBounds();
    pause.setOrigin(textRect.width / 2, 0);
    pause.setPosition(WINDOW_MAX_X / 2.0, WINDOW_MAX_Y / 3.0);*/

    while (window.isOpen()) {
        deltaTime = current.restart().asSeconds();
        sf::Event event;

        scoreLeft.setString(scoreL);
        scoreRight.setString(scoreR);

        setTextOriginAndPosition(scoreLeft, 32.8, 0.0, 40);
        setTextOriginAndPosition(scoreRight, 32.8, 0.0, -40);

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

        switch(gameState) {
        case 0:
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && delay <= 0) {
                gameState = 1;
                delay = 0.1;

            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
                window.close();
            }
            break;
        case 2:
            window.clear(sf::Color(0, 0, 0));
            gameOver.setCharacterSize(60);
            gameOver.setStyle(sf::Text::Bold);
            gameOver.setFillColor(sf::Color::White);

            gameOver2.setCharacterSize(40);
            gameOver2.setStyle(sf::Text::Bold);
            gameOver2.setFillColor(sf::Color::White);

            setTextOriginAndPosition(gameOver, 2.5);
            setTextOriginAndPosition(gameOver2, 2.5, 0.5);

            window.draw(gameOver);
            window.draw(gameOver2);
            window.display();
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
                }else if(ball.getPosition().x < 40 || ball.getPosition().x > WINDOW_MAX_X - 40){
                    if (!(ball.getPosition().x > WINDOW_MAX_X - 40)) {
                        if (scoreR[1] == '9') {
                            gameState = 2;
                            scoreR[2] = 48;
                            scoreR[1] = 49;
                        }else {
                            scoreR[2] += 1;
                        }
                    }else {
                        if (scoreL[0] == '9') {
                            gameState = 2;
                            scoreL[0] = 49;
                            scoreL[1] = 48;
                        }else {
                            scoreL[0] += 1;
                        }
                    }
                    reset(leftPlayer, ball, rightPlayer);
                    ballVec.x *= -1;
                    ballVec.y = 0;
                }
                ball.move((ballVec.x * ballSpeed) * deltaTime, (ballVec.y * ballSpeed) * deltaTime);

                std::cout << "First Player[ Y: " << leftPlayer.getPosition().y << " ] "
                          << "Second Player[ Y: " << rightPlayer.getPosition().y << " ]"
                          << "BallVec: [ X: " << ballVec.x << " Y: " << ballVec.y << " Speed: " << ballSpeed <<std::endl;




            break;
            }
        if (gameState != 2) {
            window.clear();
            drawField(window);
            window.draw(ball);
            window.draw(leftPlayer);
            window.draw(rightPlayer);
            window.draw(scoreLeft);
            window.draw(scoreRight);
            if (gameState == 0) {
                window.draw(pause);
            }
            window.display();
        }else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                break;
            }
        }
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
    sf::RectangleShape shapes[21];
    sf::RectangleShape lines[2];

    for(int i = 0; i < 21; i++){
        shapes[i].setFillColor(sf::Color(115, 115, 115));
        shapes[i].setSize({20, 20});
        shapes[i].setPosition({(1500 - 20) / 2, y});
        y += 40;
        window.draw(shapes[i]);
        if(i < 2){
            lines[i].setSize({1500, 20});
            lines[i].setFillColor(sf::Color(115, 115, 115));
            lines[i].setPosition({0, (float)(820 - 20) * i});
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

bool menu(sf::RenderWindow &menu, sf::Font &font) {
    sf::Event event;
    sf::Text textWelcome("Welcome to Pong!", font);
    sf::Text textChoice("Press left click to continue!", font);
    sf::Text textLeaderboard("Press 'L' to get to Leaderboard", font);
    int menuState = 0;

    sf::RectangleShape leftPlayer({20, 100});
    sf::RectangleShape rightPlayer({20, 100});

    leftPlayer.setPosition({20, (WINDOW_MAX_Y - 100) /2});
    leftPlayer.setFillColor(sf::Color::White);

    rightPlayer.setPosition({WINDOW_MAX_X - 40, (WINDOW_MAX_Y - 100) / 2});
    rightPlayer.setFillColor(sf::Color::White);


    //setting up all the text
    textWelcome.setCharacterSize(70);
    textWelcome.setStyle(sf::Text::Bold);
    textWelcome.setFillColor(sf::Color::White);

    textChoice.setCharacterSize(30);
    textChoice.setStyle(sf::Text::Bold);
    textChoice.setFillColor(sf::Color::White);

    textLeaderboard.setCharacterSize(30);
    textLeaderboard.setStyle(sf::Text::Bold);
    textLeaderboard.setFillColor(sf::Color::White);

    //calling the function for setting the text position (1. parameter is text, 2. startPosition, 3. offset
    setTextOriginAndPosition(textWelcome, 3.0);
    setTextOriginAndPosition(textChoice, 3.0, 0.7);
    setTextOriginAndPosition(textLeaderboard, 3.0, 0.9);

    while (menu.isOpen()) {
        while (menu.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                menu.close();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) return false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                menuState = 1;
            }
        }
        menu.clear(sf::Color(0, 0, 0));
        if (!menuState) {
            drawField(menu);
            menu.draw(leftPlayer);
            menu.draw(rightPlayer);
            menu.draw(textWelcome);
            menu.draw(textChoice);
            menu.draw(textLeaderboard);
        }else {

        }
        menu.display();
    }
    return false;
}

void setTextOriginAndPosition(sf::Text &text, float startPosition, float offset) {
    sf::FloatRect textRect;

    textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2, 0);
    text.setPosition(WINDOW_MAX_X / 2.0, WINDOW_MAX_Y / (startPosition - offset));
}

void setTextOriginAndPosition(sf::Text &text, float startPosition, float offset, float offSetX) {
    sf::FloatRect textRect;

    textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2, 0);
    text.setPosition(WINDOW_MAX_X / 2.0 - offSetX, WINDOW_MAX_Y / (startPosition - offset));
}
