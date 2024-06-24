//
// Created by anoso on 22.06.2024.
//

#include "Thundercloud.h"

Thundercloud::Thundercloud(sf::Texture& texture, sf::Vector2f position, float speed, float scale)
        : speed(speed)
{
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    sprite.setPosition(position);
}

void Thundercloud::update(sf::RenderWindow& window, float gameSpeed) {
    sprite.move(-5 * gameSpeed / 11 * speed, 0);
    if (sprite.getPosition().x + sprite.getGlobalBounds().width < 0) {
        sprite.setPosition(window.getSize().x + sprite.getGlobalBounds().width * 2, sprite.getPosition().y);
    }
}

void Thundercloud::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
