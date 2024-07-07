//
// Created by anoso on 22.06.2024.
//

#include "Thundercloud.h"  // Класс грозовой тучи.

using namespace sf;  // Пространство имён библиотеки SFML.

Thundercloud::Thundercloud(Texture &texture, Vector2f position, float speed, float scale)
        : speed(speed) {
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    sprite.setPosition(position);
}

// Метод обновления положения грозовой тучи.
void Thundercloud::update(RenderWindow &window, float gameSpeed) {
    sprite.move(-5 * gameSpeed / 11 * speed, 0);
    if (sprite.getPosition().x + sprite.getGlobalBounds().width < 0) {
        sprite.setPosition(static_cast<float>(window.getSize().x) + sprite.getGlobalBounds().width * 2,
                           sprite.getPosition().y);
    }
}

// Метод отрисовки грозовой тучи на экране.
void Thundercloud::draw(RenderWindow &window) {
    window.draw(sprite);
}
