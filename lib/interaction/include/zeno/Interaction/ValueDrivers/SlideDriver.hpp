#ifndef INCLUDED_ZENO_INTERACTION_VALUE_DRIVERS_SLIDE_DRIVER
#define INCLUDED_ZENO_INTERACTION_VALUE_DRIVERS_SLIDE_DRIVER

#include <zeno/Interaction/ValueDriver.hpp>

namespace ze {

	class SlideDriver : public ValueDriver {
	public:
		SlideDriver(float _start, float _end, float _length);
		SlideDriver(float _start, float _end, float _length, float _timeDelay);

		float calculateValue(float _time) override;

	private:
		float m_StartValue;
		float m_EndValue;
	};

}

#endif // INCLUDED_ZENO_INTERACTION_VALUE_DRIVERS_SLIDE_DRIVER