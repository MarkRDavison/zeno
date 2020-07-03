#ifndef INCLUDED_ZENO_AUDIO_WAVE_LOADER_HPP_
#define INCLUDED_ZENO_AUDIO_WAVE_LOADER_HPP_

#include <fstream>
#include <string>
#include <vector>

namespace ze {

	class WaveLoader {
		WaveLoader() = delete;
		~WaveLoader() = delete;
	public:
		static constexpr unsigned HeaderSize{ 48u };

		static bool load(const std::string& _filename,
			std::vector<char>& _data,
			unsigned& _numberChannels,
			int& _sampleRate,
			unsigned& _bitsPerSample);

		static bool parseHeader(std::ifstream& _file,
			unsigned& _numberChannels,
			int& _sampleRate,
			unsigned& _bitsPerSample,
			unsigned& _size);

		static bool load(std::ifstream& _file,
			std::vector<char>& _data,
			unsigned& _numberChannels,
			int& _sampleRate,
			unsigned& _bitsPerSample);

		static unsigned getFormat(unsigned channels, unsigned bitsPerSample);

	private:
		static int getSourceState(unsigned _source);
		static int convert_to_int(char* _buffer, unsigned _length);
	};

}

#endif // INCLUDED_ZENO_AUDIO_WAVE_LOADER_HPP_