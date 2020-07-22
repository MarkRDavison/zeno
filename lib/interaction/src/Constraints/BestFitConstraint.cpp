#include <zeno/Interaction/Constraints/BestFitConstraint.hpp>
#include <zeno/Interaction/Component.hpp>
#include <zeno/Interaction/Desktop.hpp>

namespace ze {

	BestFitConstraint::BestFitConstraint(float _aspectRatio) :
		m_AspectRatio(_aspectRatio) {

	}

	float BestFitConstraint::getRelativeValue() {
		const auto size = parent->desktop->getPixelSize();
		const float windowAspect = size.x / size.y;

		const float parentSize = xAxis
			? (parent->getPixelWidth() / size.x) / windowAspect
			: (parent->getPixelHeight() / size.y) * windowAspect;

		return xAxis
			? parentSize * m_AspectRatio
			: parentSize / m_AspectRatio;
	}
	void BestFitConstraint::setPixelValue(int _pixels) {
		throw "InvalidOperation";
	}
	void BestFitConstraint::setRelativeValue(float _value) {
		throw "InvalidOperation";
	}

}