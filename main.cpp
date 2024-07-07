/* Аносов Илья Борисович
 * Группа О737Б
 * Информационные технологии и программирование (ИТиП)
 * Практическая работа №5. Графика
 * Повышенный уровень сложности
 * Вариант 4
 * Задание 3 */

/* Создать мини-игру по мотивам фильма «Назад в будущее»: часы на старой ратуше вот-вот поразит молния.
 * Эммет Браун забрался на них, чтобы провести важный эксперимент.
 * Внизу Марти МакФлай едет на машине, собирая по дороге ускоряющие или тормозящие ДеЛориан бонусы.
 * Необходимо успеть разогнаться до 88 миль в час до момента, когда стрелки часов пробьют полночь и доктор Браун упадёт.
 * Часы с доктором Брауном являются фоном для сцены. */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include <vector>
#include <cstdlib>
#include <ctime>

#include "MainWindow.h"  // Класс главного окна программы.
#include "MainMenu.h"    // Класс меню игры.
#include "DeLorean.h"    // Класс ДеЛориана, логика игрового процесса.

using namespace sf;  // Пространство имён библиотеки SFML.

// Состояние окна.
enum class GameState {
    MainMenu,   // Главное меню.
    Playing,    // Игра.
    HowToPlay,  // Подменю "Как играть".
    About       // Подменю "Об игре".
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    srand(time(nullptr));  // Инициализация генератора случайных чисел.

    MainWindow window(
            VideoMode(1024, 768),
            "Back to the Future",
            sf::Style::Titlebar | sf::Style::Close
    );

    // Загрузка иконки окна мини-игры.
    window.setMainWindowIcon();

    // Установка начального состояния игры - главного меню.
    GameState gameState = GameState::MainMenu;

    std::vector<RectangleShape> buttons;  // Вектор для хранения кнопок.
    std::vector<Text> buttonLabels;       // Вектор для хранения названий кнопок.

    MainMenu menu;  // Объект, создающий в окне главное меню.

    menu.curMusic.setVolume(75);

    // Основной цикл приложения.
    while (window.isOpen()) {
        window.clear(Color::White);

        switch (gameState) {
            case GameState::MainMenu:
                // Если играет музыка игры, остановить её.
                if (window.curMusic.getStatus() == SoundSource::Status::Playing)
                    window.curMusic.stop();
                // Отрисовка Главного меню в окне мини-игры.
                menu.displayMainMenu(window, buttons, buttonLabels);
                break;
            case GameState::Playing:
                menu.curMusic.stop();             // Остановка музыки Главного меню.
                DeLorean::accelerate(window);  // Запуск игры.
                gameState = GameState::MainMenu;  // Переход в Главное меню по окончании игры.
                break;
            case GameState::HowToPlay:
                // Отрисовка подменю "Как играть" Главного меню в окне мини-игры.
                menu.displayHowToPlay(window);
                break;
            case GameState::About:
                // Отрисовка подменю "Об игре" Главного меню в окне мини-игры.
                menu.displayAbout(window);
                break;
        }

        Event event{};
        // Обработка очереди событий.
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();  // Закрытие окна.
            } else if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (gameState == GameState::MainMenu) {
                    if (buttons[0].getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                              static_cast<float>( mousePos.y))) {
                        // Запуск игры из Главного меню.
                        gameState = GameState::Playing;
                        window.reset();  // Перезапуск игры.
                    } else if (buttons[1].getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                                     static_cast<float>(mousePos.y))) {
                        gameState = GameState::HowToPlay;
                    } else if (buttons[2].getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                                     static_cast<float>(mousePos.y))) {
                        // Переход из Главного меню в раздел "Об игре" при нажатии кнопки.
                        gameState = GameState::About;
                    }
                } else if (gameState == GameState::HowToPlay || gameState == GameState::About) {
                    if (menu.backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                                   static_cast<float>(mousePos.y))) {
                        // Переход из подменю в Главное меню при нажатии кнопки "Назад".
                        gameState = GameState::MainMenu;
                    }
                }
            } else if (event.type == Event::KeyPressed) {
                // Переход из подменю в Главное меню при нажатии клавиши Escape или Enter.
                if (event.key.code == Keyboard::Escape || event.key.code == Keyboard::Enter) {
                    if (gameState == GameState::MainMenu) {
                        // Из Главного меню выход только по клавише Escape.
                        if (event.key.code == Keyboard::Escape) {
                            window.close();  // Закрытие окна.
                        }
                    } else {
                        // Выход в Главное меню.
                        gameState = GameState::MainMenu;
                    }
                }
                // Переход в полноэкранный режим при нажатии клавиши F.
                if (event.key.scancode == Keyboard::Scan::F) {
                    if (!window.isFullscreen) {
                        window.isFullscreen = true;
                        window.create(VideoMode(1024, 768),
                                      "Back to the Future",
                                      sf::Style::Fullscreen);
                        window.setMainWindowIcon();
                    } else {  // И выход из него.
                        window.isFullscreen = false;
                        window.create(VideoMode(1024, 768),
                                      "Back to the Future",
                                      sf::Style::Titlebar | sf::Style::Close);
                        window.setMainWindowIcon();
                    }
                }
            }
        }

        // Проигрывание музыки Главного меню, если она остановилась.
        if (menu.curMusic.getStatus() == SoundSource::Status::Stopped) {
            if (menu.curMusic.openFromFile(menu.songs[0]))
                menu.curMusic.play();
        }
    }

    return 0;
}

#pragma clang diagnostic pop