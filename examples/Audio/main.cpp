#include <zeno/Audio.hpp>
#include <thread>
#include <chrono>

int main(int _argc, char** _argv) {

    if (_argc < 2) {
        std::cout << "Please pass the path to a sound file as the parameter" << std::endl;
        return EXIT_FAILURE;
    }

    std::string soundPath = _argv[1];

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