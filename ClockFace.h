//
// Created by anoso on 22.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_CLOCKFACE_H
#define ITIP_CPP_PR_5_HDL_CLOCKFACE_H

// Модуль для работы с графикой в библиотеке SFML.
#include <SFML/Graphics.hpp>

using namespace sf;  // Пространство имён библиотеки SFML.


// Класс циферблата стрелочных часов.
class ClockFace {
private:
    CircleShape clockFace;      // Циферблат часов.
    RectangleShape hourHand;    // Часовая стрелка.
    RectangleShape minuteHand;  // Минутная стрелка.
    RectangleShape secondHand;  // Секундная стрелка.

    std::vector<RectangleShape> timeDivisions;  // Вектор делений времени.

    // Метод обновления положения стрелок.
    void updateHands(float remainingTime);

    // Метод инициализации делений времени на циферблате.
    void initializeTimeDivisions();

public:
    ClockFace();

    // Метод обновления положения стрелок.
    void update(float remainingTime);

    // Метод отрисовки стрелочных часов.
    void draw(RenderWindow &window);
};


#endif //ITIP_CPP_PR_5_HDL_CLOCKFACE_H
