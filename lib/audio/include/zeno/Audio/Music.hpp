#ifndef INCLUDED_ZENO_AUDIO_MUSIC_HPP_
#define INCLUDED_ZENO_AUDIO_MUSIC_HPP_

#include <zeno/Audio/AudioSource.hpp>

#include <string>
#include <vector>

namespace ze {

	class Music : public AudioSource {
	public:
		Music();
		Music(const Music& _other) = delete;
		Music(Music&& _other) noexcept = delete;
		Music& operator=(const Music& _other) = delete;
		Music& operator=(Music&& _other) noexcept = delete;
		~Music();

		bool load(const std::string& _filename);

		void play() override;
		void pause() override;
		void stop() override;
		void update();

		float getDuration() const;
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

	private:
		static constexpr std::size_t NUM_BUFFERS{ 8 };
		static constexpr std::size_t BUFFER_SIZE{ 65536 };

		bool m_LoopEndReached{ false };
		bool m_Looping{ true };
		unsigned m_NumberChannels;
		int m_SampleRate;
		unsigned m_BitsPerSample;
		unsigned m_Size;

		unsigned m_Buffers[NUM_BUFFERS]{ 0 };
		unsigned m_Source{ 0 };
		unsigned m_Cursor{ 0 };
		unsigned m_CursorStart{ 0 };
		char* Scratch{ nullptr };

		std::string filename;
	};
}

#endif // INCLUDED_ZENO_AUDIO_MUSIC_HPP_