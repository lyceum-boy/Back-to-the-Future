#include "GameOverMenu.h"
#include "MainWindow.h"


#define HEADER_FONT_PATH "static/fonts/backtothefuture2002_regular.ttf"
#define TEXT_FONT_PATH "static/fonts/Industry-Bold_RUS.ttf"

GameOverMenu::GameOverMenu() {
    headerFont.loadFromFile(HEADER_FONT_PATH);
    textFont.loadFromFile(TEXT_FONT_PATH);

    backButton.setSize(sf::Vector2f(200, 50));
    backButton.setOutlineThickness(2);
    backButton.setOutlineColor(sf::Color::White);
    backButton.setPosition(412, 400); // Центрируем кнопку по горизонтали

    gameOverText.setFont(headerFont);
    gameOverText.setString(cv.from_bytes("ПОРАЖЕНИЕ!"));
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(362, 200); // Центрируем текст по горизонтали

    speedText.setFont(textFont);
    speedText.setCharacterSize(30);
    speedText.setFillColor(sf::Color::White);
    speedText.setPosition(362, 300); // Центрируем текст по горизонтали
}

void GameOverMenu::draw(MainWindow &window, float finalSpeed) {
    // Отрисовка темного полупрозрачного прямоугольника
    RectangleShape darkOverlay(Vector2f(window.getSize().x - 40, window.getSize().y - 40));
    darkOverlay.setFillColor(Color(0, 0, 0, 180)); // Черный с полупрозрачностью 180
    darkOverlay.setPosition(20, 20); // Отступ 20 пикселей от каждого края
    window.draw(darkOverlay);

    Text backLabel(cv.from_bytes("Назад"), textFont, 30);
    backLabel.setFillColor(Color::White);

    Vector2i mousePos = Mouse::getPosition(window);
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
    window.draw(gameOverText);

    speedText.setString(cv.from_bytes("Максимальная набранная скорость: ") + std::to_string(finalSpeed) + " mph");
    window.draw(speedText);
}

void GameOverMenu::PollEvents(MainWindow &window) {
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
