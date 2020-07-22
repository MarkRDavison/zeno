#include <zeno/Interaction/ValueDrivers/SlideDriver.hpp>
#include <cmath>

namespace ze {

	float cosInterpolate(float a, float b, float _blend) {
		float ft = _blend * 3.14159265f;
		float f = (1.0f - cosf(ft)) * 0.5f;
		return a * (1 - f) + b * f;
	}

	SlideDriver::SlideDriver(float _start, float _end, float _length) :
		SlideDriver(_start, _end, _length, 0.0f) {
	}
	SlideDriver::SlideDriver(float _start, float _end, float _length, float _timeDelay) :
		ValueDriver(_timeDelay, _length),
		m_StartValue(_start),
		m_EndValue(_end) {

	}

	float SlideDriver::calculateValue(float _time) {
		if (hasCompletedOnePeriod()) {
			return m_EndValue;
		}

		return cosInterpolate(m_StartValue, m_EndValue, _time);
	}

}