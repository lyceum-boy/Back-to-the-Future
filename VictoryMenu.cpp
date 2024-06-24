#include <iostream>
#include "VictoryMenu.h"

#define HEADER_FONT_PATH "static/fonts/backtothefuture2002_regular.ttf"
#define TEXT_FONT_PATH "static/fonts/Industry-Bold_RUS.ttf"

VictoryMenu::VictoryMenu() {
    headerFont.loadFromFile(HEADER_FONT_PATH);
    textFont.loadFromFile(TEXT_FONT_PATH);

    backButton.setSize(sf::Vector2f(200, 50));
    backButton.setOutlineThickness(2);
    backButton.setOutlineColor(sf::Color::White);
    backButton.setPosition(412, 400); // Центрируем кнопку по горизонтали

    victoryText.setFont(headerFont);
    victoryText.setString(cv.from_bytes("ПОБЕДА!"));
    victoryText.setCharacterSize(50);
    victoryText.setFillColor(sf::Color::Green);
    victoryText.setPosition(362, 200); // Центрируем текст по горизонтали

    timeText.setFont(textFont);
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(362, 300); // Центрируем текст по горизонтали
}

void VictoryMenu::draw(MainWindow &window, int totalTime) {
    // Отрисовка темного полупрозрачного прямоугольника
    RectangleShape darkOverlay(Vector2f(window.getSize().x - 40, window.getSize().y - 40));
    darkOverlay.setFillColor(Color(0, 0, 0, 180)); // Черный с полупрозрачностью 180
    darkOverlay.setPosition(20, 20); // Отступ 20 пикселей от каждого края
    window.draw(darkOverlay);

    Text backLabel(cv.from_bytes("Назад"), textFont, 30);
    backLabel.setFillColor(Color::White);

    Vector2i mousePos = Mouse::getPosition(window);
    std::cout << mousePos.x << " " << mousePos.y << std::endl;
    if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        backButton.setFillColor(Color(0, 255, 0, 150)); // Полупрозрачный ярко-зеленый
        backButton.setSize(Vector2f(220, 55)); // Увеличить размер
        backButton.setPosition(412, 400);
        backLabel.setPosition(
                backButton.getPosition().x + (backButton.getSize().x - backLabel.getLocalBounds().width) / 2 - 10,
                backButton.getPosition().y + (backButton.getSize().y - backLabel.getLocalBounds().height) / 2 - 10
        );
        backLabel.setScale(1.2, 1.2);
    } else {
        backButton.setFillColor(Color(125, 125, 125, 150)); // Полупрозрачный черный
        backButton.setSize(Vector2f(200, 50)); // Обычный размер
        backButton.setPosition(412, 400);

        backLabel.setPosition(
                backButton.getPosition().x + (backButton.getSize().x - backLabel.getLocalBounds().width) / 2,
                backButton.getPosition().y + (backButton.getSize().y - backLabel.getLocalBounds().height) / 2 - 5
        );
        backLabel.setScale(1.0, 1.0);
    }

    window.draw(darkOverlay);
    window.draw(backButton);
    window.draw(backLabel);
    window.draw(victoryText);

    timeText.setString(cv.from_bytes("Вы успели за: ") + std::to_string(totalTime) + cv.from_bytes(" с"));
    window.draw(timeText);
}

void VictoryMenu::PollEvents(MainWindow &window) {
// Wait for user input to return to main menu
    while (window.isOpen()) {
        draw(window, 228);
        window.display();
        window.clear();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                          static_cast<float>( mousePos.y))) {
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
