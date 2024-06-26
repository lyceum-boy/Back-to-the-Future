//
// Created by anoso on 21.06.2024.
//

#include "MainMenu.h"

#include "MainWindow.h"

#define HEADER_FONT_PATH "static/fonts/backtothefuture2002_regular.ttf"
#define TEXT_FONT_PATH "static/fonts/Industry-Bold_RUS.ttf"
#define MUSIC_PATH "static/music/30959.mp3"
#define SUBMENU_BACKGROUND_PATH "static/img/submenu_background.jpg"

MainMenu::MainMenu() {
    songs.emplace_back(MUSIC_PATH);
}

void
MainMenu::displayMainMenu(MainWindow &window, std::vector<RectangleShape> &buttons, std::vector<Text> &buttonLabels) {
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("static/img/main_menu_background.jpg")) {
        throw std::runtime_error("Failed to load background texture");
    }
    Sprite background(backgroundTexture);
    background.setScale(
            (float) window.getSize().x / background.getLocalBounds().width,
            (float) window.getSize().y / background.getLocalBounds().height
    );

    Font font;
    if (!font.loadFromFile(TEXT_FONT_PATH)) {
        throw std::runtime_error("Failed to load headerFont");
    }

    if (buttons.empty() && buttonLabels.empty()) {
        std::vector<std::string> options = {"Играть!", "Как играть", "Об игре"};
        for (int i = 0; i < options.size(); ++i) {
            RectangleShape button(Vector2f(200, 50));
            button.setOutlineThickness(2);
            button.setOutlineColor(Color::White);
            buttons.push_back(button);

            Text label(cv.from_bytes(options[i]), font, 30);
            label.setFillColor(Color::White);
//            label.setPosition(
//                    button.getPosition().x + (button.getSize().x - label.getLocalBounds().width) / 2,
//                    button.getPosition().y + (button.getSize().y - label.getLocalBounds().height) / 2 - 5
//            );
            buttonLabels.push_back(label);
        }
    }

    window.draw(background);

    Vector2i mousePos = Mouse::getPosition(window);
    for (int i = 0; i < buttons.size(); ++i) {
        if (buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            buttons[i].setFillColor(Color(0, 255, 0, 150)); // Полупрозрачный ярко-зеленый
            buttons[i].setSize(Vector2f(220, 55)); // Увеличить размер
            buttons[i].setPosition(15, window.getSize().y - 322.5 + i * 70);
            buttonLabels[i].setPosition(
                    buttons[i].getPosition().x + (buttons[i].getSize().x - buttonLabels[i].getLocalBounds().width) / 2 -
                    12.5,
                    buttons[i].getPosition().y +
                    (buttons[i].getSize().y - buttonLabels[i].getLocalBounds().height) / 2 - 15
            );
            buttonLabels[i].setScale(1.2, 1.2);
        } else {
            buttons[i].setFillColor(Color(125, 125, 125, 150)); // Полупрозрачный черный
            buttons[i].setSize(Vector2f(200, 50)); // Обычный размер
            buttons[i].setPosition(25, window.getSize().y - 320 + i * 70);

            buttonLabels[i].setPosition(
                    buttons[i].getPosition().x + (buttons[i].getSize().x - buttonLabels[i].getLocalBounds().width) / 2,
                    buttons[i].getPosition().y +
                    (buttons[i].getSize().y - buttonLabels[i].getLocalBounds().height) / 2 - 10
            );
            buttonLabels[i].setScale(1.0, 1.0);

        }
        window.draw(buttons[i]);
        window.draw(buttonLabels[i]);
    }

    window.display();
}

