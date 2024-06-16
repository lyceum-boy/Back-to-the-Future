//
// Created by anoso on 17.05.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_MAINWINDOW_H
#define ITIP_CPP_PR_5_HDL_MAINWINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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


public:
    MainWindow(VideoMode vm, const std::string &str);

    void DrawBackground();

    void DrawSpeedometer();

    void UpdateSpeedometer();

    void UpdateRoad(); // Декларация метода обновления дороги

    void PollEvents();

    void UpdateBonuses(); // Декларация метода обновления бонусов

    void CheckCollisions(); // Декларация метода проверки коллизий

    static bool IsItTimeYet(int time) {
        if (time > 25)
            return true;
        return false;
    };
};


#endif //ITIP_CPP_PR_5_HDL_MAINWINDOW_H
