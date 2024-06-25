//
// Created by anoso on 22.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_VICTORYSCREEN_H
#define ITIP_CPP_PR_5_HDL_VICTORYSCREEN_H

#include <codecvt>

#include <SFML/Graphics.hpp>

#include "EndScreen.h"
#include "MainWindow.h"


class VictoryScreen : public EndScreen {
private:
    RectangleShape menuButton;

    Text victoryText;
    Text timeText;

    Font headerFont;
    Font textFont;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;

    void draw(MainWindow &window, float totalTime) override;

public:
    VictoryScreen();

    void PollEvents(MainWindow &window, float totalPLayerTime) override;
};


#endif //ITIP_CPP_PR_5_HDL_VICTORYSCREEN_H
