/* Аносов Илья Борисович
 * Группа О737Б
 * Информационные технологии и программирование (ИТиП)
 * Практическая работа №5. Графика
 * Повышенный уровень сложности
 * Вариант 4
 * Задание 3 */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "MainWindow.h"
#include "DeLorean.h"

using namespace sf;

int main(int argc, char *argv[]) {
    srand(time(nullptr));

    MainWindow window(VideoMode(1024, 768), "Back to the Future");
    DeLorean deLorean;

    while (window.isOpen()) {
        window.clear(Color::White);
        deLorean.accelerate(window);
        window.close();
    }
    return 0;
}

#pragma clang diagnostic pop