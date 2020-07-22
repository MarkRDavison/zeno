#include <zeno/Audio.hpp>
#include <thread>
#include <chrono>

int main(int _argc, char** _argv) {
    std::string soundPath = "./data/sound.wav";

    ze::AudioContext context;

    ze::SoundBuffer buffer;
    if (!buffer.load(soundPath)) {
        return EXIT_SUCCESS;
    }

    ze::Sound sound;
    sound.setSoundBuffer(&buffer);

    sound.play();

    while (ze::AudioState::Playing == sound.getState()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return EXIT_SUCCESS;
}