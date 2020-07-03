#include <zeno/Audio/AudioContext.hpp>
#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>

namespace ze {

    float AudioContext::volume{ Start };
    bool AudioContext::mute{ false };
    int AudioContext::instances{ 0 };

    AudioContext::AudioContext() {
        if (instances == 0) {
            init();
        }
        instances++;
    }
    AudioContext::~AudioContext() {
        instances--;
        if (instances == 0) {
            close();
        }
    }

    void AudioContext::setGlobalVolume(float _volume) {
        volume = _volume;
        if (volume < 0.0f) {
            volume = 0.0f;
        }
        if (!mute) {
            alListenerf(AL_GAIN, volume);
        }
    }
    float AudioContext::getGlobalVolume() {
        return mute ? 0.0f : volume;
    }

    void AudioContext::setMute(bool _mute) {
        if (mute != _mute) {
            mute = _mute;

            alListenerf(AL_GAIN, mute ? 0.0f : volume);
        }
    }
    bool AudioContext::getMute() {
        return mute;
    }
    void AudioContext::toggleMute() {
        setMute(!getMute());
    }

    void AudioContext::init() {
        openALDevice = alcOpenDevice(nullptr);
        if (!openALDevice) {
            std::cerr << "ERROR: Could not open audio device" << std::endl;
            return;
        }

        if (openALContext = alcCreateContext((ALCdevice*)openALDevice, nullptr); openALContext == nullptr) {
            std::cerr << "ERROR: Could not create audio context" << std::endl;
            return;
        }

        if (!alcMakeContextCurrent((ALCcontext*)openALContext)) {
            std::cerr << "ERROR: Could not make audio context current" << std::endl;
            return;
        }
    }

    void AudioContext::close() {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext((ALCcontext*)openALContext);
        alcCloseDevice((ALCdevice*)openALDevice);
    }



}