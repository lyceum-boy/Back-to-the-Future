//
// Created by anoso on 17.05.2024.
//

#include <iostream>
#include "MainWindow.h"

// Относительные пути к изображениям.
#define BACKGROUND_PATH "static/img/background.jpg"
#define DELOREAN_PATH "static/img/delorean.png"
#define ROAD_PATH "static/img/road.png"

#define ACCELERATOR_PATH "static/img/accelerator.png"
#define DECELERATOR_PATH "static/img/decelerator.png"

// Относительные пути к фоновой музыке.
#define MUSIC_PATH "static/music/music.mp3"

MainWindow::MainWindow(VideoMode vm, const std::string &str) : RenderWindow(vm, str) {
//    this->create(VideoMode(1024, 768), "Back to the Future", sf::Style::Fullscreen);
    setFramerateLimit(60);

    Texture tmp;
    if (!tmp.loadFromFile(BACKGROUND_PATH))
        throw std::runtime_error("Error");
    images.push_back(tmp);
    if (!tmp.loadFromFile(DELOREAN_PATH))
        throw std::runtime_error("Error");
    images.push_back(tmp);
    if (!tmp.loadFromFile(ROAD_PATH))
        throw std::runtime_error("Error");
    images.push_back(tmp);

    Sprite background;
    background.setTexture(images[0]);
    background.setScale(
            (float) this->getSize().x / background.getLocalBounds().width,
            (float) this->getSize().y / background.getLocalBounds().height
    );
    sprites.push_back(background);

    Sprite deLorean;
    deLorean.setTexture(images[1]);
    deLorean.setTextureRect(IntRect(0, 0, images[1].getSize().x, images[1].getSize().y));
    deLorean.setScale(0.35, 0.35);
    deLorean.setPosition(25, (float) (this->getSize().y * 6.75 / 10));
    sprites.push_back(deLorean);

    // Один спрайт дороги располагается в начале экрана
    Sprite road1;
    road1.setTexture(images[2]);
    road1.setScale(1.5, 1);
    road1.setPosition(0, this->getSize().y - road1.getLocalBounds().height);
    sprites.push_back(road1);

    // Второй спрайт дороги начинается сразу после первого
    Sprite road2;
    road2.setTexture(images[2]);
    road2.setScale(1.5, 1);
    road2.setPosition(road1.getLocalBounds().width * road1.getScale().x,
                      this->getSize().y - road2.getLocalBounds().height);
    sprites.push_back(road2);

    songs.emplace_back(MUSIC_PATH);

    // Инициализация текстур бонусов
    if (!acceleratorTexture.loadFromFile(ACCELERATOR_PATH))
        throw std::runtime_error("Error loading accelerator texture");
    if (!deceleratorTexture.loadFromFile(DECELERATOR_PATH))
        throw std::runtime_error("Error loading decelerator texture");

    // Инициализация спрайтов бонусов
    acceleratorSprite.setTexture(acceleratorTexture);
    acceleratorSprite.setScale(0.5, 0.5);
    deceleratorSprite.setTexture(deceleratorTexture);
    deceleratorSprite.setScale(0.5, 0.5);

    // Initialize speedometer cells
    const float cellWidth = 25.0f;
    const float cellHeight = 20.0f;
    for (int i = 0; i < 8; ++i) {
        RectangleShape cell(Vector2f(cellWidth, cellHeight));
        cell.setFillColor(Color::Black);
        cell.setOutlineColor(Color::White);
        cell.setOutlineThickness(2);
        cell.setPosition(10.0f + i * (cellWidth), 10.0f);
        speedometerCells.push_back(cell);
    }

    currentSpeed = 11.0f;  // Start with default speed
    UpdateSpeedometer();  // Initial update for speedometer
}

void MainWindow::DrawBackground() {
    draw(sprites[0]);
    draw(sprites[2]); // Отрисовка дороги
    draw(sprites[3]); // Отрисовка дороги
    draw(sprites[1]);

    if (hasAccelerator) {
        draw(acceleratorSprite);
    }
    if (hasDecelerator) {
        draw(deceleratorSprite);
    }

    draw(mainTitle);
}

