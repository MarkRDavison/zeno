#ifndef INCLUDED_ZENO_AUDIO_AUDIO_SOURCE_HPP_
#define INCLUDED_ZENO_AUDIO_AUDIO_SOURCE_HPP_

#include <zeno/Core/Vector3.hpp>

namespace ze {

	enum class AudioState {
		Playing,
		Paused,
		Stopped,
		Initial
	};

	class AudioSource {
	public:
		virtual ~AudioSource() = default;

		virtual void play() = 0;
		virtual void pause() = 0;
		virtual void stop() = 0;

		virtual float getCurrentTime()const = 0;

		virtual bool getLooping() const = 0;
		virtual void setLooping(bool _loop) = 0;

		virtual float getGain() const = 0;
		virtual void setGain(float _gain) = 0;

		virtual float getPitch() const = 0;
		virtual void setPitch(float _pitch) = 0;

		virtual ze::Vector3f getPosition() const = 0;
		virtual void setPosition(const ze::Vector3f& _position) = 0;

		virtual ze::Vector3f getDirection() const = 0;
		virtual void setDirection(const ze::Vector3f& _direction) = 0;

		virtual AudioState getState() const = 0;
	};

}

#endif // INCLUDED_ZENO_AUDIO_AUDIO_SOURCE_HPP_