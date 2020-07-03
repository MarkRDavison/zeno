#include <zeno/Audio/SoundBuffer.hpp>
#include <zeno/Audio/WaveLoader.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>

namespace ze {

	SoundBuffer::SoundBuffer(const SoundBuffer& _other) {
		if (_other.m_Buffer == 0) {
			return;
		}

		m_NumberChannels = _other.m_NumberChannels;
		m_SampleRate = _other.m_SampleRate;
		m_BitsPerSample = _other.m_BitsPerSample;
		m_Data = std::vector<char>(_other.m_Data);

		initialiseBuffer();
	}
	SoundBuffer::SoundBuffer(SoundBuffer&& _other) noexcept {
		m_Buffer = _other.m_Buffer;
		m_NumberChannels = _other.m_NumberChannels;
		m_SampleRate = _other.m_SampleRate;
		m_BitsPerSample = _other.m_BitsPerSample;
		m_Data = std::move(_other.m_Data);

		_other.m_Buffer = 0;
		_other.m_NumberChannels = 0;
		_other.m_SampleRate = 0;
		_other.m_BitsPerSample = 0;
	}
	SoundBuffer& SoundBuffer::operator=(const SoundBuffer& _other) {
		if (_other.m_Buffer == 0) {
			return *this;
		}

		m_NumberChannels = _other.m_NumberChannels;
		m_SampleRate = _other.m_SampleRate;
		m_BitsPerSample = _other.m_BitsPerSample;
		m_Data = std::vector<char>(_other.m_Data);

		initialiseBuffer();

		return *this;
	}
	SoundBuffer& SoundBuffer::operator=(SoundBuffer&& _other) noexcept {
		if (m_Buffer != 0) {
			alDeleteBuffers(1, &m_Buffer);
		}

		m_Buffer = _other.m_Buffer;
		m_NumberChannels = _other.m_NumberChannels;
		m_SampleRate = _other.m_SampleRate;
		m_BitsPerSample = _other.m_BitsPerSample;
		m_Data = std::move(_other.m_Data);

		_other.m_Buffer = 0;
		_other.m_NumberChannels = 0;
		_other.m_SampleRate = 0;
		_other.m_BitsPerSample = 0;

		return *this;
	}
	SoundBuffer::~SoundBuffer() {
		if (m_Buffer != 0) {
			alDeleteBuffers(1, &m_Buffer);
		}
	}

	bool SoundBuffer::load(const std::string& _filename) {
		if (_filename.size() < 4) {
			return false;
		}

		if (_filename.substr(_filename.size() - 4) == ".wav") {
			if (!WaveLoader::load(_filename, m_Data, m_NumberChannels, m_SampleRate, m_BitsPerSample)) {
				return false;
			}
		}
		else {
			std::cerr << "Invalid file type to load " << _filename.substr(_filename.size() - 4) << std::endl;
			return false;
		}


		initialiseBuffer();

		return true;
	}
	void SoundBuffer::initialiseBuffer() {
		if (m_Buffer != 0) {
			alDeleteBuffers(1, &m_Buffer);
		}

		if (m_Data.empty()) {
			return;
		}

		alGenBuffers(1, &m_Buffer);
		alBufferData(
			m_Buffer,
			WaveLoader::getFormat(m_NumberChannels, m_BitsPerSample),
			&m_Data[0],
			m_Data.size(),
			m_SampleRate);
	}

	float SoundBuffer::getDuration() const {
		return static_cast<float>(m_Data.size()) / static_cast<float>(m_SampleRate) / static_cast<float>(m_NumberChannels) / static_cast<float>(m_BitsPerSample / (sizeof(char) * CHAR_BIT));
	}
	int SoundBuffer::getNumberChannels() const {
		return m_NumberChannels;
	}
	int SoundBuffer::getSampleRate() const {
		return m_SampleRate;
	}
	int SoundBuffer::getBitsPerSample() const {
		return m_BitsPerSample;
	}
	unsigned SoundBuffer::getSampleCount() const {
		return m_Data.size();
	}
	const char* SoundBuffer::getSamples() const {
		return m_Data.data();
	}

}