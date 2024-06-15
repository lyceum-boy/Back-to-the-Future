//
// Created by anoso on 17.05.2024.
//

#include "MainWindow.h"

#include "DeLorian.h"

#define FONT_1_PATH "static/fonts/OpenSans-Regular.ttf"
#define FONT_2_PATH "static/fonts/OpenSans-SemiBold.ttf"

#define BACKGROUND_PATH "static/img/AA0774E2-0E43-11EF-B578-0AFFCD66D3D3.jpg"

#define MUSIC_1_PATH "static/music/music.mp3"
#define MUSIC_2_PATH "static/music/music2.mp3"
#define MUSIC_3_PATH "static/music/music3.mp3"

#define SOUND_PATH "static/sounds/tada.mp3"

#define DELORIAN_SPRITE_PATH "static/sprites/img.png"

MainWindow::MainWindow(VideoMode vm, const std::string &str) : RenderWindow(vm, str) {
    setFramerateLimit(60);

    quad.push_back(Vertex({310, 300}, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({310, 400}, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({310, 400}, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({510, 400}, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({510, 400}, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({510, 300}, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({510, 300}, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({310, 300}, Color(0, 0, 0, 255)));

    Texture tmp;
    if (!tmp.loadFromFile(BACKGROUND_PATH))
        throw std::runtime_error("Error");
    images.push_back(tmp);
    if (!tmp.loadFromFile("static/img/Superbara.png"))
        throw std::runtime_error("Error");
    images.push_back(tmp);
    if (!tmp.loadFromFile(DELORIAN_SPRITE_PATH))
        throw std::runtime_error("Error");
    images.push_back(tmp);

    Sprite background;
    background.setTexture(images[0]);
    background.setScale(
            (float) sf::RenderWindow::getSize().x / background.getLocalBounds().width,
            (float) sf::RenderWindow::getSize().y / background.getLocalBounds().height
    );
    sprites.push_back(background);

    Sprite delorian;

    delorian.setTexture(images[1]);
    delorian.setScale(0.5, 0.5);
    delorian.setPosition(400, 400);
    sprites.push_back(delorian);

    delorian.setTexture(images[2]);
    delorian.setTextureRect(IntRect(0, 0, images[2].getSize().x / 2, images[2].getSize().y));
    delorian.setScale(0.35, 0.35);
    sprites.push_back(delorian);

    delorian.setTextureRect(IntRect(images[2].getSize().x / 2, 0, images[2].getSize().x, images[2].getSize().y));
    delorian.setScale(0.35, 0.35);
    sprites.push_back(delorian);

    SoundBuffer tmp_buffer;
    if (!tmp_buffer.loadFromFile(SOUND_PATH))
        throw std::runtime_error("Error");
    buf.push_back(tmp_buffer);
    Sound tmp_sound;
    tmp_sound.setBuffer(buf[0]);
    sounds.push_back(tmp_sound);

    songs.emplace_back(MUSIC_1_PATH);
    songs.emplace_back(MUSIC_2_PATH);
    songs.emplace_back(MUSIC_3_PATH);

    if (!font.loadFromFile(FONT_2_PATH))
        throw std::runtime_error("Error");

    mainTitle.setFont(font);
    mainTitle.setCharacterSize(24);
    mainTitle.setFillColor(sf::Color::Green);
    mainTitle.setStyle(sf::Text::Bold);
    mainTitle.setString(sf::String(L"Капибара спешит на помощь!"));
    mainTitle.setPosition(400, 10);
}

void MainWindow::DrawBackground() {
    draw(sprites[0]);
    draw(mainTitle);
}

void MainWindow::PollEvents() {
    sf::Event event{};
    while (pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                quit = true;
                break;
            case sf::Event::KeyPressed:
                if (event.key.scancode == Keyboard::Scan::Escape)
                    quit = true;
                if (event.key.scancode == Keyboard::Scan::Space)
                    sounds[0].play();
                if (event.key.scancode == Keyboard::Scan::Tab)
                    if (curMusic.openFromFile(songs[rand() % 3]))
                        curMusic.play();
                if (event.key.scancode == Keyboard::Scan::Enter)
                    if (curMusic.getStatus() == SoundSource::Status::Playing)
                        curMusic.pause();
                    else if (curMusic.getStatus() == SoundSource::Status::Paused)
                        curMusic.play();
                break;
            default:
                break;
        }
    }
}
