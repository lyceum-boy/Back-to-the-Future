#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"
//
// Created by anoso on 17.05.2024.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include <iostream>
#include <locale>
#include <codecvt>

#include "MainWindow.h"
#include "Lightning.h"

// Относительные пути к изображениям.
#define BACKGROUND_PATH "static/img/background.jpg"  // Фон.
#define DELOREAN_PATH "static/img/delorean.png"      // ДеЛориан.
#define ROAD_PATH "static/img/road.png"              // Дорога.

// Относительные пути к спрайтам.
#define ACCELERATOR_PATH "static/sprites/accelerator.png"
#define DECELERATOR_1_PATH "static/img/road_cone.png"
#define DECELERATOR_2_PATH "static/img/road_fence.png"
#define DECELERATOR_3_PATH "static/img/road_stone.png"
#define CHARACTER_PATH "static/img/brown.png"

#define FIRE_PATH "static/img/fire.png" // Добавим путь к текстуре огня

#define THUNDERCLOUD_PATH "static/img/thundercloud.png"

// Относительный путь к фоновой музыке.
#define MUSIC_PATH "static/music/music.mp3"

#define FONT_PATH "static/fonts/Industry-Bold_RUS.ttf"

MainWindow::MainWindow(VideoMode vm, const std::string &str, int i) : RenderWindow(vm, str, i) {
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

    // Инициализация текстур бонусов
    if (!acceleratorTexture.loadFromFile(ACCELERATOR_PATH))
        throw std::runtime_error("Error loading accelerator texture");
    if (!deceleratorTextures.emplace_back().loadFromFile(DECELERATOR_1_PATH))
        throw std::runtime_error("Error loading decelerator texture 1");
    if (!deceleratorTextures.emplace_back().loadFromFile(DECELERATOR_2_PATH))
        throw std::runtime_error("Error loading decelerator texture 2");
    if (!deceleratorTextures.emplace_back().loadFromFile(DECELERATOR_3_PATH))
        throw std::runtime_error("Error loading decelerator texture 3");

    if (!explosionTexture.loadFromFile("static/img/explosion.png"))
        throw std::runtime_error("Error loading explosion texture");

    if (!lightningTexture.loadFromFile("static/img/lightning.png")) {
        throw std::runtime_error("Error loading lightning texture");
    }

    if (!thundercloudTexture.loadFromFile("static/img/thundercloud.png")) {
        throw std::runtime_error("Error loading thundercloud texture");
    }

    if (!fireTexture.loadFromFile(FIRE_PATH)) {
        throw std::runtime_error("Error loading fire texture");
    }

    if (!font.loadFromFile(FONT_PATH)) {
        throw std::runtime_error("Failed to load headerFont");
    }

    init();
}

void MainWindow::init() {
    hasAccelerator = false;
    hasDecelerator = false;

     isGameOver = false;
     isVictory = false;

    bonusTimer.restart();

    isFirstBonus = true;

    deceleratorHistory.clear();
    sprites.clear();
    songs.clear();
    speedometerCells.clear();

    explosions.clear();
    lightnings.clear();
    fireAnimations.clear();

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

    currentSpeed = 80.0f;  // Start with default speed
    maxPlayerSpeed = currentSpeed;
    UpdateSpeedometer();  // Initial update for speedometer

    speedText.setFont(font);
    speedText.setCharacterSize(24);
    speedText.setFillColor(sf::Color::Black);
    speedText.setPosition(10.0f, 50.0f); // Позиция текста на экране

    remainingTime = 15.0f; // 1 minute 40 seconds

    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(this->getSize().x - 150.0f, 10.0f); // Position timer at top right

    // Initialize clock face
    clockFace = new ClockFace(getSize());


    if (!characterTexture.loadFromFile(CHARACTER_PATH)) {
        throw std::runtime_error("Error loading character texture");
    }

    characterSprite.setTexture(characterTexture);
    characterSprite.setScale(0.1f, 0.1f); // Adjust the scale as needed
    characterSprite.setOrigin(characterSprite.getLocalBounds().width / 2, characterSprite.getLocalBounds().height / 2); // Set origin to center
    characterSprite.setPosition((float)this->getSize().x / 2 - 40, 120.0f); // Position the character at the top center
    isCharacterFalling = false;
    characterFallSpeed = 1.0f;
    characterRotationSpeed = 5.0f; // Set initial rotation speed

    isCharacterFlying = false;
    characterFlySpeed = 2.0f; // Скорость полета
    characterFlyDirection = 1.0f; // Направление движения (1 - вверх, -1 - вниз)
    characterFlyMaxY = characterSprite.getPosition().y - 20; // Верхняя граница движения
    characterFlyMinY = characterSprite.getPosition().y; // Нижняя граница движения

    // Initialize thunderclouds
    CreateThunderclouds();
}

