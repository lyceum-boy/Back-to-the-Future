//
// Created by anoso on 22.06.2024.
//

#include "Explosion.h"  // Класс анимации взрыва.

Explosion::Explosion(Texture &texture, Vector2f position)
        : currentFrame(0), frameDuration(0.1f), elapsedTime(0), finished(false) {
    // Добавление 8 кадров анимации из спрайт-листа.
    for (int i = 0; i < 8; ++i) {
        frames.emplace_back(i * (texture.getSize().x / 8), 0,
                            texture.getSize().x / 8, texture.getSize().y);
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(frames[0]);
    // Смещение позиции взрыва, чтобы центрировать его относительно позиции бонуса.
    sprite.setPosition(static_cast<float>(position.x - (texture.getSize().x / 8.0) / 2),
                       static_cast<float>(position.y - texture.getSize().y / 3.0));
}

// Метод обновления кадров анимации.
void Explosion::update() {
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
void Explosion::draw(RenderWindow &window) {
    if (!finished) {
        window.draw(sprite);
    }
}

// Метод проверки окончания анимации.
bool Explosion::isFinished() const {
    return finished;
}
