//
// Created by anoso on 22.06.2024.
//

#include "Lightning.h"  // Класс анимации молнии.

Lightning::Lightning(Texture &texture, Vector2f position)
        : currentFrame(0), frameDuration(0.1f), elapsedTime(0), finished(false) {
    int frameWidth = static_cast<int>(texture.getSize().x / 2);   // 2 столбца.
    int frameHeight = static_cast<int>(texture.getSize().y / 2);  // 2 строки.

    // Добавление 4 кадров анимации из спрайт-листа.
    for (int i = 0; i < 4; ++i) {
        frames.emplace_back(i % 2 * frameWidth, i / 2 * frameHeight,
                            frameWidth, frameHeight);
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(frames[0]);
    sprite.setScale(0.35, 0.25);
    sprite.setPosition(
            position.x - sprite.getScale().x * static_cast<float>(frameWidth) / 2.0f,
            position.y
    );
}

// Метод обновления кадров анимации.
void Lightning::update() {
    // Увеличение времени, прошедшего с последнего обновления.
    elapsedTime += frameDuration;
    // Проверка, прошло ли достаточно времени для смены кадра.
    if (elapsedTime >= frameDuration) {
        elapsedTime = 0;  // Сброс прошедшего времени.
        ++currentFrame;   // Переход к следующему кадру.
        // Проверка, достигнут ли конец анимации.
        if (currentFrame >= frames.size()) {
            finished = true;  // Анимация окончена.
        } else {
            // Установка текущего кадра анимации.
            sprite.setTextureRect(frames[currentFrame]);
        }
    }
}

// Метод отрисовки кадра анимации.
void Lightning::draw(RenderWindow &window) {
    if (!finished) {
        window.draw(sprite);
    }
}

// Метод проверки окончания анимации.
bool Lightning::isFinished() const {
    return finished;
}
