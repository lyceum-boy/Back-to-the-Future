//
// Created by anoso on 22.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_CLOCKFACE_H
#define ITIP_CPP_PR_5_HDL_CLOCKFACE_H

#include <SFML/Graphics.hpp>


class ClockFace {
public:
    ClockFace(sf::Vector2u windowSize);

    void update(float remainingTime);
    void draw(sf::RenderWindow& window);

private:
    sf::CircleShape clockFace;
    sf::RectangleShape hourHand;
    sf::RectangleShape minuteHand;
    sf::RectangleShape secondHand;

    std::vector<sf::RectangleShape> timeDivisions; // Массив делений времени

    void updateHands(float remainingTime);
    void initializeTimeDivisions(); // Инициализация делений времени
};


#endif //ITIP_CPP_PR_5_HDL_CLOCKFACE_H
