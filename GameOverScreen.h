//
// Created by anoso on 22.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_GAMEOVERSCREEN_H
#define ITIP_CPP_PR_5_HDL_GAMEOVERSCREEN_H

#include <codecvt>

#include <SFML/Graphics.hpp>

#include "EndScreen.h"
#include "MainWindow.h"


class GameOverScreen : public EndScreen {
private:
    RectangleShape menuButton;

    Text gameOverText;
    Text speedText;

    Font headerFont;
    Font textFont;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;

    void draw(MainWindow &window, float maxSpeed) override;

public:
    GameOverScreen();

    void PollEvents(MainWindow &window, float maxPlayerSpeed) override;
};


#endif //ITIP_CPP_PR_5_HDL_GAMEOVERSCREEN_H
