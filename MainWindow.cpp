//
// Created by anoso on 17.05.2024.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include "MainWindow.h"  // Класс главного окна программы.

// Относительные пути к изображениям.
#define ICON_PATH "static/img/icon.png"              // Иконка мини-игры.
#define BACKGROUND_PATH "static/img/background.jpg"  // Фон для сцены с часовой башней.

// Относительные пути к спрайтам.
#define DELOREAN_PATH "static/sprites/delorean.png"  // Спрайт ДеЛориана.
#define ROAD_PATH "static/sprites/road.png"          // Спрайт дороги.

#define ACCELERATOR_PATH "static/sprites/accelerator.png"   // Спрайт ускоряющего бонуса (канистры).
#define DECELERATOR_1_PATH "static/sprites/road_cone.png"   // Спрайт замедляющего бонуса (конуса).
#define DECELERATOR_2_PATH "static/sprites/road_fence.png"  // Спрайт замедляющего бонуса (забора).
#define DECELERATOR_3_PATH "static/sprites/road_stone.png"  // Спрайт замедляющего бонуса (камня).

#define THUNDERCLOUD_PATH "static/sprites/thundercloud.png"  // Спрайт грозовых туч.
#define DOC_BROWN_PATH "static/sprites/brown.png"            // Спрайт доктора Эмметта Брауна.

// Относительные пути к спрайт-листам.
#define EXPLOSION_PATH "static/spritesheets/explosion.png"  // Спрайт-лист анимации взрыва при ударе о тормозящий бонус.
#define LIGHTNING_PATH "static/spritesheets/lightning.png"  // Спрайт-лист анимации молнии, ударяющей в полночь.
#define FIRE_TRACE_PATH "static/spritesheets/fire_trace.png" // Спрайт-лист анимации огненного следа от колёс ДеЛориана.

// Относительный путь к фоновой музыке.
#define MUSIC_PATH "static/music/game_music.mp3"

// Относительные пути к звукам.
#define THUNDER_SOUND_PATH "static/sounds/thunder.mp3"
#define BUMP_SOUND_PATH "static/sounds/bump.mp3"
#define FUELING_SOUND_PATH "static/sounds/fueling.mp3"
#define DRIFT_SOUND_PATH "static/sounds/drift.mp3"
#define START_ENGINE_SOUND_PATH "static/sounds/start_engine.mp3"  // Звук двигателя
#define ACCELERATE_SOUND_PATH "static/sounds/accelerate.mp3"      // З

// Относительный путь к шрифту основного текста.
#define TEXT_FONT_PATH "static/fonts/Industry-Bold_RUS.ttf"

// Игровые константы.
#define INITIAL_TIME 100  // Время таймера обратного отсчёта.
#define INITIAL_SPEED 8   // Начальная скорость.
#define MAXIMAL_SPEED 88  // Максимальная скорость.

using namespace sf;  // Пространство имён библиотеки SFML.

MainWindow::MainWindow(VideoMode vm, const std::string &str, int i) : RenderWindow(vm, str, i) {
    setFramerateLimit(60);

    // Инициализация текстур.
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

    // Инициализация текстур ускоряющих и замедляющих бонусов.
    if (!acceleratorTexture.loadFromFile(ACCELERATOR_PATH))
        throw std::runtime_error("Error");
    if (!deceleratorTextures.emplace_back().loadFromFile(DECELERATOR_1_PATH))
        throw std::runtime_error("Error");
    if (!deceleratorTextures.emplace_back().loadFromFile(DECELERATOR_2_PATH))
        throw std::runtime_error("Error");
    if (!deceleratorTextures.emplace_back().loadFromFile(DECELERATOR_3_PATH))
        throw std::runtime_error("Error");

    if (!thundercloudTexture.loadFromFile(THUNDERCLOUD_PATH))
        throw std::runtime_error("Error");
    if (!brownTexture.loadFromFile(DOC_BROWN_PATH))
        throw std::runtime_error("Error");

    // Инициализация текстур анимаций.
    if (!explosionTexture.loadFromFile(EXPLOSION_PATH))
        throw std::runtime_error("Error");
    if (!fireTexture.loadFromFile(FIRE_TRACE_PATH))
        throw std::runtime_error("Error");
    if (!lightningTexture.loadFromFile(LIGHTNING_PATH))
        throw std::runtime_error("Error");

    // Инициализация шрифта основного текста.
    if (!textFont.loadFromFile(TEXT_FONT_PATH))
        throw std::runtime_error("Error");

    init();  // Инициализация полей при запуске игры.
}

