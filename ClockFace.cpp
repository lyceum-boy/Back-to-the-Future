//
// Created by anoso on 22.06.2024.
//

#include <cmath>  // Тригонометрия для положения стрелок и делений.

#include "ClockFace.h"  // Класс циферблата стрелочных часов.

using namespace sf;  // Пространство имён библиотеки SFML.

ClockFace::ClockFace() {
    // Установка параметров циферблата часов.
    clockFace.setRadius(100);
    clockFace.setFillColor(Color::White);
    clockFace.setOutlineThickness(5);
    clockFace.setOutlineColor(Color::Black);
    clockFace.setOrigin(clockFace.getRadius(), clockFace.getRadius());
    clockFace.setScale(0.3f, 0.3f);
    clockFace.setPosition(537, 130);

    // Установка параметров часовой стрелки.
    hourHand.setSize(Vector2f(50, 10));
    hourHand.setFillColor(Color::Black);
    hourHand.setOrigin(hourHand.getSize().x, hourHand.getSize().y / 2);
    hourHand.setScale(0.3f, 0.3f);
    hourHand.setPosition(537, 130);

    // Установка параметров секундной стрелки.
    secondHand.setSize(Vector2f(80, 15));
    secondHand.setFillColor(Color::Red);
    secondHand.setOrigin(secondHand.getSize().x, secondHand.getSize().y / 2);
    secondHand.setScale(0.3f, 0.3f);
    secondHand.setPosition(537, 130);

    // Инициализация делений времени на циферблате.
    initializeTimeDivisions();
}

// Метод инициализации делений времени на циферблате.
void ClockFace::initializeTimeDivisions() {
    for (int i = 0; i < 12; ++i) {
        RectangleShape division(Vector2f(10, 10));  // Длина и толщина деления.
        division.setFillColor(Color::Black);
        division.setOrigin(division.getSize().x / 2, division.getSize().y / 2);
        // Угол поворота (360 градусов / 12 делений = 30 градусов).
        float angle = 30.0f * static_cast<float>(i);
        division.setRotation(angle);
        division.setPosition(537, 130);
        division.move(static_cast<float>(25 * std::cos(angle * M_PI / 180)),
                      static_cast<float>(25 * std::sin(angle * M_PI / 180)));
        division.setScale(0.3f, 0.3f);
        timeDivisions.push_back(division);
    }
}

// Метод обновления положения стрелок.
void ClockFace::update(float remainingTime) {
    updateHands(remainingTime);
}

// Метод отрисовки стрелочных часов.
void ClockFace::draw(RenderWindow &window) {
    window.draw(clockFace);
    for (const auto &division: timeDivisions) {
        window.draw(division);
    }
    window.draw(hourHand);
    window.draw(minuteHand);
    window.draw(secondHand);
}

// Метод обновления положения стрелок.
void ClockFace::updateHands(float remainingTime) {
    // Вычисление углов для стрелок.
    float totalSeconds = remainingTime;
    float seconds = totalSeconds;
    float minutes = totalSeconds / 60;
    float hours = totalSeconds / 3600;

    float secondAngle = 360 * (seconds / 60);
    float minuteAngle = 360 * (minutes / 60);
    float hourAngle = 360 * (hours / 12);

    secondHand.setRotation(90 - secondAngle);
    minuteHand.setRotation(90 - minuteAngle);
    hourHand.setRotation(90 - hourAngle);
}