void MainWindow::CreateThunderclouds() {
    // Используем текущее время для инициализации генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Генерируем случайное количество туч (от 5 до 10)
    int numClouds = rand() % 75 + 50; // От 5 до 10 туч

    // Генерируем тучи со случайными координатами за экраном справа
    for (int i = 0; i < numClouds; ++i) {
        float x = static_cast<float>(this->getSize().x + rand() % 2000 + 1000); // Случайная координата по X от 1000 до 3999
        auto y = static_cast<float>(rand() % 10 - 65);    // Случайная координата по Y от 0 до 49
        float speed = static_cast<float>(rand() % 5 + 5) / 10.0f; // Случайная скорость от 0.5 до 1.0
        float scale = static_cast<float>(rand() % 5 + 5) / 20.0f; // Случайный масштаб от 0.25 до 0.5

        thunderclouds.emplace_back(thundercloudTexture, sf::Vector2f(x, y), speed, scale);
    }
}


void MainWindow::DrawBackground() {
    draw(sprites[0]);

    clockFace->draw(*this);

    // Draw lightning
    for (auto &lightning: lightnings) {
        lightning.draw(*this);
    }

    // Draw thunderclouds
    for (auto& thundercloud : thunderclouds) {
        thundercloud.draw(*this);
    }

    draw(sprites[2]); // Отрисовка дороги
    draw(sprites[3]); // Отрисовка дороги
    draw(sprites[1]);

    if (hasAccelerator) {
        draw(acceleratorSprite);
    }
    if (hasDecelerator) {
        draw(deceleratorSprite);
    }

    if (!isVictory && !isGameOver) {
        draw(mainTitle);
        draw(timerText); // Draw the timer
    }

    for (auto &explosion: explosions) {
        explosion.draw(*this);
    }

    draw(characterSprite);

    // Отрисовка анимаций огня
    for (auto &fire : fireAnimations) {
        fire.draw(*this);
    }
}

void MainWindow::DeLoreanAway() {
    auto &delorean = sprites[1];

    delorean.move(5 * 0.5 * currentSpeed / 11, 0); // Двигаем первый спрайт дороги влево
    for (auto &fire :fireAnimations) {
        fire.sprite.move(-5 * 1.5 * currentSpeed / 11, 0);
    }
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
    if (isVictory)
        return;

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
        } else
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

