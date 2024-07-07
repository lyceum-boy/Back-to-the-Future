//
// Created by anoso on 22.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_THUNDERCLOUD_H
#define ITIP_CPP_PR_5_HDL_THUNDERCLOUD_H

// Модуль для работы с графикой в библиотеке SFML.
#include <SFML/Graphics.hpp>

using namespace sf;  // Пространство имён библиотеки SFML.


// Класс грозовой тучи.
class Thundercloud {
public:
    Thundercloud(Texture &texture, Vector2f position, float speed, float scale);

    // Метод обновления положения грозовой тучи.
    void update(RenderWindow &window, float gameSpeed);

    // Метод отрисовки грозовой тучи на экране.
    void draw(RenderWindow &window);

private:
    Sprite sprite;  // Спрайт грозовой тучи.
    float speed;    // Скорость движения тучи.
};


#endif //ITIP_CPP_PR_5_HDL_THUNDERCLOUD_H
