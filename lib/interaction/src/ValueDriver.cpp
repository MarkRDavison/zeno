#include <zeno/Interaction/ValueDriver.hpp>

namespace ze {


	ValueDriver::ValueDriver(float _length) :
	ValueDriver(0.0f, _length) {

	}
	ValueDriver::ValueDriver(float _startTime, float _length) :
		m_StartTime(_startTime),
		m_Length(_length) {

	}

	float ValueDriver::update(float _delta) {
		m_CurrentTime += _delta;
		if (m_CurrentTime < m_StartTime) {
			m_CurrentValue = calculateValue(0.0f);
			return m_CurrentValue;
		}

		const float totalTime = m_Length + m_StartTime;
		if (m_CurrentTime >= totalTime) {
			m_CurrentTime -= totalTime;
			m_FirstPeriodDone = true;
		}

		const float relativeTime = (m_CurrentTime - m_StartTime) / m_Length;
		m_CurrentValue = calculateValue(relativeTime);
		return m_CurrentValue;
	}
	bool ValueDriver::hasCompletedOnePeriod() const {
		return m_FirstPeriodDone;
	}
	float ValueDriver::getCurrentValue() const {
		return m_CurrentValue;
	}

}