//
// Created by anoso on 21.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_MAINMENU_H
#define ITIP_CPP_PR_5_HDL_MAINMENU_H

#include <codecvt>

#include "MainWindow.h"


class MainMenu {
public:
    std::vector<std::string> songs;

    Sprite background;

    Music curMusic;
    Font font;
    Clock mainTimer;
    Text mainTitle;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;

public:
    RectangleShape backButton;
public:
    MainMenu();

    void showHowToPlay(MainWindow &window);

    void showAbout(MainWindow &window);

    void displayMainMenu(MainWindow &window, std::vector<RectangleShape> &buttons, std::vector<Text> &buttonLabels);

    void drawBackButton(MainWindow &window);
};


#endif //ITIP_CPP_PR_5_HDL_MAINMENU_H
