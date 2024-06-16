//
// Created by anoso on 16.06.2024.
//

#include "LightningAnimation.h"

LightningAnimation::LightningAnimation()
        : animationDuration(0), currentTime(0), currentFrame(0), finished(false) {}

void LightningAnimation::load(const std::string &spriteSheetPath, int frameWidth, int frameHeight, float animationDuration) {
    this->animationDuration = animationDuration;
    texture.loadFromFile(spriteSheetPath);
    sprite.setTexture(texture);

    int rows = texture.getSize().y / frameHeight;
    int cols = texture.getSize().x / frameWidth;

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            frames.emplace_back(x * frameWidth, y * frameHeight, frameWidth, frameHeight);
        }
    }

    sprite.setTextureRect(frames[0]);
}

void LightningAnimation::start() {
    currentTime = 0;
    currentFrame = 0;
    finished = false;
}

void LightningAnimation::update(float deltaTime) {
    if (finished) return;

    currentTime += deltaTime;

    if (currentTime >= animationDuration) {
        finished = true;
        return;
    }

    float frameDuration = animationDuration / frames.size();
    int frameIndex = static_cast<int>(currentTime / frameDuration);

    if (frameIndex != currentFrame) {
        currentFrame = frameIndex;
        sprite.setTextureRect(frames[currentFrame]);
    }
}

void LightningAnimation::draw(sf::RenderWindow &window) {
    if (!finished) {
        window.draw(sprite);
    }
}

bool LightningAnimation::isFinished() const {
    return finished;
}