void MainMenu::drawBackButton(MainWindow &window) {
    Font font;
    if (!font.loadFromFile(TEXT_FONT_PATH)) {
        throw std::runtime_error("Failed to load headerFont");
    }

    // Add back button to buttons and buttonLabels
    backButton.setSize(Vector2f(200, 50));
    backButton.setOutlineThickness(2);
    backButton.setOutlineColor(Color::White);

    Text backLabel(cv.from_bytes("Назад"), font, 30);
    backLabel.setFillColor(Color::White);

    Vector2i mousePos = Mouse::getPosition(window);
    if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        backButton.setFillColor(Color(0, 255, 0, 150)); // Полупрозрачный ярко-зеленый
        backButton.setSize(Vector2f(220, 55)); // Увеличить размер
        backButton.setPosition(40, window.getSize().y - 102.5);
        backLabel.setPosition(
                backButton.getPosition().x + (backButton.getSize().x - backLabel.getLocalBounds().width) / 2 - 10,
                backButton.getPosition().y + (backButton.getSize().y - backLabel.getLocalBounds().height) / 2 - 10
        );
        backLabel.setScale(1.2, 1.2);
    } else {
        backButton.setFillColor(Color(125, 125, 125, 150)); // Полупрозрачный черный
        backButton.setSize(Vector2f(200, 50)); // Обычный размер
        backButton.setPosition(50, window.getSize().y - 100);
        backLabel.setPosition(
                backButton.getPosition().x + (backButton.getSize().x - backLabel.getLocalBounds().width) / 2,
                backButton.getPosition().y + (backButton.getSize().y - backLabel.getLocalBounds().height) / 2 - 5
        );
        backLabel.setScale(1.0, 1.0);
    }

    window.draw(backButton);
    window.draw(backLabel);
    window.display();
}

void MainMenu::showHowToPlay(MainWindow &window) {
    Font font, header_font;
    font.loadFromFile(TEXT_FONT_PATH);
    header_font.loadFromFile(HEADER_FONT_PATH);

    // Загрузка текстуры фона
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(SUBMENU_BACKGROUND_PATH)) {
        throw std::runtime_error("Failed to load background texture");
    }
    Sprite background(backgroundTexture);
    background.setScale(
            (float) window.getSize().x / background.getLocalBounds().width,
            (float) window.getSize().y / background.getLocalBounds().height
    );
    window.draw(background);

    // Отрисовка темного полупрозрачного прямоугольника
    RectangleShape darkOverlay(Vector2f(window.getSize().x - 40, window.getSize().y - 40));
    darkOverlay.setFillColor(Color(0, 0, 0, 180)); // Черный с полупрозрачностью 180
    darkOverlay.setPosition(20, 20); // Отступ 20 пикселей от каждого края
    window.draw(darkOverlay);

    // Отрисовка заголовка "Об игре"
    Text aboutTitle(cv.from_bytes("как играть"), header_font, 50);
    aboutTitle.setFillColor(Color::White); // Белый цвет текста
    aboutTitle.setPosition(315, 50);
    window.draw(aboutTitle);

    // Отрисовка описания игры
    Text gameDescription(
            cv.from_bytes(
                    "Перемещайте ДеЛориан по двум полосам дороги, собирая \n"
                    "ускоряющие его бонусы (зелёные канистры с радиоактивным \n"
                    "топливом). На дороге много препятствий! Старайтесь избегать \n"
                    "столкновения с тормозящими бонусами: камнями, заборами и \n"
                    "дорожными конусами, ведь если не успеть разогнаться до 88 миль \n"
                    "в час до момента, когда стрелки часов пробьют полночь, \n"
                    "доктор Браун упадёт и вернуться назад в будущее не удастся!"
            ),
            font,
            30
    );
    gameDescription.setFillColor(Color::White);
    gameDescription.setPosition(40, 125); // Позиция описания игры
    window.draw(gameDescription);

    // Отрисовка заголовка "Об игре"
    Text developerTitle(cv.from_bytes("управление"), header_font, 50);
    developerTitle.setFillColor(Color::White); // Белый цвет текста
    developerTitle.setPosition(285, 425);
    window.draw(developerTitle);

    // Отрисовка информации о разработчике
    Text developerInfo(
            cv.from_bytes(
                    "[PgUp] или [W]: переместить ДеЛориан на верхнюю дорогу; \n"
                    "[PgDn] или [S]: переместить ДеЛориан на нижнюю дорогу; \n"
                    "[Esc]: назад / выход; \n"
                    "[F]: переход в полноэкранный режим."
    ), font, 30);
    developerInfo.setFillColor(Color::White);
    developerInfo.setPosition(40, 500); // Позиция информации о разработчике
    window.draw(developerInfo);

    drawBackButton(window); // Рисуем кнопку "Назад"
}

