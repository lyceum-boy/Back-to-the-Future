//
// Created by anoso on 16.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_LIGHTNINGANIMATION_H
#define ITIP_CPP_PR_5_HDL_LIGHTNINGANIMATION_H

#include <iostream>

#include <SFML/Graphics.hpp>


class LightningAnimation {
public:
    LightningAnimation();

    void load(const std::string &spriteSheetPath, int frameWidth, int frameHeight, float animationDuration);

    void start();

    void update(float deltaTime);

    void draw(sf::RenderWindow &window);

    bool isFinished() const;

private:
    sf::Texture texture;
    std::vector<sf::IntRect> frames;
    sf::Sprite sprite;
    float animationDuration;
    float currentTime;
    int currentFrame;
    bool finished;
};


#endif //ITIP_CPP_PR_5_HDL_LIGHTNINGANIMATION_H
