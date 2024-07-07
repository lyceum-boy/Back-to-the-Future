//
// Created by anoso on 16.06.2024.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include "DeLorean.h"        // Класс ДеЛориана, логика игрового процесса.
#include "GameOverScreen.h"  // Класс окна поражения.
#include "VictoryScreen.h"   // Класс окна победы.

using namespace sf;  // Пространство имён библиотеки SFML.

// Метод запуска ДеЛориана и игрового процесса.
void DeLorean::accelerate(MainWindow &window) {
    if (window.curMusic.openFromFile(window.songs[0]))
        window.curMusic.play();

    GameOverScreen gameOverMenu;
    VictoryScreen victoryMenu;

    window.sounds[4].play();

    while (!window.quit) {
        Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed: {
                    window.quit = true;
                    window.close();
                    break;
                }
                case Event::KeyPressed:
                    if (event.key.scancode == Keyboard::Scan::Escape)
                        window.quit = true;
                    // Переход в полноэкранный режим при нажатии клавиши F.
                    if (event.key.scancode == Keyboard::Scan::F) {
                        if (!window.isFullscreen) {
                            window.isFullscreen = true;
                            window.create(VideoMode(1024, 768),
                                          "Back to the Future",
                                          Style::Fullscreen);
                            window.setMainWindowIcon();
                        } else {  // И выход из него.
                            window.isFullscreen = false;
                            window.create(VideoMode(1024, 768),
                                          "Back to the Future",
                                          Style::Titlebar | Style::Close);
                            window.setMainWindowIcon();
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
        if (MainWindow::IsItTimeYet(time)) {
            window.DrawBackground();
            window.DrawSpeedometer();
            window.UpdateRoad();
            if (window.currentSpeed >= window.maxSpeed)
                window.BackToTheFuture();
            window.UpdateBonuses();
            window.UpdateAnimations();
            window.CheckCollisions();
            window.UpdateTimer();
            window.display();
            window.clear();
            window.mainTimer.restart();
        }

        // Проверка на условия проигрыша или победы.
        if (window.remainingTime <= 0) {
            window.curMusic.setVolume(75);
            if (window.isGameOver) {
                gameOverMenu.PollEvents(window, window.maxPlayerSpeed);
            } else {
                victoryMenu.PollEvents(window, window.totalPlayerTime);
            }
            break;
        }

    }

    // После завершения игры возвращаемся в главное меню.
    window.quit = false;
}

#pragma clang diagnostic pop