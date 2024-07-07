//
// Created by anoso on 17.05.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_MAINWINDOW_H
#define ITIP_CPP_PR_5_HDL_MAINWINDOW_H

// Используется для конвертации строки в UTF-8 для отрисовки кириллических символов.
#include <codecvt>

// Модуль для работы с графикой в библиотеке SFML.
#include <SFML/Graphics.hpp>
// Модуль для работы с аудио в библиотеке SFML.
#include <SFML/Audio.hpp>

#include "ClockFace.h"     // Класс циферблата стрелочных часов.
#include "Explosion.h"     // Класс анимации взрыва.
#include "FireTrace.h"     // Класс анимации огненного следа от колёс.
#include "Lightning.h"     // Класс анимации молнии.
#include "Thundercloud.h"  // Класс грозовой тучи.

// Игровые константы.
#define INITIAL_TIME 100  // Время таймера обратного отсчёта.
#define INITIAL_SPEED 8   // Начальная скорость.
#define MAXIMAL_SPEED 88  // Максимальная скорость.

using namespace sf;  // Пространство имён библиотеки SFML.


// Класс основного окна игры.
class MainWindow : public RenderWindow {
public:
    std::vector<Texture> images;     // Вектор текстур.
    std::vector<Sprite> sprites;     // Вектор спрайтов.
    std::vector<std::string> songs;  // Вектор путей к фоновой музыке.
    std::vector<SoundBuffer> buf;    // Вектор буферов звуков.
    std::vector<Sound> sounds;       // Вектор звуков.

    Music curMusic;   // Текущая фоновая музыка.
    Font textFont;    // Шрифт основного текста.
    Clock mainTimer;  // Таймер отрисовки кадров.

    // Поля, связанные со скоростью ДеЛориана.

    Text speedText;  // Текущая скорость.

    // Шкала спидометра.
    std::vector<RectangleShape> speedometerCells;

    float currentSpeed = INITIAL_SPEED;
    const float maxSpeed = MAXIMAL_SPEED;
    const float speedIncrement = INITIAL_SPEED;

    // Поля для ускоряющих и тормозящих бонусов.

    Texture acceleratorTexture;
    Sprite acceleratorSprite;

    std::vector<Texture> deceleratorTextures;
    Sprite deceleratorSprite;

    // История появления ускоряющих и тормозящих бонусов.
    std::vector<bool> deceleratorHistory;

    bool hasAccelerator = false;  // Флаг наличия на экране ускорителя.
    bool hasDecelerator = false;  // Флаг наличия на экране замедлителя.

    Clock bonusTimer;  // Таймер появления бонусов.

    bool isFirstBonus = true;  // Первый бонус в игре всегда ускоритель.

    // Поля, связанные со временем.

    Clock countdownClock;   // Таймер обратного отсчёта.
    float remainingTime{};  // Оставшееся время в секундах.

    Text timerText;         // Оставшееся время.

    // Поля для анимаций.

    Texture explosionTexture;
    std::vector<Explosion> explosions;

    Texture fireTexture;
    std::vector<FireTrace> fireTraces;

    Texture lightningTexture;
    std::vector<Lightning> lightnings;

    // Инициализация стрелочных часов.
    ClockFace *clockFace{};

    Texture thundercloudTexture;
    std::vector<Thundercloud> thunderclouds;

    // Поля, связанные с доктором Эмметом Брауном.

    Texture brownTexture;
    Sprite brownSprite;

    bool isBrownFalling = false;      // Флаг падения.
    float brownFallSpeed = 1.0f;      // Скорость падения.
    float brownRotationSpeed = 5.0f;  // Скорость вращения.

    bool isBrownJumping = false;      // Флаг падения.
    float brownJumpSpeed = 2.0f;      // Скорость прыжка.
    float brownJumpDirection = 1.0f;  // Направление движения (1 - вверх, -1 - вниз).
    float brownJumpMaxY = brownSprite.getPosition().y - 20;  // Верхняя граница движения.
    float brownJumpMinY = brownSprite.getPosition().y;       // Нижняя граница движения.

    // Переменные, связанные с состоянием игры и окна.

    bool isGameOver = false;  // Флаг поражения.
    bool isVictory = false;   // Флаг победы.

    /* Флаг нахождения ДеЛориана на верхней полосе дороги
     * для корректного проигрывания звука drift.mp3. */
    bool deLoreanOnFirstRoad = true;

    // Флаг отправки ДеЛориана назад в будущее.
    bool isDeloreanSpriteMoving{};

    // Флаг полноэкранного режима.
    bool isFullscreen = false;

    // Счётчики очков для экрана окончания игры.
    float maxPlayerSpeed{};   // Максимальная набранная скорость.
    float totalPlayerTime{};  // Затраченное пользователем время.

    bool quit = false;  // Флаг завершения игры.

    // Конвертер строки для отрисовки кириллических символов в UTF-8.
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;

public:
    MainWindow(VideoMode vm, const std::string &str, int i);

    // Метод инициализации окна игры при запуске и перезапуске.
    void init();

    // Метод создания грозовых туч в небе над дорогой.
    void CreateThunderclouds();

    // Метод отрисовки фона и всех игровых объектов.
    void DrawBackground();

    // Метод отрисовки спидометра на экране.
    void DrawSpeedometer();

    // Метод обновления шкалы спидометра.
    void UpdateSpeedometer();

    // Метод обновления положения дороги.
    void UpdateRoad();

    // Метод создания и обновления положения бонусов.
    void UpdateBonuses();

    // Метод обновления кадров анимаций.
    void UpdateAnimations();

    // Метод проверки коллизий.
    void CheckCollisions();

    // Метод обновления таймера обратного отсчёта.
    void UpdateTimer();

    // Метод отправки ДеЛориана назад в будущее.
    void BackToTheFuture();

    // Метод проверки необходимости отрисовки следующего кадра игры.
    static bool IsItTimeYet(int time);

    // Метод перезапуска таймера обратного отсчёта.
    void resetTimer();

    // Метод перезапуска игры.
    void reset();

    // Метод установки иконки приложения.
    void setMainWindowIcon();
};


#endif //ITIP_CPP_PR_5_HDL_MAINWINDOW_H
