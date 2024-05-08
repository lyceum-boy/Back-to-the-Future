#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace sf;

class MainWindow :public RenderWindow
{
    std::vector<Vertex> quad;
    int state = 0;
    std::vector<Texture> images;
    std::vector<Sprite> sprites;
    std::vector <std::string> songs;
    std::vector <SoundBuffer> buf;
    std::vector <Sound> sounds;
    Music curMusic;
    Font font;
    bool quit = false;
    Clock mainTimer;
    Text mainTitle;
public:

    MainWindow(VideoMode vm, std::string str);
    void DrawFrance();
    void DrawJapan();
    void DrawSuperbara(int x, int y);
    void DrawSuperbara();
    void DrawBackground();
    void FlySuperbara();
    void PollEvents();
    bool IsItTimeYet(int time)
    {
        if (time > 25)
            return true;
        return false;
    };

};

MainWindow::MainWindow(VideoMode vm, std::string str) :RenderWindow(vm, str)
{
    setFramerateLimit(60);


    quad.push_back(Vertex({ 310,300 }, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({ 310,400 }, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({ 310,400 }, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({ 510,400 }, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({ 510,400 }, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({ 510,300 }, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({ 510,300 }, Color(0, 0, 0, 255)));
    quad.push_back(Vertex({ 310,300 }, Color(0, 0, 0, 255)));

    Texture tmp;
    if (!tmp.loadFromFile("background.bmp"))
        throw "Error";
    images.push_back(tmp);
    if (!tmp.loadFromFile("Superbara.png"))
        throw "Error";
    images.push_back(tmp);
    if (!tmp.loadFromFile("capysprite.png"))
        throw "Error";
    images.push_back(tmp);

    Sprite bckg;
    bckg.setTexture(images[0]);
    bckg.setScale(getSize().x / bckg.getLocalBounds().width, getSize().y / bckg.getLocalBounds().height);
    sprites.push_back(bckg);
    Sprite capy;
    capy.setTexture(images[1]);
    capy.setScale(0.5, 0.5);
    capy.setPosition(400, 400);
    sprites.push_back(capy);
    capy.setTexture(images[2]);
    capy.setTextureRect(IntRect(0, 0, images[2].getSize().x / 2, images[2].getSize().y));
    capy.setScale(0.35, 0.35);
    sprites.push_back(capy);
    capy.setTextureRect(IntRect(images[2].getSize().x / 2, 0, images[2].getSize().x, images[2].getSize().y));
    capy.setScale(0.35, 0.35);
    sprites.push_back(capy);

    SoundBuffer tmpbuf;
    if (!tmpbuf.loadFromFile("tada.mp3"))
        throw "Error";
    buf.push_back(tmpbuf);
    Sound tmpsound;
    tmpsound.setBuffer(buf[0]);
    sounds.push_back(tmpsound);

    songs.push_back("music.mp3");
    songs.push_back("music2.mp3");
    songs.push_back("music3.mp3");

    if (!font.loadFromFile("OpenSans-SemiBold.ttf"))
        throw "Error";

    mainTitle.setFont(font);
    mainTitle.setCharacterSize(24);
    mainTitle.setFillColor(sf::Color::Green);
    mainTitle.setStyle(sf::Text::Bold);
    mainTitle.setString(sf::String(L"Капибара спешит на помощь!"));
    mainTitle.setPosition(400, 10);
}


void MainWindow::DrawFrance()
{
    draw(quad.data(), 8, Lines);
}

void MainWindow::DrawJapan()
{
    RectangleShape border({ 200,100 });
    border.setOutlineThickness(4);
    border.setOutlineColor(Color::Black);
    border.setFillColor(Color::White);
    border.setPosition(310, 300);
    draw(border);
    CircleShape circle(30);
    circle.setFillColor(Color(188, 0, 45));
    circle.setPosition(380, 320);
    draw(circle);
}

void MainWindow::DrawSuperbara(int x, int y)
{
    int ind = state / 10 + 2;
    sprites[ind].setPosition(x, y);
    draw(sprites[ind]);
    state = (state + 1) % 20;
}

void MainWindow::DrawBackground()
{
    draw(sprites[0]);
    draw(mainTitle);
}

void MainWindow::DrawSuperbara()
{
    draw(sprites[1]);
}

void MainWindow::FlySuperbara()
{
    //DrawBackground();
    if (curMusic.openFromFile(songs[rand() % 3]))
        curMusic.play();

    int w = sprites[2].getLocalBounds().width * 0.35;
    int h = sprites[2].getLocalBounds().height * 0.35;


    int x = -w;
    int y = getSize().y + h;

    while (!quit)
    {
        PollEvents();
        int time = mainTimer.getElapsedTime().asMilliseconds();
        if (curMusic.getStatus() == SoundSource::Status::Stopped)
        {
            if (curMusic.openFromFile(songs[rand() % 3]))
                curMusic.play();
        }
        if (IsItTimeYet(time))
        {
            DrawBackground();
            x++;
            y--;

            if (x > (int)(getSize().x + w))
                x = -w;
            if (y < -h)
                y = getSize().y + h;

            DrawSuperbara(x, y);
            display();
            clear();
            mainTimer.restart();
        }
    }

}

void MainWindow::PollEvents()
{
    sf::Event event;
    while (pollEvent(event))
    {
        switch (event.type)
        {
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

int main()
{
    srand(time(NULL));
    MainWindow window(VideoMode(1024, 768), "SFML can into Capybaras!");

    while (window.isOpen())
    {
        /*     Event event;
             while (window.pollEvent(event))
             {
                 if (event.type == Event::Closed)
                     window.close();
             }
        */
        window.clear(Color::White);
        //window.DrawFrance();
        //window.DrawJapan();
        //window.DrawBackground();
        //window.DrawSuperbara();
        //window.display();
        window.FlySuperbara();
        window.close();
    }
    return 0;
}
