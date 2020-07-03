#include <zeno/Audio/Music.hpp>
#include <zeno/Audio/WaveLoader.hpp>
#include <iostream>
#include <cassert>
#include <AL/al.h>
#include <AL/alc.h>

namespace ze {

	Music::Music() {
	}
    Music::~Music() {
		if (m_Source != 0) {
			alDeleteSources(1, &m_Source);
		}
		delete[]Scratch;
    }

    bool Music::load(const std::string& _filename) {
		if (m_Source != 0) {
			alDeleteSources(1, &m_Source);
			alDeleteBuffers(NUM_BUFFERS, &m_Buffers[0]);
		}

		alGenSources(1, &m_Source);
		alGenBuffers(NUM_BUFFERS, &m_Buffers[0]);

		if (Scratch == nullptr) {
			Scratch = new char[BUFFER_SIZE];
		}

		if (_filename.size() < 4) {
			return false;
		}

		std::ifstream file(_filename, std::ios::binary);
		if (!file.is_open()) {
			std::cerr << "ERROR: could not open file '" << _filename << "'" << std::endl;
			return false;
		}


		if (_filename.substr(_filename.size() - 4) == ".wav") {
			if (!WaveLoader::parseHeader(
				file,
				m_NumberChannels,
				m_SampleRate,
				m_BitsPerSample,
				m_Size)) {

				return false;
			}
		}
		else {
			std::cerr << "Invalid file type to load " << _filename.substr(_filename.size() - 4) << std::endl;
			return false;
		}

		m_Cursor = 0;

		for (unsigned i = 0; i < NUM_BUFFERS; ++i) {

			std::size_t dataSizeToCopy = BUFFER_SIZE;
			if (m_Cursor + BUFFER_SIZE > m_Size) {
				if (!m_Looping && !m_LoopEndReached) {
					m_LoopEndReached = true;
				}
				dataSizeToCopy = m_Size - m_Cursor;
			}

			file.read(Scratch, dataSizeToCopy);
			alBufferData(
				m_Buffers[i],
				WaveLoader::getFormat(m_NumberChannels, m_BitsPerSample), 
				Scratch,
				dataSizeToCopy,
				m_SampleRate);

			m_Cursor += dataSizeToCopy;
		}
		alSourceQueueBuffers(m_Source, NUM_BUFFERS, &m_Buffers[0]);
		m_CursorStart = m_Cursor;
		file.close();
		this->filename = _filename;
        return true;
    }

	void Music::play() {
		m_LoopEndReached = false;
		alSourcePlay(m_Source);
	}
	void Music::pause() {
	}
	void Music::stop() {
		alSourceStop(m_Source);
	}

	void Music::update() {
		ALint buffersProcessed = 0;
		alGetSourcei(m_Source, AL_BUFFERS_PROCESSED, &buffersProcessed);

		if (buffersProcessed <= NUM_BUFFERS / 2) {
			return;
		}

		if (buffersProcessed == NUM_BUFFERS) {
			stop();
		}
		if (m_LoopEndReached && !m_Looping) {
			return;
		}

		std::ifstream file(filename, std::ios::binary);
		file.seekg(m_Cursor, file.beg);

		while (buffersProcessed--) {
			unsigned startCursor = m_Cursor;
			ALuint b;
			alSourceUnqueueBuffers(m_Source, 1, &b);
		
			std::memset(Scratch, 0, BUFFER_SIZE);
			std::size_t dataSizeToCopy = BUFFER_SIZE;
			if (m_Cursor + BUFFER_SIZE > m_Size) {
				if (!m_Looping && !m_LoopEndReached) {
					m_LoopEndReached = true;
				}
				dataSizeToCopy = m_Size - m_Cursor;
			}
		
			file.read(&Scratch[0], dataSizeToCopy);

			m_Cursor += dataSizeToCopy;
		
			if (dataSizeToCopy < BUFFER_SIZE &&
				!m_LoopEndReached) {
				m_Cursor = 0;
				file.seekg(0, file.beg);
				file.read(&Scratch[dataSizeToCopy], BUFFER_SIZE - dataSizeToCopy);
				m_Cursor = BUFFER_SIZE - dataSizeToCopy;
				dataSizeToCopy = BUFFER_SIZE;
			}
		
			alBufferData(b, WaveLoader::getFormat(m_NumberChannels, m_BitsPerSample), Scratch, dataSizeToCopy, m_SampleRate);
			alSourceQueueBuffers(m_Source, 1, &b);
		}
		
		file.close();
	}
	float Music::getDuration() const {
		return static_cast<float>(m_Size) / static_cast<float>(m_SampleRate) / static_cast<float>(m_NumberChannels) / static_cast<float>(m_BitsPerSample / (sizeof(char) * CHAR_BIT));
	}
	float Music::getCurrentTime()const {
		if (m_NumberChannels == 0 || m_SampleRate == 0) {
			return 0.0f;
		}

		float f{ 0.0f };
		alGetSourcef(m_Source, AL_SEC_OFFSET, &f);

		return static_cast<float>(m_Cursor - m_CursorStart) / static_cast<float>(m_NumberChannels) / static_cast<float>(m_SampleRate) / static_cast<float>(m_BitsPerSample / (sizeof(char) * CHAR_BIT)) + f;
	}

	bool Music::getLooping() const {
		return m_Looping;
	}
	void Music::setLooping(bool _loop) {
		m_Looping = _loop;
	}

	float Music::getGain() const {
		float f{ 0.0f };
		alGetSourcef(m_Source, AL_GAIN, &f);
		return f;
	}
	void Music::setGain(float _gain) {
		alSourcef(m_Source, AL_GAIN, _gain);
	}

	float Music::getPitch() const {
		float f{ 0.0f };
		alGetSourcef(m_Source, AL_PITCH, &f);
		return f;
	}
	void Music::setPitch(float _pitch) {
		alSourcef(m_Source, AL_PITCH, _pitch);
	}

	ze::Vector3f Music::getPosition() const {
		ze::Vector3f pos;
		alGetSource3f(m_Source, AL_POSITION, &pos.x, &pos.y, &pos.z);
		return pos;
	}
	void Music::setPosition(const ze::Vector3f& _position) {
		alSource3f(m_Source, AL_POSITION, _position.x, _position.y, _position.z);
	}

	ze::Vector3f Music::getDirection() const {
		ze::Vector3f dir;
		alGetSource3f(m_Source, AL_VELOCITY, &dir.x, &dir.y, &dir.z);
		return dir;
	}
	void Music::setDirection(const ze::Vector3f& _direction) {
		alSource3f(m_Source, AL_VELOCITY, _direction.x, _direction.y, _direction.z);
	}

	AudioState Music::getState() const {
		int state;
		alGetSourcei(m_Source, AL_SOURCE_STATE, &state);

		switch (state) {
		case AL_PLAYING:
			return AudioState::Playing;
		case AL_PAUSED:
			return AudioState::Paused;
		case AL_STOPPED:
		case AL_INITIAL:
		default:
			return AudioState::Stopped;
		}
	}
}