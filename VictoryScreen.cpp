//
// Created by anoso on 22.06.2024.
//

#include "VictoryScreen.h"
#include "MainWindow.h"

#define HEADER_FONT_PATH "static/fonts/backtothefuture2002_regular.ttf"
#define TEXT_FONT_PATH "static/fonts/Industry-Bold_RUS.ttf"

VictoryScreen::VictoryScreen() {
    headerFont.loadFromFile(HEADER_FONT_PATH);
    textFont.loadFromFile(TEXT_FONT_PATH);

    menuButton.setSize(sf::Vector2f(200, 50));
    menuButton.setOutlineThickness(2);
    menuButton.setOutlineColor(sf::Color::White);

    victoryText.setFont(headerFont);
    victoryText.setString(cv.from_bytes("ПОБЕДА!"));
    victoryText.setCharacterSize(50);
    victoryText.setFillColor(sf::Color::Green);
    victoryText.setPosition(375, 275); // Центрируем текст по горизонтали

    timeText.setFont(textFont);
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(390, 375); // Центрируем текст по горизонтали
}

void VictoryScreen::draw(MainWindow &window, float totalTime) {
    Text menuLabel(cv.from_bytes("В меню"), textFont, 30);
    menuLabel.setFillColor(Color::White);

    Vector2i mousePos = Mouse::getPosition(window);
    if (menuButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        menuButton.setFillColor(Color(0, 255, 0, 150)); // Полупрозрачный ярко-зеленый
        menuButton.setSize(Vector2f(220, 55)); // Увеличить размер
        menuButton.setPosition(static_cast<float>(window.getSize().x / 2.0 - menuButton.getSize().x / 2),
                               static_cast<float>(window.getSize().y - 102.5));
        menuLabel.setPosition(
                menuButton.getPosition().x + (menuButton.getSize().x - menuLabel.getLocalBounds().width) / 2 - 10,
                menuButton.getPosition().y + (menuButton.getSize().y - menuLabel.getLocalBounds().height) / 2 - 12.5f
        );
        menuLabel.setScale(1.2, 1.2);
    } else {
        menuButton.setFillColor(Color(125, 125, 125, 150)); // Полупрозрачный черный
        menuButton.setSize(Vector2f(200, 50)); // Обычный размер
        menuButton.setPosition(static_cast<float>(window.getSize().x / 2.0 - menuButton.getSize().x / 2),
                               static_cast<float>(window.getSize().y - 100));
        menuLabel.setPosition(
                menuButton.getPosition().x + (menuButton.getSize().x - menuLabel.getLocalBounds().width) / 2,
                menuButton.getPosition().y + (menuButton.getSize().y - menuLabel.getLocalBounds().height) / 2 - 7.5f
        );
        menuLabel.setScale(1.0, 1.0);
    }

    timeText.setString(
            cv.from_bytes("Вы успели за: ")
            + std::to_string(static_cast<int>(totalTime))
            + cv.from_bytes(" s")
    );

    window.draw(victoryText);
    window.draw(timeText);
    window.draw(menuButton);
    window.draw(menuLabel);
}

void VictoryScreen::PollEvents(MainWindow &window, float totalPLayerTime) {
    // Обработка цикла ожидания выхода в Главное меню.
    while (window.isOpen()) {
        draw(window, totalPLayerTime);
        window.display();
        window.clear();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (menuButton.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                          static_cast<float>(mousePos.y))) {
                    return;
                }
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::Escape ||
                    event.key.scancode == sf::Keyboard::Scan::Enter) {
                    return;
                }
            }
        }
    }
}
