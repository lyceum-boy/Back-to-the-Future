//
// Created by anoso on 22.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_LIGHTNING_H
#define ITIP_CPP_PR_5_HDL_LIGHTNING_H

#include <vector>

// Модуль для работы с графикой в библиотеке SFML.
#include <SFML/Graphics.hpp>

#include "Animation.h"  // Абстрактный базовый класс анимации.

using namespace sf;  // Пространство имён библиотеки SFML.


// Класс-наследник Animation, реализующий анимацию молнии.
class Lightning : public Animation {
public:
    Lightning(Texture &texture, Vector2f position);

    // Метод обновления кадров анимации.
    void update() override;

    // Метод отрисовки кадра анимации.
    void draw(RenderWindow &window) override;

    // Метод проверки окончания анимации.
    bool isFinished() const override;

private:
    Sprite sprite;                // Спрайт.
    std::vector<IntRect> frames;  // Кадры анимации.
    int currentFrame;             // Текущий кадр анимации.
    float frameDuration;          // Продолжительность кадра анимации.
    float elapsedTime;            // Время с момента обновления кадра.
    bool finished;                // Флаг завершения анимации.
};


#endif //ITIP_CPP_PR_5_HDL_LIGHTNING_H
