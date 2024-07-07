//
// Created by anoso on 22.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_GAMEOVERSCREEN_H
#define ITIP_CPP_PR_5_HDL_GAMEOVERSCREEN_H

// Используется для конвертации строки в UTF-8 для отрисовки кириллических символов.
#include <codecvt>

// Модуль для работы с графикой в библиотеке SFML.
#include <SFML/Graphics.hpp>

#include "EndScreen.h"   // Абстрактный базовый класс экрана окончания игры.
#include "MainWindow.h"  // Класс главного окна программы.


// Класс-наследник EndScreen, реализующий экран поражения.
class GameOverScreen : public EndScreen {
private:
    RectangleShape menuButton;  // Кнопка возврата в меню.

    Text gameOverText;  // Текст поражения.
    Text speedText;     // Счёт - набранная скорость.

    // Метод отрисовки экрана окончания игры.
    void draw(MainWindow &window, float maxSpeed) override;

public:
    GameOverScreen();

    // Метод отображения экрана и обработки ожидания возврата в меню.
    void PollEvents(MainWindow &window, float maxPlayerSpeed) override;
};


#endif //ITIP_CPP_PR_5_HDL_GAMEOVERSCREEN_H
