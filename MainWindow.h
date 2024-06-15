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
    std::vector<Texture> images;
    std::vector<Sprite> sprites;
    std::vector<std::string> songs;
    std::vector<SoundBuffer> buf;
    std::vector<Sound> sounds;

    Music curMusic;
    Font font;
    Clock mainTimer;
    Text mainTitle;

    int state = 0;
    bool quit = false;

public:
    MainWindow(VideoMode vm, const std::string &str);

    void DrawBackground();

    void PollEvents();

    bool IsItTimeYet(int time) {
        if (time > 25)
            return true;
        return false;
    };

};


#endif //ITIP_CPP_PR_5_HDL_MAINWINDOW_H
