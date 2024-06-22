//
// Created by anoso on 22.06.2024.
//

#include "Explosion.h"

#include "MainWindow.h"

Explosion::Explosion(sf::Texture &texture, sf::Vector2f position)
        : currentFrame(0), frameDuration(0.1f), elapsedTime(0), finished(false) {
    for (int i = 0; i < 8; ++i) {
        frames.emplace_back(i * (texture.getSize().x / 8), 0, texture.getSize().x / 8, texture.getSize().y);
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(frames[0]);

    // Смещение позиции взрыва, чтобы центрировать его относительно позиции бонуса
    sprite.setPosition(position.x - (texture.getSize().x / 8) / 2, position.y - texture.getSize().y / 3);
}


void Explosion::update() {
    elapsedTime += frameDuration;
    if (elapsedTime >= frameDuration) {
        elapsedTime = 0;
        ++currentFrame;
        if (currentFrame >= frames.size()) {
            finished = true;
        } else {
            sprite.setTextureRect(frames[currentFrame]);
        }
    }
}

void Explosion::draw(sf::RenderWindow &window) {
    if (!finished) {
        window.draw(sprite);
    }
}

bool Explosion::isFinished() const {
    return finished;
}
