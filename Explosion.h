//
// Created by anoso on 22.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_EXPLOSION_H
#define ITIP_CPP_PR_5_HDL_EXPLOSION_H

#include <vector>

#include <SFML/Graphics.hpp>


class Explosion {
public:
    Explosion(sf::Texture &texture, sf::Vector2f position);
    void update();
    void draw(sf::RenderWindow &window);
    bool isFinished() const;

private:
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;
    int currentFrame;
    float frameDuration;
    float elapsedTime;
    bool finished;
};


#endif //ITIP_CPP_PR_5_HDL_EXPLOSION_H
