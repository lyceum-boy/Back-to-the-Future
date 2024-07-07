//
// Created by anoso on 24.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_ANIMATION_H
#define ITIP_CPP_PR_5_HDL_ANIMATION_H

#include <vector>

// Модуль для работы с графикой в библиотеке SFML.
#include <SFML/Graphics.hpp>

using namespace sf;  // Пространство имён библиотеки SFML.


// Абстрактный базовый класс анимации.
class Animation {
public:
    Animation() = default;

    // Метод обновления кадров анимации.
    virtual void update() = 0;

    // Метод отрисовки кадра анимации.
    virtual void draw(RenderWindow &window) = 0;

    // Метод проверки окончания анимации.
    [[nodiscard]] virtual bool isFinished() const = 0;
};


#endif //ITIP_CPP_PR_5_HDL_ANIMATION_H
