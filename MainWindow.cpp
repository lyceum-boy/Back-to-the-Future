//
// Created by anoso on 17.05.2024.
//

#include "MainWindow.h"

#include <iostream>

// Относительные пути к изображениям.
#define BACKGROUND_PATH "static/img/background.jpg"  // Фон.
#define DELOREAN_PATH "static/img/delorean.png"      // ДеЛориан.
#define ROAD_PATH "static/img/road.png"              // Дорога.

#define ACCELERATOR_PATH "static/img/accelerator.png"
#define DECELERATOR_1_PATH "static/img/road_cone.png"
#define DECELERATOR_2_PATH "static/img/road_fence.png"
#define DECELERATOR_3_PATH "static/img/road_stone.png"

// Относительный путь к фоновой музыке.
#define MUSIC_PATH "static/music/music.mp3"

#define FONT_PATH "static/fonts/OpenSans-SemiBold.ttf"

MainWindow::MainWindow(VideoMode vm, const std::string &str) : RenderWindow(vm, str) {
    setVerticalSyncEnabled(true);
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
    deLorean.setPosition(25, (float) (this->getSize().y * 7 / 10));
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

    if (!deceleratorTextures.emplace_back().loadFromFile(DECELERATOR_1_PATH))
        throw std::runtime_error("Error loading decelerator texture 1");
    if (!deceleratorTextures.emplace_back().loadFromFile(DECELERATOR_2_PATH))
        throw std::runtime_error("Error loading decelerator texture 2");
    if (!deceleratorTextures.emplace_back().loadFromFile(DECELERATOR_3_PATH))
        throw std::runtime_error("Error loading decelerator texture 3");

    // Инициализация спрайтов бонусов
    acceleratorSprite.setTexture(acceleratorTexture);
    acceleratorSprite.setScale(0.4f, 0.4f);

    // Initialize speedometer cells
    const float cellWidth = 25.0f;
    const float cellHeight = 20.0f;
    for (int i = 0; i < 11; ++i) {
        RectangleShape cell(Vector2f(cellWidth, cellHeight));
        cell.setFillColor(Color::Black);
        cell.setOutlineColor(Color::White);
        cell.setOutlineThickness(2);
        cell.setPosition(10.0f + i * (cellWidth), 10.0f);
        speedometerCells.push_back(cell);
    }

    currentSpeed = 8.0f;  // Start with default speed
    UpdateSpeedometer();  // Initial update for speedometer

    if (!font.loadFromFile(FONT_PATH)) {
        throw std::runtime_error("Failed to load font");
    }

    speedText.setFont(font);
    speedText.setCharacterSize(24);
    speedText.setFillColor(sf::Color::Black);
    speedText.setPosition(10.0f, 50.0f); // Позиция текста на экране
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

    road1.move(-5 * 1.5 * currentSpeed / 11, 0); // Двигаем первый спрайт дороги влево
    road2.move(-5 * 1.5 * currentSpeed / 11, 0); // Двигаем второй спрайт дороги влево

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

    // Отображение текущей скорости
    speedText.setString("Current Speed: " + std::to_string(currentSpeed) + " km/h");
    draw(speedText);
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
    // Если прошло более трёх секунд с момента последнего бонуса
    if (bonusTimer.getElapsedTime().asSeconds() > 3.0f) {
        // Сбросить таймер
        bonusTimer.restart();

        // Проверяем, есть ли уже активный бонус (ускоритель или замедлитель)
        if (hasAccelerator || hasDecelerator) {
            return; // Если есть, просто выходим из функции без генерации нового бонуса
        }

        // Генерируем случайное число для выбора бонуса (0 - ускоритель, 1 - замедлитель)
        int bonusType;
        if (isFirstBonus) {
            isFirstBonus = false;
            bonusType = 0;
        }
        else
            bonusType = rand() % 2;

        // Проверяем историю появления замедлителей
        bool lastThreeWereDecelerators = false;
        if (deceleratorHistory.size() >= 3) {
            lastThreeWereDecelerators = (deceleratorHistory[deceleratorHistory.size() - 1] &&
                                         deceleratorHistory[deceleratorHistory.size() - 2] &&
                                         deceleratorHistory[deceleratorHistory.size() - 3]);
        }

        // Если последние три были замедлителями, генерируем ускоритель
        if (lastThreeWereDecelerators) {
            bonusType = 0;  // Ускоритель
        }

        // Проверяем, чтобы не было двух ускорителей подряд
        if (bonusType == 0 && !deceleratorHistory.empty() && !deceleratorHistory.back()) {
            // Если последний бонус был ускорителем, генерируем замедлитель
            bonusType = 1;
        }

        // Определяем положение появления бонуса
        int lane = rand() % 2; // Случайный выбор полосы (0 или 1)
        float y = (lane == 0) ? (float) (getSize().y * 8.25 / 10) : (float) (getSize().y * 9.8 / 10);
        float x = getSize().x; // Появление за пределами экрана справа

        if (bonusType == 0) {
            // Ускоритель
            hasAccelerator = true;
            acceleratorSprite.setPosition(x, y - acceleratorTexture.getSize().y * acceleratorSprite.getScale().y);

            // Обновляем историю появлений
            deceleratorHistory.push_back(false); // false для ускорителя
            if (deceleratorHistory.size() > 3) {
                deceleratorHistory.erase(
                        deceleratorHistory.begin());  // Удаляем первый элемент, если история слишком длинная
            }
        } else {
            // Замедлитель
            hasDecelerator = true;
            int deceleratorIndex = rand() % 3;  // Случайный выбор индекса замедлителя
            deceleratorSprite.setTexture(deceleratorTextures[deceleratorIndex]);
            deceleratorSprite.setScale(0.4f, 0.4f);
            deceleratorSprite.setPosition(x, y - deceleratorTextures[deceleratorIndex].getSize().y *
                                                 deceleratorSprite.getScale().y);

            // Добавляем текущий бонус в историю
            deceleratorHistory.push_back(true); // true для замедлителя
            if (deceleratorHistory.size() > 3) {
                deceleratorHistory.erase(
                        deceleratorHistory.begin());  // Удаляем первый элемент, если история слишком длинная
            }
        }
    }

    // Обновление позиции ускорителя, если он активен
    if (hasAccelerator) {
        acceleratorSprite.move(-5 * 1.5 * currentSpeed / 11, 0);
        if (acceleratorSprite.getPosition().x + acceleratorSprite.getGlobalBounds().width < 0) {
            hasAccelerator = false;
        }
    }

    // Обновление позиции замедлителя, если он активен
    if (hasDecelerator) {
        deceleratorSprite.move(-5 * 1.5 * currentSpeed / 11, 0);
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
