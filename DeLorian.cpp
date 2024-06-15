//
// Created by anoso on 17.05.2024.
//

#include "DeLorian.h"

#include "MainWindow.h"

DeLorian::DeLorian() = default;

void DeLorian::draw(MainWindow &window, int x, int y) {
    int ind = window.state / 10 + 2;
    window.sprites[ind].setPosition(x, y);
    window.draw(window.sprites[ind]);
    window.state = (window.state + 1) % 20;
}

void DeLorian::accelerate(MainWindow &window) {
    if (window.curMusic.openFromFile(window.songs[rand() % 3]))
        window.curMusic.play();

    int w = window.sprites[2].getLocalBounds().width * 0.35;
    int h = window.sprites[2].getLocalBounds().height * 0.35;

    int x = -w;
    int y = 500;

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
                    if (event.key.scancode == Keyboard::Scan::Space)
                        window.sounds[0].play();
                    if (event.key.scancode == Keyboard::Scan::Tab)
                        if (window.curMusic.openFromFile(window.songs[rand() % 3]))
                            window.curMusic.play();
                    if (event.key.scancode == Keyboard::Scan::Enter)
                        if (window.curMusic.getStatus() == SoundSource::Status::Playing)
                            window.curMusic.pause();
                        else if (window.curMusic.getStatus() == SoundSource::Status::Paused)
                            window.curMusic.play();
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

            x += 5;

            draw(window, x, y);
            window.display();
            window.clear();
            window.mainTimer.restart();
        }
    }
}
