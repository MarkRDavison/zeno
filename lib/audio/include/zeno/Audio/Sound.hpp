#ifndef INCLUDED_ZENO_AUDIO_SOUND_HPP_
#define INCLUDED_ZENO_AUDIO_SOUND_HPP_

#include <zeno/Audio/AudioSource.hpp>

#include <string>
#include <vector>

namespace ze {

	class SoundBuffer;
	class Sound : public AudioSource {
	public:
		Sound();
		Sound(const Sound& _other);
		Sound(Sound&& _other) noexcept;
		Sound& operator=(const Sound& _other);
		Sound& operator=(Sound&& _other) noexcept;
		~Sound() override;

		void play() override;
		void pause() override;
		void stop() override;

		float getCurrentTime() const override;

		bool getLooping() const override;
		void setLooping(bool _loop) override;

		float getGain() const override;
		void setGain(float _gain) override;

		float getPitch() const override;
		void setPitch(float _pitch) override;

		ze::Vector3f getPosition() const override;
		void setPosition(const ze::Vector3f& _position) override;

		ze::Vector3f getDirection() const override;
		void setDirection(const ze::Vector3f& _direction) override;

		AudioState getState() const override;

		void setSoundBuffer(SoundBuffer* _buffer);
		void resetBuffer();

	private:
		unsigned m_Source{ 0 };
		SoundBuffer* m_Buffer{ nullptr };
	};
}

#endif // INCLUDED_ZENO_AUDIO_SOUND_HPP_