//
// Created by anoso on 17.05.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_MAINWINDOW_H
#define ITIP_CPP_PR_5_HDL_MAINWINDOW_H

#include <codecvt>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ClockFace.h"
#include "Explosion.h"
#include "FireAnimation.h"
#include "Lightning.h"
#include "Thundercloud.h"

using namespace sf;


class MainWindow : public RenderWindow {
public:
    std::vector<Texture> images;     // Вектор текстур.
    std::vector<Sprite> sprites;     // Вектор спрайтов.
    std::vector<std::string> songs;  // Вектор фоновой музыки.
    std::vector<SoundBuffer> buf;
    std::vector<Sound> sounds;       // Вектор звуков.

    Music curMusic;
    Font font;
    Clock mainTimer;
    Text mainTitle;

    bool quit = false;

    sf::Text speedText;

    std::vector<RectangleShape> speedometerCells;
    float maxPlayerSpeed{};
    float currentSpeed{};  // Current speed in km/h
    const float maxSpeed = 88.0f;  // Maximum speed in km/h
    const float speedIncrement = 8.0f;  // Speed increment in km/h

    // Новые переменные для бонусов
    Texture acceleratorTexture;
    Sprite acceleratorSprite;
    std::vector<Texture> deceleratorTextures;
    Sprite deceleratorSprite;

    std::vector<bool> deceleratorHistory;  // История появления замедлителей и ускорителей

    bool hasAccelerator = false;
    bool hasDecelerator = false;

    Clock bonusTimer;

    bool isFirstBonus = true;

    Clock countdownClock;      // Clock to track elapsed time
    float remainingTime{};       // Remaining time in seconds
    Text timerText;            // Text to display the timer

    sf::Texture explosionTexture;
    std::vector<Explosion> explosions;

    sf::Texture lightningTexture;
    std::vector<Lightning> lightnings;

    ClockFace* clockFace{};

    Texture thundercloudTexture;
    std::vector<Thundercloud> thunderclouds;

    sf::Texture characterTexture;
    sf::Sprite characterSprite;
    bool isCharacterFalling = false; // Track falling state
    float characterFallSpeed = 0.0f; // Speed of the fall
    float characterRotationSpeed = 0.0f; // Speed of rotation

    bool isCharacterFlying{};
    float characterFlySpeed{};
    float characterFlyDirection{};
    float characterFlyMaxY{};
    float characterFlyMinY{};

    bool isGameOver = false;
    bool isVictory = false;

    std::vector<FireAnimation> fireAnimations;
    sf::Texture fireTexture;

    bool isDeloreanSpriteMoving = false;

    bool wasThunder = false;
    bool isFullscreen = false;

    bool deLoreanOnFirstRoad = true;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;

    float totalPlayerTime{};


public:
    MainWindow(VideoMode vm, const std::string &str, int i);

    void init();

    void DrawBackground();

    void DrawSpeedometer();

    void UpdateSpeedometer();

    void UpdateRoad(); // Декларация метода обновления дороги

    void UpdateBonuses(); // Декларация метода обновления бонусов

    void UpdateAnimations();

    void CheckCollisions(); // Декларация метода проверки коллизий

    static bool IsItTimeYet(int time) {
        if (time > 25)
            return true;
        return false;
    };

    void UpdateTimer(); // Update the timer

    void resetTimer() {
        remainingTime = 100.0f; // Reset the timer to 100 seconds
        countdownClock.restart(); // Restart the clock
    }

    void reset() {
        resetTimer();
        init();
    }
    void LoadTextures();
    void CreateThunderclouds();

    void DeLoreanAway();
};


#endif //ITIP_CPP_PR_5_HDL_MAINWINDOW_H
