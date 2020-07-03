#ifndef INCLUDED_ZENO_AUDIO_SOUND_BUFFER_HPP_
#define INCLUDED_ZENO_AUDIO_SOUND_BUFFER_HPP_

#include <cstdint>
#include <string>
#include <vector>

namespace ze {

	class SoundBuffer {
	public:
		SoundBuffer() = default;
		SoundBuffer(const SoundBuffer& _other);
		SoundBuffer(SoundBuffer&& _other) noexcept;
		SoundBuffer& operator=(const SoundBuffer& _other);
		SoundBuffer& operator=(SoundBuffer&& _other) noexcept;
		~SoundBuffer();

		bool load(const std::string& _filename);
		void initialiseBuffer();


		float getDuration() const;
		int getNumberChannels() const;
		int getSampleRate() const;
		int getBitsPerSample() const;
		unsigned getSampleCount() const;
		const char* getSamples() const;


	private:
		friend class Sound;

		unsigned m_NumberChannels{ 0 };
		int m_SampleRate{ 0 };
		unsigned m_BitsPerSample{ 0 };
		std::vector<char> m_Data;

		unsigned m_Buffer{ 0 };
	};

}

#endif // INCLUDED_ZENO_AUDIO_SOUND_BUFFER_HPP_