// Метод инициализации окна игры при запуске и перезапуске.
void MainWindow::init() {
    // Очистка векторов для избегания двойного заполнения при перезапуске.
    sprites.clear();
    songs.clear();
    buf.clear();
    sounds.clear();

    speedometerCells.clear();

    deceleratorHistory.clear();

    explosions.clear();
    fireTraces.clear();
    lightnings.clear();

    thunderclouds.clear();

    curMusic.setVolume(75);

    hasAccelerator = false;
    hasDecelerator = false;

    isGameOver = false;
    isVictory = false;

    bonusTimer.restart();

    isFirstBonus = true;

    isGameOver = false;
    isVictory = false;

    isDeloreanSpriteMoving = false;

    isFullscreen = false;

    deLoreanOnFirstRoad = true;

    quit = false;

    Sprite background;
    background.setTexture(images[0]);
    background.setScale(
            static_cast<float>(this->getSize().x) / background.getLocalBounds().width,
            static_cast<float>(this->getSize().y) / background.getLocalBounds().height
    );
    sprites.push_back(background);

    Sprite deLorean;
    deLorean.setTexture(images[1]);
    deLorean.setTextureRect(
            IntRect(0, 0,
                    static_cast<int>(images[1].getSize().x), static_cast<int>(images[1].getSize().y))
    );
    deLorean.setScale(0.35, 0.35);
    deLorean.setPosition(25, static_cast<float>(this->getSize().y) * 7 / 10.0f);
    sprites.push_back(deLorean);

    // Один спрайт дороги располагается в начале экрана.
    Sprite road1;
    road1.setTexture(images[2]);
    road1.setScale(1.5, 1);
    road1.setPosition(0, static_cast<float>(this->getSize().y) - road1.getLocalBounds().height);
    sprites.push_back(road1);

    // Второй спрайт дороги начинается сразу после первого.
    Sprite road2;
    road2.setTexture(images[2]);
    road2.setScale(1.5, 1);
    road2.setPosition(road1.getLocalBounds().width * road1.getScale().x,
                      static_cast<float>(this->getSize().y) - road2.getLocalBounds().height);
    sprites.push_back(road2);

    songs.emplace_back(MUSIC_PATH);

    // Инициализация спрайтов бонусов.
    acceleratorSprite.setTexture(acceleratorTexture);
    acceleratorSprite.setScale(0.4f, 0.4f);

    // Инициализация шкалы спидометра.
    const float cellWidth = 25.0f;
    const float cellHeight = 20.0f;
    for (int i = 0; i < 11; ++i) {
        RectangleShape cell(Vector2f(cellWidth, cellHeight));
        cell.setFillColor(Color::Black);
        cell.setOutlineColor(Color::White);
        cell.setOutlineThickness(2);
        cell.setPosition(10.0f + static_cast<float>(i) * (cellWidth), 10.0f);
        speedometerCells.push_back(cell);
    }

    currentSpeed = INITIAL_SPEED;
    maxPlayerSpeed = currentSpeed;
    UpdateSpeedometer();

    speedText.setFont(textFont);
    speedText.setCharacterSize(22);
    speedText.setFillColor(sf::Color::White);
    speedText.setPosition(10.0f, 40.0f);  // Позиция текста на экране.

    remainingTime = INITIAL_TIME + 5.0f;  // 5 секунд на анимацию.

    timerText.setFont(textFont);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(static_cast<float>(this->getSize().x) - 175.0f, 7.5f);  // В правом верхнем углу.

    // Инициализация стрелочных часов.
    clockFace = new ClockFace();

    brownSprite.setRotation(0);
    brownSprite.setTexture(brownTexture);
    brownSprite.setScale(0.1f, 0.1f);
    brownSprite.setOrigin(brownSprite.getLocalBounds().width / 2,
                          brownSprite.getLocalBounds().height / 2);  // Привязка к центру спрайта.
    brownSprite.setPosition(static_cast<float>( this->getSize().x) / 2 - 40, 120.0f);

    isBrownFalling = false;     // Флаг падения.
    brownFallSpeed = 1.0f;      // Скорость падения.
    brownRotationSpeed = 5.0f;  // Скорость вращения.

    isBrownJumping = false;
    brownJumpSpeed = 2.0f;      // Скорость прыжка.
    brownJumpDirection = 1.0f;  // Направление движения (1 - вверх, -1 - вниз).
    brownJumpMaxY = brownSprite.getPosition().y - 20;  // Верхняя граница движения.
    brownJumpMinY = brownSprite.getPosition().y;       // Нижняя граница движения.

    // Создание грозовых туч.
    CreateThunderclouds();

    // Инициализация звуков.
    SoundBuffer tmp_buf;
    if (!tmp_buf.loadFromFile(THUNDER_SOUND_PATH))
        throw std::runtime_error("Error");
    buf.push_back(tmp_buf);

    Sound tmp_sound;
    tmp_sound.setBuffer(buf[0]);
    sounds.push_back(tmp_sound);

    if (!tmp_buf.loadFromFile(BUMP_SOUND_PATH))
        throw std::runtime_error("Error");
    buf.push_back(tmp_buf);

    tmp_sound.setBuffer(buf[1]);
    sounds.push_back(tmp_sound);

    if (!tmp_buf.loadFromFile(FUELING_SOUND_PATH))
        throw std::runtime_error("Error");
    buf.push_back(tmp_buf);

    tmp_sound.setBuffer(buf[2]);
    sounds.push_back(tmp_sound);

    if (!tmp_buf.loadFromFile(DRIFT_SOUND_PATH))
        throw std::runtime_error("Error");
    buf.push_back(tmp_buf);

    tmp_sound.setBuffer(buf[3]);
    sounds.push_back(tmp_sound);

    if (!tmp_buf.loadFromFile(START_ENGINE_SOUND_PATH))
        throw std::runtime_error("Error");
    buf.push_back(tmp_buf);

    tmp_sound.setBuffer(buf[4]);
    sounds.push_back(tmp_sound);

    if (!tmp_buf.loadFromFile(ACCELERATE_SOUND_PATH))
        throw std::runtime_error("Error");
    buf.push_back(tmp_buf);

    tmp_sound.setBuffer(buf[5]);
    sounds.push_back(tmp_sound);
}

