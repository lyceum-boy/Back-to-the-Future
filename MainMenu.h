//
// Created by anoso on 21.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_MAINMENU_H
#define ITIP_CPP_PR_5_HDL_MAINMENU_H

// Используется для конвертации строки в UTF-8 для отрисовки кириллических символов.
#include <codecvt>

#include "MainWindow.h"  // Класс главного окна программы.

using namespace sf;  // Пространство имён библиотеки SFML.


// Класс Главного меню.
class MainMenu {
public:
    std::vector<std::string> songs;  // Вектор путей к фоновой музыке.

    Sprite background;  // Фоновое изображение.

    Music curMusic;   // Текущая фоновая музыка.
    Font headerFont;  // Шрифт заголовков.
    Font textFont;    // Шрифт основного текста.
    Clock mainTimer;  // Таймер отрисовки кадров.

    RectangleShape backButton;  // Кнопка "Назад".

    // Конвертер строки для отрисовки кириллических символов в UTF-8.
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;

public:
    MainMenu();

    // Метод вывода Главного меню.
    void displayMainMenu(MainWindow &window, std::vector<RectangleShape> &buttons, std::vector<Text> &buttonLabels);

    // Метод вывода подменю "Как играть".
    void displayHowToPlay(MainWindow &window);

    // Метод вывода подменю "Об игре".
    void displayAbout(MainWindow &window);

    // Метод отрисовки кнопки "Назад".
    void drawBackButton(MainWindow &window);
};


#endif //ITIP_CPP_PR_5_HDL_MAINMENU_H
