//
// Created by anoso on 24.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_ENDSCREEN_H
#define ITIP_CPP_PR_5_HDL_ENDSCREEN_H

#include <codecvt>

#include <SFML/Graphics.hpp>

#include "MainWindow.h"

using namespace sf;


class EndScreen {
private:
    RectangleShape backButton;

    Text victoryText;
    Text timeText;

    Font headerFont;
    Font textFont;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;

    void draw(MainWindow &window, int totalTime);

public:
    EndScreen() = default;

    virtual void PollEvents(MainWindow &window);
};


#endif //ITIP_CPP_PR_5_HDL_ENDSCREEN_H