void MainMenu::showAbout(MainWindow &window) {
    Font font, header_font;
    font.loadFromFile(TEXT_FONT_PATH);
    header_font.loadFromFile(HEADER_FONT_PATH);

    // Загрузка текстуры фона
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(SUBMENU_BACKGROUND_PATH)) {
        throw std::runtime_error("Failed to load background texture");
    }
    Sprite background(backgroundTexture);
    background.setScale(
            (float) window.getSize().x / background.getLocalBounds().width,
            (float) window.getSize().y / background.getLocalBounds().height
    );
    window.draw(background);

    // Отрисовка темного полупрозрачного прямоугольника
    RectangleShape darkOverlay(Vector2f(window.getSize().x - 40, window.getSize().y - 40));
    darkOverlay.setFillColor(Color(0, 0, 0, 180)); // Черный с полупрозрачностью 180
    darkOverlay.setPosition(20, 20); // Отступ 20 пикселей от каждого края
    window.draw(darkOverlay);

    // Отрисовка заголовка "Об игре"
    Text aboutTitle(cv.from_bytes("об игре"), header_font, 50);
    aboutTitle.setFillColor(Color::White); // Белый цвет текста
    aboutTitle.setPosition(375, 50);
    window.draw(aboutTitle);

    // Отрисовка описания игры
    Text gameDescription(
            cv.from_bytes(
                    "Мини-игра по мотивам «Назад в будущее»: часы на старой ратуше \n"
                    "вот-вот поразит молния. Эммет Браун забрался на них, чтобы \n"
                    "провести важный эксперимент. Внизу Марти МакФлай едет на \n"
                    "машине, собирая ускоряющие или тормозящие ДеЛориан бонусы. \n"
                    "Нужно успеть разогнаться до 88 миль в час до момента, когда \n"
                    "стрелки часов пробьют полночь и доктор Браун упадёт."
            ),
            font,
            30
    );
    gameDescription.setFillColor(Color::White);
    gameDescription.setPosition(40, 125); // Позиция описания игры
    window.draw(gameDescription);

    // Отрисовка заголовка "Об игре"
    Text developerTitle(cv.from_bytes("о разработчике"), header_font, 50);
    developerTitle.setFillColor(Color::White); // Белый цвет текста
    developerTitle.setPosition(225, 400);
    window.draw(developerTitle);

    // Отрисовка информации о разработчике
    Text developerInfo(
            cv.from_bytes(
                    "Разработчик: студент группы О737Б кафедры О7 \n"
                    "«Информационные системы и программная инженерия» \n"
                    "БГТУ «ВОЕНМЕХ» им. Д. Ф. Устинова Аносов Илья Борисович"
            ), font, 30);
    developerInfo.setFillColor(Color::White);
    developerInfo.setPosition(40, 475); // Позиция информации о разработчике
    window.draw(developerInfo);

    // Отрисовка информации о разработчике
    Text developerInfo1(
            cv.from_bytes(
                    "Контакты: o737b04@voenmeh.ru"
            ), font, 30);
    developerInfo1.setFillColor(Color::White);
    developerInfo1.setPosition(40, 600); // Позиция информации о разработчике
    window.draw(developerInfo1);

    drawBackButton(window); // Рисуем кнопку "Назад"
}
