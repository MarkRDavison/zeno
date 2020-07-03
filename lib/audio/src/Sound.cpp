#include <zeno/Audio/Sound.hpp>
#include <zeno/Audio/SoundBuffer.hpp>
#include <iostream>
#include <AL/al.h>
#include <cassert>

namespace ze {


	Sound::Sound() {
		alGenSources(1, &m_Source);
	}

	Sound::Sound(const Sound& _other) {
		alGenSources(1, &m_Source);
	
		setLooping(_other.getLooping());
		setGain(_other.getGain());
		setPitch(_other.getPitch());
		setDirection(_other.getDirection());
		setPosition(_other.getPosition());
		setSoundBuffer(_other.m_Buffer);
	}
	Sound::Sound(Sound&& _other) noexcept {
		this->m_Source = _other.m_Source;

		setSoundBuffer(_other.m_Buffer);
		this->setSoundBuffer(_other.m_Buffer);

		_other.m_Source = 0;
		_other.resetBuffer();
	}
	Sound& Sound::operator=(const Sound& _other) {
		setLooping(_other.getLooping());
		setGain(_other.getGain());
		setPitch(_other.getPitch());
		setDirection(_other.getDirection());
		setPosition(_other.getPosition());
		setSoundBuffer(_other.m_Buffer);
		this->setSoundBuffer(_other.m_Buffer);
	
		return *this;
	}
	Sound& Sound::operator=(Sound&& _other) noexcept {
		assert(this != &_other);

		resetBuffer();
		if (m_Source != 0) {
			alDeleteSources(1, &m_Source);
			m_Source = 0;
		}

		this->m_Source = _other.m_Source;
		this->setSoundBuffer(_other.m_Buffer);

		_other.m_Source = 0;
		_other.resetBuffer();

		return *this;
	}
	Sound::~Sound() {
		resetBuffer();
		if (m_Source != 0) {
			alDeleteSources(1, &m_Source);
		}
	} 
	void Sound::play() {
		alSourcePlay(m_Source);
	}
	void Sound::pause() {
		alSourcePause(m_Source);
	}
	void Sound::stop() {
		alSourceStop(m_Source);
	}

	float Sound::getCurrentTime()const {
		float f{ 0.0f };
		alGetSourcef(m_Source, AL_SEC_OFFSET, &f);
		return f;
	}

	bool Sound::getLooping() const {
		int b{ 0 };
		alGetSourcei(m_Source, AL_LOOPING, &b);
		return b == AL_TRUE;
	}
	void Sound::setLooping(bool _loop) {
		alSourcei(m_Source, AL_LOOPING, _loop ? AL_TRUE : AL_FALSE);
	}

	float Sound::getGain() const {
		float f{ 0.0f };
		alGetSourcef(m_Source, AL_GAIN, &f);
		return f;
	}
	void Sound::setGain(float _gain) {
		alSourcef(m_Source, AL_GAIN, _gain);
	}

	float Sound::getPitch() const {
		float f{ 0.0f };
		alGetSourcef(m_Source, AL_PITCH, &f);
		return f;
	}
	void Sound::setPitch(float _pitch) {
		alSourcef(m_Source, AL_PITCH, _pitch);
	}

	ze::Vector3f Sound::getPosition() const {
		ze::Vector3f pos;
		alGetSource3f(m_Source, AL_POSITION, &pos.x, &pos.y, &pos.z);
		return pos;
	}
	void Sound::setPosition(const ze::Vector3f& _position) {
		alSource3f(m_Source, AL_POSITION, _position.x, _position.y, _position.z);
	}

	ze::Vector3f Sound::getDirection() const {
		ze::Vector3f dir;
		alGetSource3f(m_Source, AL_VELOCITY, &dir.x, &dir.y, &dir.z);
		return dir;
	}
	void Sound::setDirection(const ze::Vector3f& _direction) {
		alSource3f(m_Source, AL_VELOCITY, _direction.x, _direction.y, _direction.z);
	}

	AudioState Sound::getState() const {
		int state;
		alGetSourcei(m_Source, AL_SOURCE_STATE, &state);

		switch (state) {
		case AL_INITIAL:
			return AudioState::Initial;
		case AL_PLAYING:
			return AudioState::Playing;
		case AL_PAUSED:
			return AudioState::Paused;
		case AL_STOPPED:
		default:
			return AudioState::Stopped;
		}
	}

	void Sound::setSoundBuffer(SoundBuffer* _buffer) {
		m_Buffer = _buffer;
		if (m_Buffer != nullptr && m_Source != 0) {
			alSourcei(m_Source, AL_BUFFER, m_Buffer->m_Buffer);
		}
	}
	void Sound::resetBuffer() {
		m_Buffer = nullptr;
	}
}