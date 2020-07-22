#ifndef INCLUDED_ZENO_INTERACTION_VALUE_DRIVER_HPP_
#define INCLUDED_ZENO_INTERACTION_VALUE_DRIVER_HPP_

namespace ze {

	class ValueDriver {
	public:
		ValueDriver(float _length);
		ValueDriver(float _startTime, float _length);
		virtual ~ValueDriver() = 0;

		float update(float _delta);
		bool hasCompletedOnePeriod() const;
		float getCurrentValue() const;

		virtual float calculateValue(float _time) = 0;

	private:
		float m_StartTime{ 0.0f };
		float m_Length{ 0.0f };
		float m_CurrentValue{ 0.0f };
		float m_CurrentTime{ 0.0f };
		bool m_FirstPeriodDone{ false };
	};

	inline ValueDriver::~ValueDriver() = default;
}

#endif // INCLUDED_ZENO_INTERACTION_VALUE_DRIVER_HPP_