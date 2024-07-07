//
// Created by anoso on 24.06.2024.
//

#include "FireTrace.h"  // Класс анимации огненного следа от колёс.

FireTrace::FireTrace(const Texture &texture, const Vector2f &position)
        : currentFrame(0), frameCount(64), framesPerSide(8) {
    frameSize = static_cast<int>(texture.getSize().x) / framesPerSide;  // Размер одного кадра.

    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0,
                                  frameSize, frameSize));
    sprite.setScale(0.65, 0.65);
    sprite.setPosition(position);
}

// Метод обновления кадров анимации.
void FireTrace::update() {
    currentFrame++;  // Переход к следующему кадру.
    if (currentFrame >= frameCount) {
        currentFrame = 0;  // Переход к первому кадру.
    }

    int row = currentFrame / framesPerSide;
    int col = currentFrame % framesPerSide;

    // Установка текущего кадра анимации.
    sprite.setTextureRect(IntRect(col * frameSize, row * frameSize,
                                  frameSize, frameSize));
}

// Метод отрисовки кадра анимации.
void FireTrace::draw(RenderWindow &window) {
    window.draw(sprite);
}

// Метод проверки окончания анимации.
bool FireTrace::isFinished() const {
    // Анимация продолжается до появления экрана окончания игры.
    return false;
}