void MainWindow::UpdateAnimations() {
    if (isVictory) {
        sf::Vector2f deLoreanPos = sprites[1].getPosition();
        fireAnimations.emplace_back(fireTexture,sf::Vector2f(deLoreanPos.x - 75, deLoreanPos.y - 30));
        fireAnimations.emplace_back(fireTexture,sf::Vector2f(deLoreanPos.x - 75, deLoreanPos.y - 5));
    }
    for (auto &fire : fireAnimations) {
        fire.update();
    }

    // Update explosions
    for (auto &explosion: explosions) {
        explosion.update();
    }
    explosions.erase(std::remove_if(explosions.begin(), explosions.end(), [](Explosion &e) { return e.isFinished(); }),
                     explosions.end());

    // Update lightning animations
    for (auto &lightning: lightnings) {
        lightning.update();
    }
    lightnings.erase(std::remove_if(lightnings.begin(), lightnings.end(), [](Lightning &l) { return l.isFinished(); }),
                     lightnings.end());

    for (auto& thundercloud : thunderclouds) {
        thundercloud.update(*this, currentSpeed); // Обновление положения тучи
    }

    float time = remainingTime - 5 >= 0 ? remainingTime - 5: 0;
    clockFace->update(time);

    if (isCharacterFalling) {
        characterFallSpeed += 0.1f; // Increase falling speed (gravity effect)
        characterSprite.move(0, characterFallSpeed);
        characterSprite.rotate(characterRotationSpeed); // Rotate the character around its center
        if (characterSprite.getPosition().y + characterSprite.getGlobalBounds().height / 2 >= this->getSize().y - 300) {
            characterSprite.setPosition(characterSprite.getPosition().x, this->getSize().y - characterSprite.getGlobalBounds().height / 2 - 300);
            isCharacterFalling = false; // Stop the character from falling further
            characterSprite.setRotation(90.0f); // Set the character to lie horizontally
        }
    }

    if (isCharacterFlying) {
        float newY = characterSprite.getPosition().y - characterFlyDirection * characterFlySpeed;

        // Изменение направления, если достигнута верхняя или нижняя граница
        if (newY <= characterFlyMaxY || newY >= characterFlyMinY) {
            characterFlyDirection = -characterFlyDirection;
        }

        characterSprite.setPosition(characterSprite.getPosition().x, newY);
        std::cout << characterFlyMaxY << std::endl;
        std::cout << characterFlyMinY << std::endl;
        std::cout << newY << std::endl;
    }
}

void MainWindow::CheckCollisions() {
    if (hasAccelerator && sprites[1].getGlobalBounds().intersects(acceleratorSprite.getGlobalBounds())) {
        currentSpeed += speedIncrement;
        maxPlayerSpeed = currentSpeed > maxPlayerSpeed ? currentSpeed : maxPlayerSpeed;
        if (currentSpeed > maxSpeed) {
            currentSpeed = maxSpeed;
            remainingTime = 5;
        }
        UpdateSpeedometer();
        hasAccelerator = false;
    }

    if (hasDecelerator && sprites[1].getGlobalBounds().intersects(deceleratorSprite.getGlobalBounds())) {
        currentSpeed -= speedIncrement;
        if (currentSpeed <= 0) {
            currentSpeed = 0;
            remainingTime = 5;
        }
        UpdateSpeedometer();
        hasDecelerator = false;

        // Создание взрыва
        sf::Vector2f deceleratorPosition = deceleratorSprite.getPosition();
        explosions.emplace_back(explosionTexture, deceleratorPosition);
    }
}

void MainWindow::UpdateTimer() {
    float elapsed = countdownClock.getElapsedTime().asSeconds();
    remainingTime -= elapsed;
    countdownClock.restart();

    if (remainingTime <= 5) {
        if (!isVictory)
            isGameOver = true;
        if (!isVictory) {
            currentSpeed = 0;
            UpdateSpeedometer();
            // Create a lightning instance in the top-right corner
            if (lightnings.empty())
                lightnings.emplace_back(lightningTexture, sf::Vector2f(537, 0));
            isCharacterFalling = true; // Start the character fall
        } else {
            UpdateSpeedometer();
            if (lightnings.empty())
                lightnings.emplace_back(lightningTexture, sf::Vector2f(537, 0));
            isCharacterFlying = true; // Start the character jump
        }

    }
    if (remainingTime <= 0) {
        remainingTime = 0;
        quit = true; // End the game
    }

    float time = remainingTime - 5 >= 0 ? remainingTime - 5: 0;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;
    timerText.setString(cv.from_bytes("Осталось: ") + std::to_string(static_cast<int>(time)) + " с");

    clockFace->update(time);
}

#pragma clang diagnostic pop
#pragma clang diagnostic pop