// Метод создания грозовых туч в небе над дорогой.
void MainWindow::CreateThunderclouds() {
    // Используем текущее время для инициализации генератора случайных чисел.
    srand(static_cast<unsigned int>(std::time(nullptr)));

    int numClouds = rand() % 75 + 50;  // От 50 до 74 туч.

    // Генерируем тучи со случайными координатами за экраном справа
    for (int i = 0; i < numClouds; ++i) {
        float x = static_cast<float>(this->getSize().x + rand() % 2000 + 1000);
        auto y = static_cast<float>(rand() % 10 - 65);
        float speed = static_cast<float>(rand() % 5 + 5) / 10.0f;
        float scale = static_cast<float>(rand() % 5 + 5) / 20.0f;

        thunderclouds.emplace_back(thundercloudTexture, sf::Vector2f(x, y), speed, scale);
    }
}

// Метод отрисовки фона и всех игровых объектов.
void MainWindow::DrawBackground() {
    draw(sprites[0]);  // Отрисовка фонового изображения.

    clockFace->draw(*this);  // Отрисовка стрелочных часов.

    // Отрисовка кадра анимации молнии.
    for (auto &lightning: lightnings) {
        lightning.draw(*this);
    }

    // Отрисовка грозовых туч.
    for (auto &thundercloud: thunderclouds) {
        thundercloud.draw(*this);
    }

    draw(sprites[2]);  // Отрисовка первой части дороги.
    draw(sprites[3]);  // Отрисовка второй части дороги.
    draw(sprites[1]);  // Отрисовка ДеЛориана.

    // Отрисовка ускоряющих и тормозящих бонусов.
    if (hasAccelerator) {
        draw(acceleratorSprite);
    }
    if (hasDecelerator) {
        draw(deceleratorSprite);
    }

    // Отрисовка таймера обратного отсчёта.
    if (!isVictory && !isGameOver) {
        draw(timerText);
    }

    // Отрисовка анимации взрыва.
    for (auto &explosion: explosions) {
        explosion.draw(*this);
    }

    // Отрисовка доктора Эммета Брауна на часовой башне.
    draw(brownSprite);

    // Отрисовка кадра анимации огненного следа.
    for (auto &fire: fireTraces) {
        fire.draw(*this);
    }
}

