//
// Created by anoso on 24.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_FIRETRACE_H
#define ITIP_CPP_PR_5_HDL_FIRETRACE_H

// Модуль для работы с графикой в библиотеке SFML.
#include <SFML/Graphics.hpp>

#include "Animation.h"  // Абстрактный базовый класс анимации.

using namespace sf;  // Пространство имён библиотеки SFML.


// Класс-наследник Animation, реализующий анимацию огненного следа от колёс.
class FireTrace : public Animation {
public:
    FireTrace(const Texture &texture, const Vector2f &position);

    // Метод обновления кадров анимации.
    void update() override;

    // Метод отрисовки кадра анимации.
    void draw(RenderWindow &window) override;

    // Метод проверки окончания анимации.
    bool isFinished() const override;

public:
    Sprite sprite;  // Спрайт.

private:
    int currentFrame;        // Текущий кадр анимации.
    int frameSize;           // Размер кадра.
    int frameCount;          // Количество кадров.
    int framesPerSide;       // Количество кадров по одной стороне.
};


#endif //ITIP_CPP_PR_5_HDL_FIRETRACE_H
