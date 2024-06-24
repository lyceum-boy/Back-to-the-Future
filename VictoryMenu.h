//
// Created by anoso on 22.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_VICTORYMENU_H
#define ITIP_CPP_PR_5_HDL_VICTORYMENU_H


#include <SFML/Graphics.hpp>
#include <codecvt>
#include "MainWindow.h"

class VictoryMenu {
public:
    VictoryMenu();

    void draw(MainWindow &window, int totalTime);

    void PollEvents(MainWindow &window);

private:
    sf::RectangleShape backButton;
    sf::Text victoryText;
    sf::Text timeText;
    sf::Font headerFont;
    sf::Font textFont;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;
};


#endif //ITIP_CPP_PR_5_HDL_VICTORYMENU_H