// Метод отрисовки спидометра на экране.
void MainWindow::DrawSpeedometer() {
    // Отрисовка шкалы спидометра.
    for (const auto &cell: speedometerCells) {
        draw(cell);
    }

    // Отображение текущей скорости.
    speedText.setString(cv.from_bytes("Текущая скорость: ") + std::to_string(static_cast<int>(currentSpeed)) + " mph");
    draw(speedText);
}

// Метод обновления шкалы спидометра.
void MainWindow::UpdateSpeedometer() {
    int activeCells = static_cast<int>(currentSpeed / speedIncrement);

    for (int i = 0; i < speedometerCells.size(); ++i) {
        if (i < activeCells) {
            float percent = static_cast<float>(i) / (static_cast<float>(speedometerCells.size()) - 1);
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

// Метод обновления положения дороги.
void MainWindow::UpdateRoad() {
    auto &road1 = sprites[2];
    auto &road2 = sprites[3];

    road1.move(-5 * 1.5f * currentSpeed / 11, 0);  // Двигаем первый спрайт дороги влево.
    road2.move(-5 * 1.5f * currentSpeed / 11, 0);  // Двигаем второй спрайт дороги влево.

    // Если первый спрайт дороги вышел за пределы экрана, перемещаем его вправо за вторым спрайтом.
    if (road1.getPosition().x + road1.getLocalBounds().width * road1.getScale().x < 0) {
        road1.setPosition(road2.getPosition().x + road2.getLocalBounds().width * road2.getScale().x,
                          road1.getPosition().y);
    }

    // Если второй спрайт дороги вышел за пределы экрана, перемещаем его вправо за первым спрайтом.
    if (road2.getPosition().x + road2.getLocalBounds().width * road2.getScale().x < 0) {
        road2.setPosition(road1.getPosition().x + road1.getLocalBounds().width * road1.getScale().x,
                          road2.getPosition().y);
    }
}

// Метод создания и обновления положения бонусов.
void MainWindow::UpdateBonuses() {
    if (isVictory)
        return;

    // Если прошло более трёх секунд с момента последнего бонуса.
    if (bonusTimer.getElapsedTime().asSeconds() > 3.0f) {
        // Сбросить таймер.
        bonusTimer.restart();

        // Проверяем, есть ли уже активный бонус (ускоритель или замедлитель).
        if (hasAccelerator || hasDecelerator) {
            return;  // Если есть, просто выходим из функции без генерации нового бонуса.
        }

        // Генерируем случайное число для выбора бонуса (0 - ускоритель, 1 - замедлитель).
        int bonusType;
        if (isFirstBonus) {
            isFirstBonus = false;
            bonusType = 0;
        } else
            bonusType = rand() % 2;

        // Проверяем историю появления замедлителей.
        bool lastThreeWereDecelerators = false;
        if (deceleratorHistory.size() >= 3) {
            lastThreeWereDecelerators = (deceleratorHistory[deceleratorHistory.size() - 1] &&
                                         deceleratorHistory[deceleratorHistory.size() - 2] &&
                                         deceleratorHistory[deceleratorHistory.size() - 3]);
        }

        // Если последние три были замедлителями, генерируем ускоритель.
        if (lastThreeWereDecelerators) {
            bonusType = 0;  // Ускоритель.
        }

        // Проверяем, чтобы не было двух ускорителей подряд.
        if (bonusType == 0 && !deceleratorHistory.empty() && !deceleratorHistory.back()) {
            // Если последний бонус был ускорителем, генерируем замедлитель.
            bonusType = 1;
        }

        // Определяем положение появления бонуса.
        int lane = rand() % 2;  // Случайный выбор полосы (0 или 1).
        float y = (lane == 0) ? static_cast<float>(getSize().y * 8.25 / 10) : static_cast<float>(getSize().y * 9.8 /
                                                                                                 10);
        float x = static_cast<float>(getSize().x);  // Появление за пределами экрана справа.

        if (bonusType == 0) {
            // Ускоритель.
            hasAccelerator = true;
            acceleratorSprite.setPosition(x, y - static_cast<float>(acceleratorTexture.getSize().y) *
                                                 acceleratorSprite.getScale().y);

            // Обновляем историю появлений.
            deceleratorHistory.push_back(false);  // False для ускорителя.
            // Удаляем первый элемент, если история слишком длинная.
            if (deceleratorHistory.size() > 3) {
                deceleratorHistory.erase(
                        deceleratorHistory.begin());
            }
        } else {
            // Замедлитель.
            hasDecelerator = true;
            int deceleratorIndex = rand() % 3;  // Случайный выбор индекса замедлителя.
            deceleratorSprite.setTexture(deceleratorTextures[deceleratorIndex]);
            deceleratorSprite.setScale(0.4f, 0.4f);
            deceleratorSprite.setPosition(x,
                                          y - static_cast<float>(deceleratorTextures[deceleratorIndex].getSize().y) *
                                              deceleratorSprite.getScale().y);

            // Добавляем текущий бонус в историю.
            deceleratorHistory.push_back(true);  // True для замедлителя.
            // Удаляем первый элемент, если история слишком длинная.
            if (deceleratorHistory.size() > 3) {
                deceleratorHistory.erase(
                        deceleratorHistory.begin());
            }
        }
    }

    // Обновление позиции ускорителя, если он активен.
    if (hasAccelerator) {
        acceleratorSprite.move(-5 * 1.5f * currentSpeed / 11, 0);
        if (acceleratorSprite.getPosition().x + acceleratorSprite.getGlobalBounds().width < 0) {
            hasAccelerator = false;
        }
    }

    // Обновление позиции замедлителя, если он активен.
    if (hasDecelerator) {
        deceleratorSprite.move(-5 * 1.5f * currentSpeed / 11, 0);
        if (deceleratorSprite.getPosition().x + deceleratorSprite.getGlobalBounds().width < 0) {
            hasDecelerator = false;
        }
    }
}

// Метод обновления кадров анимаций.
void MainWindow::UpdateAnimations() {
    if (isVictory) {
        sf::Vector2f deLoreanPos = sprites[1].getPosition();
        fireTraces.emplace_back(fireTexture, sf::Vector2f(deLoreanPos.x - 75, deLoreanPos.y - 30));
        fireTraces.emplace_back(fireTexture, sf::Vector2f(deLoreanPos.x - 75, deLoreanPos.y - 5));
    }

    // Обновление анимации огненного следа от колёс ДеЛориана.
    for (auto &fire: fireTraces) {
        fire.update();
    }

    // Обновление анимации взрыва.
    for (auto &explosion: explosions) {
        explosion.update();
    }
    explosions.erase(
            std::remove_if(
                    explosions.begin(), explosions.end(),
                    [](Explosion &e) { return e.isFinished(); }),
            explosions.end()
    );

    // Обновление анимации молнии.
    for (auto &lightning: lightnings) {
        lightning.update();
    }
    lightnings.erase(
            std::remove_if(
                    lightnings.begin(), lightnings.end(),
                    [](Lightning &l) { return l.isFinished(); }),
            lightnings.end()
    );

    // Обновление положения тучи.
    for (auto &thundercloud: thunderclouds) {
        thundercloud.update(*this, currentSpeed);
    }

    float time = remainingTime - 5 >= 0 ? remainingTime - 5 : 0;
    clockFace->update(time);

    if (isBrownFalling) {
        brownFallSpeed += 0.1f;  // Увеличение скорости падения (имитация гравитации).
        brownSprite.move(0, brownFallSpeed);
        brownSprite.rotate(brownRotationSpeed);  // Вращение при падении.
        if (brownSprite.getPosition().y + brownSprite.getGlobalBounds().height / 2 >=
            this->getSize().y - 300.0) {
            brownSprite.setPosition(brownSprite.getPosition().x,
                                    static_cast<float>(this->getSize().y) -
                                    brownSprite.getGlobalBounds().height / 2 - 300);
            // Доктор Браун упал.
            isBrownFalling = false;
            brownSprite.setRotation(90.0f);
        }
    }

    if (isBrownJumping) {
        float newY = brownSprite.getPosition().y - brownJumpDirection * brownJumpSpeed;
        // Изменение направления, если достигнута верхняя или нижняя граница.
        if (newY <= brownJumpMaxY || newY >= brownJumpMinY) {
            brownJumpDirection = -brownJumpDirection;
        }
        brownSprite.setPosition(brownSprite.getPosition().x, newY);
    }
}

// Метод проверки коллизий.
void MainWindow::CheckCollisions() {
    if (hasAccelerator && sprites[1].getGlobalBounds().intersects(acceleratorSprite.getGlobalBounds())) {
        currentSpeed += speedIncrement;
        maxPlayerSpeed = currentSpeed > maxPlayerSpeed ? currentSpeed : maxPlayerSpeed;

        if (currentSpeed >= maxSpeed) {
            currentSpeed = maxSpeed;
            if (!isVictory) {
                isVictory = true;
                isGameOver = false;
                isDeloreanSpriteMoving = true;

                totalPlayerTime = INITIAL_TIME - remainingTime + 5.0;
                remainingTime = 5;

                curMusic.setVolume(50);
                sounds[0].play();
                sounds[5].play();
            }
        }

        UpdateSpeedometer();
        hasAccelerator = false;

        sounds[2].play();
    }

    if (hasDecelerator && sprites[1].getGlobalBounds().intersects(deceleratorSprite.getGlobalBounds())) {
        currentSpeed -= speedIncrement;
        if (currentSpeed <= 0) {
            currentSpeed = 0;
            totalPlayerTime = INITIAL_TIME - remainingTime + 5.0;
            remainingTime = 5;
        }
        UpdateSpeedometer();
        hasDecelerator = false;

        // Создание взрыва.
        sf::Vector2f deceleratorPosition = deceleratorSprite.getPosition();
        explosions.emplace_back(explosionTexture, deceleratorPosition);

        sounds[1].play();
    }
}

// Метод обновления таймера обратного отсчёта.
void MainWindow::UpdateTimer() {
    float elapsed = countdownClock.getElapsedTime().asSeconds();
    remainingTime -= elapsed;
    countdownClock.restart();

    if (remainingTime <= 5) {
        if (!isVictory && !isGameOver) {
            isGameOver = true;
            curMusic.setVolume(50);
            sounds[0].play();
        }
        if (!isVictory) {
            currentSpeed = 0;
            UpdateSpeedometer();
            if (lightnings.empty())
                lightnings.emplace_back(lightningTexture, sf::Vector2f(537, 0));
            isBrownFalling = true;  // Доктор Браун падает с часовой башни.
        } else {
            UpdateSpeedometer();
            if (lightnings.empty())
                lightnings.emplace_back(lightningTexture, sf::Vector2f(537, 0));
            isBrownJumping = true;  // Доктор Браун прыгает от радости.
        }

    }
    if (remainingTime <= 0) {
        remainingTime = 0;
        quit = true;  // Время вышло, игра окончена.
    }

    float time = remainingTime - 5 >= 0 ? remainingTime - 5 : 0;
    timerText.setString(
            cv.from_bytes("Осталось: ")
            + std::to_string(static_cast<int>(time))
            + " s"
    );
    clockFace->update(time);
}

// Метод отправки ДеЛориана назад в будущее.
void MainWindow::BackToTheFuture() {
    auto &delorean = sprites[1];

    // ДеЛориан уезжает с экрана.
    delorean.move(5 * 0.5f * currentSpeed / 11, 0);
    for (auto &fire: fireTraces) {
        fire.sprite.move(-5 * 1.5f * currentSpeed / 11, 0);
    }
}

// Метод проверки необходимости отрисовки следующего кадра игры.
bool MainWindow::IsItTimeYet(int time) {
    if (time > 25)
        return true;
    return false;
}

// Метод перезапуска таймера обратного отсчёта.
void MainWindow::resetTimer() {
    remainingTime = INITIAL_TIME;  // Обновление оставшегося времени.
    countdownClock.restart();      // Перезапуск таймера.
}

// Метод перезапуска игры.
void MainWindow::reset() {
    resetTimer();  // Перезапуск таймера обратного отсчёта.
    init();        // Инициализация окна игры при перезапуске.
}

// Метод установки иконки приложения.
void MainWindow::setMainWindowIcon() {
    sf::Image icon;
    icon.loadFromFile(ICON_PATH);
    this->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

#pragma clang diagnostic pop