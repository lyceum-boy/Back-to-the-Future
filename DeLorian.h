//
// Created by anoso on 17.05.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_DELORIAN_H
#define ITIP_CPP_PR_5_HDL_DELORIAN_H

#include "MainWindow.h"


class DeLorian {

public:
    DeLorian();

    static void accelerate(MainWindow &window);

    static void draw(MainWindow &window, int x, int y);
};


#endif //ITIP_CPP_PR_5_HDL_DELORIAN_H
