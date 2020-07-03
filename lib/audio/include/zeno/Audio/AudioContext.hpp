#ifndef INCLUDED_ZENO_AUDIO_AUDIO_CONTEXT_HPP_
#define INCLUDED_ZENO_AUDIO_AUDIO_CONTEXT_HPP_

namespace ze {

    struct AudioContext {
        AudioContext();
        ~AudioContext();

        static void setGlobalVolume(float _volume);
        static float getGlobalVolume();

        static void setMute(bool _mute);
        static bool getMute();
        static void toggleMute();

    private:
        void init();
        void close();

    private:
        static float volume;
        static bool mute;
        static int instances;
        void* openALDevice{ nullptr };
        void* openALContext{ nullptr };
    };

}

#endif // INCLUDED_ZENO_AUDIO_AUDIO_CONTEXT_HPP_