//
// Created by anoso on 22.06.2024.
//

#include "Lightning.h"

#include "MainWindow.h"

Lightning::Lightning(sf::Texture &texture, sf::Vector2f position)
        : currentFrame(0), frameDuration(0.1f), elapsedTime(0), finished(false) {
    int frameWidth = texture.getSize().x / 2; // 2 columns
    int frameHeight = texture.getSize().y / 2; // 2 rows

    for (int i = 0; i < 4; ++i) {
        frames.emplace_back(i % 2 * frameWidth, i / 2 * frameHeight, frameWidth, frameHeight);
    }

    sprite.setTexture(texture);
    sprite.setScale(0.35, 0.25);
    sprite.setTextureRect(frames[0]);
    sprite.setPosition(position.x - sprite.getScale().x * frameWidth / 2, position.y);
}

void Lightning::update() {
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

void Lightning::draw(sf::RenderWindow &window) {
    if (!finished) {
        window.draw(sprite);
    }
}

bool Lightning::isFinished() const {
    return finished;
}
