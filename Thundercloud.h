//
// Created by anoso on 22.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_THUNDERCLOUD_H
#define ITIP_CPP_PR_5_HDL_THUNDERCLOUD_H

#include <SFML/Graphics.hpp>

using namespace sf;


class Thundercloud {
public:
    Thundercloud(sf::Texture& texture, sf::Vector2f position, float speed, float scale);

    void update(sf::RenderWindow& window, float gameSpeed);
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
    float speed;
};


#endif //ITIP_CPP_PR_5_HDL_THUNDERCLOUD_H
