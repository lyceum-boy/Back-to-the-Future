//
// Created by anoso on 22.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_VICTORYSCREEN_H
#define ITIP_CPP_PR_5_HDL_VICTORYSCREEN_H

// Используется для конвертации строки в UTF-8 для отрисовки кириллических символов.
#include <codecvt>

// Модуль для работы с графикой в библиотеке SFML.
#include <SFML/Graphics.hpp>

#include "EndScreen.h"   // Абстрактный базовый класс экрана окончания игры.
#include "MainWindow.h"  // Класс главного окна программы.


// Класс-наследник EndScreen, реализующий экран победы.
class VictoryScreen : public EndScreen {
private:
    RectangleShape menuButton;  // Кнопка возврата в меню.

    Text victoryText;  // Текст победы.
    Text timeText;     // Счёт - затраченное время.

    // Метод отрисовки экрана окончания игры.
    void draw(MainWindow &window, float totalTime) override;

public:
    VictoryScreen();

    // Метод отображения экрана и обработки ожидания возврата в меню.
    void PollEvents(MainWindow &window, float totalPLayerTime) override;
};


#endif //ITIP_CPP_PR_5_HDL_VICTORYSCREEN_H
