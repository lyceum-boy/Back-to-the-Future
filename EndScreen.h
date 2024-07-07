//
// Created by anoso on 24.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_ENDSCREEN_H
#define ITIP_CPP_PR_5_HDL_ENDSCREEN_H

// Используется для конвертации строки в UTF-8 для отрисовки кириллических символов.
#include <codecvt>

// Модуль для работы с графикой в библиотеке SFML.
#include <SFML/Graphics.hpp>

#include "MainWindow.h"  // Класс главного окна программы.


// Абстрактный базовый класс экрана окончания игры.
class EndScreen {
private:
    // Метод отрисовки экрана окончания игры.
    virtual void draw(MainWindow &window, float score) = 0;

public:
    Font headerFont;  // Шрифт заголовка.
    Font textFont;    // Шрифт основного текста.

    // Конвертер строки для отрисовки кириллических символов в UTF-8.
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;

public:
    EndScreen() = default;

    // Метод отображения экрана и обработки ожидания возврата в меню.
    virtual void PollEvents(MainWindow &window, float score) = 0;
};


#endif //ITIP_CPP_PR_5_HDL_ENDSCREEN_H
