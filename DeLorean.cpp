//
// Created by anoso on 16.06.2024.
//

#include <iostream>
#include "DeLorean.h"
#include "GameOverScreen.h"
#include "VictoryScreen.h"

void DeLorean::accelerate(MainWindow &window) {
    if (window.curMusic.openFromFile(window.songs[rand() % 1]))
        window.curMusic.play();

    GameOverScreen gameOverMenu;
    VictoryScreen victoryMenu;

    window.sounds[4].play();

    while (!window.quit) {
        // window.PollEvents();

        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    window.quit = true;
                    window.close();
                    break;
                }
                case sf::Event::KeyPressed:
                    if (event.key.scancode == Keyboard::Scan::Escape)
                        window.quit = true;
                    // Переход в полноэкранный режим при нажатии клавиши F.
                    if (event.key.scancode == Keyboard::Scan::F) {
                        if (!window.isFullscreen) {
                            window.isFullscreen = true;
                            window.create(VideoMode(1024, 768),
                                          "Back to the Future",
                                          sf::Style::Fullscreen);
                        } else {  // И выход из него.
                            window.isFullscreen = false;
                            window.create(VideoMode(1024, 768),
                                          "Back to the Future",
                                          sf::Style::Titlebar | sf::Style::Close);
// todo
                            //                            // Загрузка иконки окна мини-игры.
//                            sf::Image icon;
//                            icon.loadFromFile(ICON_PATH);
//                            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
                        }
                    }
                    if (event.key.scancode == Keyboard::Scan::Up || event.key.scancode == Keyboard::Scan::W) {
                        if (window.remainingTime - 5 >= 0) {
                            if (!window.deLoreanOnFirstRoad) {
                                float x = 25;
                                float y = static_cast<float>(window.getSize().y * 7.0 / 10);
                                window.sprites[1].setPosition(x, y);
                                window.draw(window.sprites[1]);

                                window.deLoreanOnFirstRoad = true;
                                window.sounds[3].play();
                            }
                        }
                    }
                    if (event.key.scancode == Keyboard::Scan::Down || event.key.scancode == Keyboard::Scan::S) {
                        if (window.remainingTime - 5 >= 0) {
                            if (window.deLoreanOnFirstRoad) {
                                float x = 25;
                                float y = static_cast<float>(window.getSize().y * 8.5 / 10);
                                window.sprites[1].setPosition(x, y);
                                window.draw(window.sprites[1]);

                                window.deLoreanOnFirstRoad = false;
                                window.sounds[3].play();
                            }
                        }
                    }
                    if (event.key.scancode == Keyboard::Scan::Space) {
                        window.currentSpeed += window.speedIncrement;
                        if (window.currentSpeed > window.maxSpeed)
                            window.currentSpeed = window.maxSpeed;
                        window.UpdateSpeedometer();
                    }
                    break;
                default:
                    break;
            }
        }

        int time = window.mainTimer.getElapsedTime().asMilliseconds();
        if (window.curMusic.getStatus() == SoundSource::Status::Stopped) {
            if (window.curMusic.openFromFile(window.songs[0]))
                window.curMusic.play();
        }
        if (window.IsItTimeYet(time)) {
            window.DrawBackground();
            window.DrawSpeedometer();
            window.UpdateRoad();
            if (window.currentSpeed >= window.maxSpeed)
                window.DeLoreanAway();
            window.UpdateBonuses(); // Обновление бонусов
            window.UpdateAnimations();
            window.CheckCollisions(); // Проверка коллизий
            window.UpdateTimer(); // Update the timer
            window.display();
            window.clear();
            window.mainTimer.restart();
        }

        // Проверка на условия проигрыша или победы
        if (window.remainingTime <= 0) {
            if (window.isGameOver) {
                gameOverMenu.PollEvents(window, window.maxPlayerSpeed);
            } else {
                victoryMenu.PollEvents(window, window.totalPlayerTime);
            }
            break;
        }

        if (window.currentSpeed >= 88) {
            // todo: набранная скорость в момент выхода таймера
            if (!window.isVictory) {
                window.isVictory = true;
                window.isGameOver = false;
                window.isDeloreanSpriteMoving = true;
                window.remainingTime = 5;
                window.curMusic.setVolume(70);
                window.sounds[0].play();
            }
        }
    }

    // После завершения игры возвращаемся в главное меню
    window.quit = false;
}