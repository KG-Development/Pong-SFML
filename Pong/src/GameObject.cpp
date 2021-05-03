#include "GameObject.h"

GameObject::GameObject()
{
    //ctor
}
GameObject::GameObject(sf::Vector2f size, sf::Vector2f position, sf::Color color){

    this->obj.setSize(size);
    this->obj.setPosition(position);
    this->obj.setFillColor(color);
}
GameObject::~GameObject()
{
    //dtor
}
sf::RectangleShape GameObject::getGameObject(){
    return this->obj;
}
void GameObject::setPosition(sf::Vector2f newPosition){
    this->obj.setPosition(newPosition);
}
void GameObject::setSize(sf::Vector2f newSize){
    this->obj.setSize(newSize);
}
void GameObject::setColor(sf::Color newColor){
    this->obj.setFillColor(newColor);
}
void GameObject::draw(sf::RenderWindow &window){
    window.draw(this->obj);
}
