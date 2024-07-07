//
// Created by anoso on 22.06.2024.
//

#include "GameOverScreen.h"  // Класс окна поражения.
#include "MainWindow.h"      // Класс главного окна программы.

// Относительные пути к шрифтам.
#define HEADER_FONT_PATH "static/fonts/backtothefuture2002_regular.ttf"
#define TEXT_FONT_PATH "static/fonts/Industry-Bold_RUS.ttf"

GameOverScreen::GameOverScreen() {
    headerFont.loadFromFile(HEADER_FONT_PATH);
    textFont.loadFromFile(TEXT_FONT_PATH);

    menuButton.setSize(sf::Vector2f(200, 50));
    menuButton.setOutlineThickness(2);
    menuButton.setOutlineColor(sf::Color::White);

    gameOverText.setFont(headerFont);
    gameOverText.setString(cv.from_bytes("ПОРАЖЕНИЕ!"));
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(300, 275);

    speedText.setFont(textFont);
    speedText.setCharacterSize(30);
    speedText.setFillColor(sf::Color::White);
    speedText.setPosition(280, 375);
}

// Метод отрисовки экрана поражения.
void GameOverScreen::draw(MainWindow &window, float maxSpeed) {
    Text menuLabel(cv.from_bytes("В меню"), textFont, 30);
    menuLabel.setFillColor(Color::White);

    Vector2i mousePos = Mouse::getPosition(window);
    if (menuButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        menuButton.setFillColor(Color(0, 255, 0, 150));  // Полупрозрачный ярко-зеленый.
        menuButton.setSize(Vector2f(220, 55));  // Увеличить размер.
        menuButton.setPosition(static_cast<float>(window.getSize().x / 2.0 - menuButton.getSize().x / 2),
                               static_cast<float>(window.getSize().y - 102.5));
        menuLabel.setPosition(
                menuButton.getPosition().x + (menuButton.getSize().x - menuLabel.getLocalBounds().width) / 2 - 10,
                menuButton.getPosition().y + (menuButton.getSize().y - menuLabel.getLocalBounds().height) / 2 - 12.5f
        );
        menuLabel.setScale(1.2, 1.2);
    } else {
        menuButton.setFillColor(Color(125, 125, 125, 150));  // Полупрозрачный чёрный.
        menuButton.setSize(Vector2f(200, 50));  // Обычный размер.
        menuButton.setPosition(static_cast<float>(window.getSize().x / 2.0 - menuButton.getSize().x / 2),
                               static_cast<float>(window.getSize().y - 100));
        menuLabel.setPosition(
                menuButton.getPosition().x + (menuButton.getSize().x - menuLabel.getLocalBounds().width) / 2,
                menuButton.getPosition().y + (menuButton.getSize().y - menuLabel.getLocalBounds().height) / 2 - 7.5f
        );
        menuLabel.setScale(1.0, 1.0);
    }

    speedText.setString(
            cv.from_bytes("Максимальная скорость: ")
            + std::to_string(static_cast<int>(maxSpeed))
            + " mph"
    );

    window.draw(gameOverText);
    window.draw(speedText);
    window.draw(menuButton);
    window.draw(menuLabel);
}

// Метод отображения экрана поражения и обработки ожидания возврата в меню.
void GameOverScreen::PollEvents(MainWindow &window, float maxPlayerSpeed) {
    // Обработка цикла ожидания выхода в Главное меню.
    while (window.isOpen()) {
        draw(window, maxPlayerSpeed);
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
                // Переход в полноэкранный режим при нажатии клавиши F.
                if (event.key.scancode == Keyboard::Scan::F) {
                    if (!window.isFullscreen) {
                        window.isFullscreen = true;
                        window.create(VideoMode(1024, 768),
                                      "Back to the Future",
                                      sf::Style::Fullscreen);
                        window.setMainWindowIcon();
                    } else {  // И выход из него.
                        window.isFullscreen = false;
                        window.create(VideoMode(1024, 768),
                                      "Back to the Future",
                                      sf::Style::Titlebar | sf::Style::Close);
                        window.setMainWindowIcon();
                    }
                }
            }
        }
    }
}
