//
// Created by anoso on 22.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_GAMEOVERMENU_H
#define ITIP_CPP_PR_5_HDL_GAMEOVERMENU_H


#include <SFML/Graphics.hpp>
#include <codecvt>
#include "MainWindow.h"

class GameOverMenu {
public:
    GameOverMenu();

    void draw(MainWindow &window, float finalSpeed);

    void PollEvents(MainWindow &window);

private:
    sf::RectangleShape backButton;
    sf::Text gameOverText;
    sf::Text speedText;
    sf::Font headerFont;
    sf::Font textFont;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;
};


#endif //ITIP_CPP_PR_5_HDL_GAMEOVERMENU_H
