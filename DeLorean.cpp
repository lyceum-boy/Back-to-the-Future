//
// Created by anoso on 16.06.2024.
//

#include <iostream>
#include "DeLorean.h"

void DeLorean::accelerate(MainWindow &window) {
    if (window.curMusic.openFromFile(window.songs[rand() % 1]))
        window.curMusic.play();

    while (!window.quit) {
        // window.PollEvents();

        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.quit = true;
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.scancode == Keyboard::Scan::Escape)
                        window.quit = true;
//                    if (event.key.scancode == Keyboard::Scan::Space)
//                        window.sounds[0].play();
                    if (event.key.scancode == Keyboard::Scan::Tab)
                        if (window.curMusic.openFromFile(window.songs[rand() % 3]))
                            window.curMusic.play();
                    if (event.key.scancode == Keyboard::Scan::Enter)
                        if (window.curMusic.getStatus() == SoundSource::Status::Playing)
                            window.curMusic.pause();
                        else if (window.curMusic.getStatus() == SoundSource::Status::Paused)
                            window.curMusic.play();
                    if (event.key.scancode == Keyboard::Scan::Up || event.key.scancode == Keyboard::Scan::W) {
                        float x = 25;
                        float y = (float) (window.getSize().y * 6.75 / 10);
                        window.sprites[1].setPosition(x, y);
                        window.draw(window.sprites[1]);
                    }
                    if (event.key.scancode == Keyboard::Scan::Down || event.key.scancode == Keyboard::Scan::S) {
                        float x = 25;
                        float y = (float) (window.getSize().y * 8.25 / 10);
                        window.sprites[1].setPosition(x, y);
                        window.draw(window.sprites[1]);
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
            if (window.curMusic.openFromFile(window.songs[rand() % 3]))
                window.curMusic.play();
        }
        if (window.IsItTimeYet(time)) {
            window.DrawBackground();
            window.DrawSpeedometer();
            window.UpdateRoad();
            window.UpdateBonuses(); // Обновление бонусов
            window.CheckCollisions(); // Проверка коллизий
            window.display();
            window.clear();
            window.mainTimer.restart();
        }
    }
}
