//
// Created by anoso on 24.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_FIREANIMATION_H
#define ITIP_CPP_PR_5_HDL_FIREANIMATION_H

#include <SFML/Graphics.hpp>


class FireAnimation {
public:
    FireAnimation(const sf::Texture& texture, const sf::Vector2f& position)
            : texture(texture), currentFrame(0), frameSize(0), frameCount(64), rows(8), columns(8) {

        frameSize = texture.getSize().x / columns; // Размер одного кадра
        sprite.setTexture(texture);
        sprite.setScale(0.65, 0.65);
        sprite.setPosition(position);
        sprite.setTextureRect(sf::IntRect(0, 0, frameSize, frameSize));
    }

    void update() {
        currentFrame++;
        if (currentFrame >= frameCount) {
            currentFrame = 0;
        }

        int row = currentFrame / columns;
        int col = currentFrame % columns;

        sprite.setTextureRect(sf::IntRect(col * frameSize, row * frameSize, frameSize, frameSize));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    const sf::Texture& texture;
    int currentFrame;
    int frameSize;
    int frameCount;
    int rows;
    int columns;
public:
    sf::Sprite sprite;
};


#endif //ITIP_CPP_PR_5_HDL_FIREANIMATION_H
