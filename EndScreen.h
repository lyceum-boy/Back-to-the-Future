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
    virtual void draw(MainWindow &window, float score) = 0;

public:
    EndScreen() = default;

    virtual void PollEvents(MainWindow &window, float score) = 0;
};


#endif //ITIP_CPP_PR_5_HDL_ENDSCREEN_H
