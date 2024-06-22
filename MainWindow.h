//
// Created by anoso on 17.05.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_MAINWINDOW_H
#define ITIP_CPP_PR_5_HDL_MAINWINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Explosion.h"
#include "Lightning.h"
#include "ClockFace.h"
#include "Thundercloud.h"

using namespace sf;


class MainWindow : public RenderWindow {
public:
    std::vector<Vertex> quad;
    std::vector<Texture> images;  // Вектор текстур.
    std::vector<Sprite> sprites;  // Вектор спрайтов.
    std::vector<std::string> songs;
    std::vector<SoundBuffer> buf;
    std::vector<Sound> sounds;

    Music curMusic;
    Font font;
    Clock mainTimer;
    Text mainTitle;

    int state = 0;
    bool quit = false;

    sf::Text speedText;

    std::vector<RectangleShape> speedometerCells;
    float currentSpeed;  // Current speed in km/h
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
    float remainingTime;       // Remaining time in seconds
    Text timerText;            // Text to display the timer

    sf::Texture explosionTexture;
    std::vector<Explosion> explosions;

    sf::Texture lightningTexture;
    std::vector<Lightning> lightnings;

    ClockFace* clockFace;

    Texture thundercloudTexture;
    std::vector<Thundercloud> thunderclouds;

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
};


#endif //ITIP_CPP_PR_5_HDL_MAINWINDOW_H
