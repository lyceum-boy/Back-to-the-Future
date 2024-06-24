//
// Created by anoso on 22.06.2024.
//

#include "ClockFace.h"

#include <cmath>

ClockFace::ClockFace(sf::Vector2u windowSize) {
    // Set clock face
    clockFace.setRadius(100);
    clockFace.setFillColor(sf::Color::White);
    clockFace.setOutlineThickness(5);
    clockFace.setOutlineColor(sf::Color::Black);
    // center = sf::Vector2f(windowSize.x / 2, windowSize.y / 2);
    clockFace.setOrigin(clockFace.getRadius(), clockFace.getRadius());
    clockFace.setScale(0.3f, 0.3f);
    clockFace.setPosition(537, 130);

    // Set hour hand
    hourHand.setSize(sf::Vector2f(50, 10));
    hourHand.setFillColor(sf::Color::Black);
    hourHand.setOrigin(hourHand.getSize().x, hourHand.getSize().y / 2);
    hourHand.setScale(0.3f, 0.3f);
    hourHand.setPosition(537, 130);

    // Set second hand
    secondHand.setSize(sf::Vector2f(80, 15));
    secondHand.setFillColor(sf::Color::Red);
    secondHand.setOrigin(secondHand.getSize().x, secondHand.getSize().y / 2);
    secondHand.setScale(0.3f, 0.3f);
    secondHand.setPosition(537, 130);

    // Initialize time divisions
    initializeTimeDivisions();
}

void ClockFace::initializeTimeDivisions() {
    for (int i = 0; i < 12; ++i) {
        sf::RectangleShape division(sf::Vector2f(10, 10)); // Длина и толщина деления
        division.setFillColor(sf::Color::Black);
        division.setOrigin(division.getSize().x / 2, division.getSize().y / 2);
        float angle = 30 * i; // Угол поворота (360 градусов / 12 делений = 30 градусов)
        division.setRotation(angle);
        division.setPosition(537, 130);
        division.move(25 * std::cos(angle * M_PI / 180), 25 * std::sin(angle * M_PI / 180));
        division.setScale(0.3f, 0.3f);
        timeDivisions.push_back(division);
    }
}

void ClockFace::update(float remainingTime) {
    updateHands(remainingTime);
}

void ClockFace::draw(sf::RenderWindow& window) {
    window.draw(clockFace);
    for (const auto& division : timeDivisions) {
        window.draw(division);
    }
    window.draw(hourHand);
    window.draw(minuteHand);
    window.draw(secondHand);
}

void ClockFace::updateHands(float remainingTime) {
    // Calculate angles for hands
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
