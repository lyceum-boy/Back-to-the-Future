//
// Created by anoso on 16.06.2024.
//

#ifndef ITIP_CPP_PR_5_HDL_DELOREAN_H
#define ITIP_CPP_PR_5_HDL_DELOREAN_H

#include "MainWindow.h"  // Класс главного окна программы.


// Класс ДеЛориана, описывающий логику игрового процесса.
class DeLorean {
public:
    DeLorean() = default;

    // Метод запуска ДеЛориана и игрового процесса.
    static void accelerate(MainWindow &window);
};


#endif //ITIP_CPP_PR_5_HDL_DELOREAN_H
