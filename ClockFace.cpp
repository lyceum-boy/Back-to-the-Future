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
    center = sf::Vector2f(windowSize.x / 2, windowSize.y / 2);
    clockFace.setOrigin(clockFace.getRadius(), clockFace.getRadius());
    clockFace.setPosition(center);

    // Set hour hand
    hourHand.setSize(sf::Vector2f(100, 8));
    hourHand.setFillColor(sf::Color::Black);
    hourHand.setOrigin(hourHand.getSize().x - 20, hourHand.getSize().y / 2);
    hourHand.setPosition(center);

    // Set minute hand
    minuteHand.setSize(sf::Vector2f(150, 6));
    minuteHand.setFillColor(sf::Color::Black);
    minuteHand.setOrigin(minuteHand.getSize().x - 20, minuteHand.getSize().y / 2);
    minuteHand.setPosition(center);

    // Set second hand
    secondHand.setSize(sf::Vector2f(180, 5));
    secondHand.setFillColor(sf::Color::Red);
    secondHand.setOrigin(secondHand.getSize().x - 20, secondHand.getSize().y / 2);
    secondHand.setPosition(center);
}

void ClockFace::update(float remainingTime) {
    updateHands(remainingTime);
}

void ClockFace::draw(sf::RenderWindow& window) {
    window.draw(clockFace);
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
