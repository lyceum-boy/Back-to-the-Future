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

#include "MainWindow.h"
#include "MainMenu.h"
#include "DeLorean.h"

#define FONT_PATH "static/fonts/OpenSans-SemiBold.ttf"

using namespace sf;

enum class GameState {
    MainMenu,
    Playing,
    HowToPlay,
    About
};

int main(int argc, char *argv[]) {
    srand(time(nullptr));

    MainWindow window(VideoMode(1024, 768), "Back to the Future", sf::Style::Titlebar | sf::Style::Close);

    sf::Image icon;
    icon.loadFromFile("static/img/icon.png"); // File/Image/Pixel
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


    GameState gameState = GameState::MainMenu;

    std::vector<RectangleShape> buttons;
    std::vector<Text> buttonLabels;

    MainMenu menu;

    while (window.isOpen()) {
        window.clear(Color::White);

        switch (gameState) {
            case GameState::MainMenu:
                if (window.curMusic.getStatus() == SoundSource::Status::Playing)
                    window.curMusic.stop();
                menu.displayMainMenu(window, buttons, buttonLabels);
                break;
            case GameState::Playing:
                menu.curMusic.stop();
                DeLorean deLorean;
                deLorean.accelerate(window);
                gameState = GameState::MainMenu;
                break;
            case GameState::HowToPlay:
                menu.showHowToPlay(window);
                break;
            case GameState::About:
                menu.showAbout(window);
                break;
        }

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (gameState == GameState::MainMenu) {
                    if (buttons[0].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        gameState = GameState::Playing;
                        window.reset();
                    } else if (buttons[1].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        gameState = GameState::HowToPlay;
                    } else if (buttons[2].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        gameState = GameState::About;
                    }
                } else if (gameState == GameState::HowToPlay || gameState == GameState::About) {
                    if (menu.backButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        gameState = GameState::MainMenu; // Переход в главное меню при нажатии "Назад"
                    }
                }
            } else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                gameState = GameState::MainMenu;
            }
        }
        if (menu.curMusic.getStatus() == SoundSource::Status::Stopped) {
            if (menu.curMusic.openFromFile(menu.songs[rand() % 1]))
                menu.curMusic.play();
        }
    }

    return 0;
}

#pragma clang diagnostic pop