void MainWindow::UpdateRoad() {
    auto &road1 = sprites[2];
    auto &road2 = sprites[3];

    road1.move(-5 * currentSpeed / 11, 0); // Двигаем первый спрайт дороги влево
    road2.move(-5 * currentSpeed / 11, 0); // Двигаем второй спрайт дороги влево

    // Если первый спрайт дороги вышел за пределы экрана, перемещаем его вправо за вторым спрайтом
    if (road1.getPosition().x + road1.getLocalBounds().width * road1.getScale().x < 0) {
        road1.setPosition(road2.getPosition().x + road2.getLocalBounds().width * road2.getScale().x,
                          road1.getPosition().y);
    }

    // Если второй спрайт дороги вышел за пределы экрана, перемещаем его вправо за первым спрайтом
    if (road2.getPosition().x + road2.getLocalBounds().width * road2.getScale().x < 0) {
        road2.setPosition(road1.getPosition().x + road1.getLocalBounds().width * road1.getScale().x,
                          road2.getPosition().y);
    }
}

void MainWindow::PollEvents() {
    sf::Event event{};
    while (pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                quit = true;
                break;
            case sf::Event::KeyPressed:
                if (event.key.scancode == Keyboard::Scan::Escape)
                    quit = true;
                if (event.key.scancode == Keyboard::Scan::Space)
                    sounds[0].play();
                if (event.key.scancode == Keyboard::Scan::Tab)
                    if (curMusic.openFromFile(songs[rand() % 3]))
                        curMusic.play();
                if (event.key.scancode == Keyboard::Scan::Enter)
                    if (curMusic.getStatus() == SoundSource::Status::Playing)
                        curMusic.pause();
                if (event.key.scancode == Keyboard::Scan::W) {
                    float x, y;
                    std::cout << "delorean" << std::endl;

                    x = sprites[1].getPosition().x;
                    y = sprites[1].getPosition().y - 100;
                    sprites[1].setPosition(x, y);
                    draw(sprites[1]);
                } else if (curMusic.getStatus() == SoundSource::Status::Paused)
                    curMusic.play();
                break;
            default:
                break;
        }
    }
}

void MainWindow::DrawSpeedometer() {
    for (const auto &cell: speedometerCells) {
        draw(cell);
    }
}

void MainWindow::UpdateSpeedometer() {
    int activeCells = static_cast<int>(currentSpeed / speedIncrement);

    for (int i = 0; i < speedometerCells.size(); ++i) {
        if (i < activeCells) {
            float percent = static_cast<float>(i) / (speedometerCells.size() - 1);
            Color color;
            color.r = static_cast<Uint8>(255 * (1 - percent));
            color.g = static_cast<Uint8>(255 * percent);
            color.b = 0;
            speedometerCells[i].setFillColor(color);
        } else {
            speedometerCells[i].setFillColor(Color::Black);
        }
    }
}

void MainWindow::UpdateBonuses() {
    if (bonusTimer.getElapsedTime().asSeconds() > 5.0f) {
        if (!hasAccelerator && !hasDecelerator) {
            int lane = rand() % 2; // Случайный выбор полосы (0 или 1)
            float y = (lane == 0) ? (float) (this->getSize().y * 7 / 10) : (float) (this->getSize().y * 8.5 / 10);
            float x = this->getSize().x; // Появление за пределами экрана справа

            if (rand() % 2 == 0) {
                hasAccelerator = true;
                acceleratorSprite.setPosition(x, y);
                acceleratorSprite.setScale(0.10, 0.10);
            } else {
                hasDecelerator = true;
                deceleratorSprite.setPosition(x, y);
                deceleratorSprite.setScale(0.10, 0.10);
            }
        }
        bonusTimer.restart();
    }

    if (hasAccelerator) {
        acceleratorSprite.move(-5 * currentSpeed / 11, 0);
        if (acceleratorSprite.getPosition().x + acceleratorSprite.getGlobalBounds().width < 0) {
            hasAccelerator = false;
        }
    }

    if (hasDecelerator) {
        deceleratorSprite.move(-5 * currentSpeed / 11, 0);
        if (deceleratorSprite.getPosition().x + deceleratorSprite.getGlobalBounds().width < 0) {
            hasDecelerator = false;
        }
    }
}

void MainWindow::CheckCollisions() {
    if (hasAccelerator && sprites[1].getGlobalBounds().intersects(acceleratorSprite.getGlobalBounds())) {
        currentSpeed += speedIncrement;
        if (currentSpeed > maxSpeed) {
            currentSpeed = maxSpeed;
        }
        UpdateSpeedometer();
        hasAccelerator = false;
    }

    if (hasDecelerator && sprites[1].getGlobalBounds().intersects(deceleratorSprite.getGlobalBounds())) {
        currentSpeed -= speedIncrement;
        if (currentSpeed < 0) {
            currentSpeed = 0;
        }
        UpdateSpeedometer();
        hasDecelerator = false;
    }
}
